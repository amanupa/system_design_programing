#include "presentation/CliApp.hpp"

#include <istream>
#include <ostream>
#include <string>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

namespace {

std::string trim(const std::string& s) {
    const auto begin = s.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos) {
        return "";
    }
    const auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(begin, end - begin + 1);
}

bool parseInt(const std::string& s, int& out) {
    try {
        std::size_t pos = 0;
        const int value = std::stoi(s, &pos);
        if (pos != s.size()) {
            return false;
        }
        out = value;
        return true;
    } catch (...) {
        return false;
    }
}

}  // namespace

CliApp::CliApp(ParkingLot& lot, std::istream& in, std::ostream& out) noexcept
    : lot_(lot), in_(in), out_(out) {}

std::optional<std::string> CliApp::readLine(const std::string& prompt) const {
    out_ << prompt;
    out_.flush();
    std::string line;
    if (!std::getline(in_, line)) {
        return std::nullopt;  // end of input
    }
    return line;
}

std::optional<VehicleType> CliApp::promptVehicleType() const {
    out_ << "  Vehicle: 1)Bike 2)Car 3)SUV 4)Truck 5)Electric 6)VIP\n";
    const auto line = readLine("  Type> ");
    if (!line) {
        return std::nullopt;
    }
    int choice = 0;
    if (!parseInt(trim(*line), choice)) {
        throw InvalidArgumentException("vehicle type must be a number 1-6");
    }
    switch (choice) {
        case 1: return VehicleType::Bike;
        case 2: return VehicleType::Car;
        case 3: return VehicleType::Suv;
        case 4: return VehicleType::Truck;
        case 5: return VehicleType::ElectricVehicle;
        case 6: return VehicleType::Vip;
        default:
            throw InvalidArgumentException("vehicle type out of range (1-6)");
    }
}

std::optional<PaymentMethod> CliApp::promptPaymentMethod() const {
    out_ << "  Payment: 1)Cash 2)Card 3)UPI\n";
    const auto line = readLine("  Method> ");
    if (!line) {
        return std::nullopt;
    }
    int choice = 0;
    if (!parseInt(trim(*line), choice)) {
        throw InvalidArgumentException("payment method must be a number 1-3");
    }
    switch (choice) {
        case 1: return PaymentMethod::Cash;
        case 2: return PaymentMethod::Card;
        case 3: return PaymentMethod::Upi;
        default:
            throw InvalidArgumentException("payment method out of range (1-3)");
    }
}

void CliApp::printMenu() const {
    out_ << "\n 1) Park vehicle\n"
         << " 2) Exit vehicle\n"
         << " 3) Status\n"
         << " 4) Gate admin\n"
         << " 5) Reports\n"
         << " 0) Quit\n";
}

void CliApp::handlePark() {
    const auto type = promptVehicleType();
    if (!type) {
        return;
    }
    const auto plate = readLine("  License plate: ");
    if (!plate) {
        return;
    }
    const auto gate = readLine("  Entry gate id: ");
    if (!gate) {
        return;
    }
    const std::shared_ptr<Ticket> ticket =
        lot_.parkVehicle(trim(*gate), *type, trim(*plate));
    out_ << "  OK: ticket " << ticket->id() << " -> spot " << ticket->spotId()
         << " (floor " << ticket->floorNumber() << ")\n";
}

void CliApp::handleExit() {
    const auto ticketId = readLine("  Ticket id: ");
    if (!ticketId) {
        return;
    }
    const auto method = promptPaymentMethod();
    if (!method) {
        return;
    }
    const auto gate = readLine("  Exit gate id: ");
    if (!gate) {
        return;
    }
    const ExitReceipt receipt =
        lot_.exitVehicle(trim(*gate), trim(*ticketId), *method);
    out_ << "  OK: fee " << receipt.fee.toString() << " paid via "
         << toString(*method) << " (" << toString(receipt.payment->status())
         << ")\n";
}

void CliApp::handleStatus() const {
    out_ << "  Lot: " << lot_.name() << "\n"
         << "  Spots free: " << lot_.availableSpots() << "/" << lot_.totalSpots()
         << "\n"
         << "  Active tickets: " << lot_.activeTicketCount() << "\n"
         << "  Fee policy: " << lot_.feeStrategyName() << "\n"
         << "  Gates:\n";
    for (const std::string& summary : lot_.gateSummaries()) {
        out_ << "    - " << summary << "\n";
    }
}

void CliApp::handleGateAdmin() {
    out_ << "  Gates:\n";
    for (const std::string& summary : lot_.gateSummaries()) {
        out_ << "    - " << summary << "\n";
    }
    const auto gate = readLine("  Gate id: ");
    if (!gate) {
        return;
    }
    out_ << "  Action: 1)enable 2)disable 3)maintenance\n";
    const auto action = readLine("  Action> ");
    if (!action) {
        return;
    }
    int choice = 0;
    if (!parseInt(trim(*action), choice)) {
        throw InvalidArgumentException("action must be a number 1-3");
    }
    const std::string id = trim(*gate);
    switch (choice) {
        case 1: lot_.enableGate(id); break;
        case 2: lot_.disableGate(id); break;
        case 3: lot_.sendGateToMaintenance(id); break;
        default:
            throw InvalidArgumentException("gate action out of range (1-3)");
    }
    out_ << "  Gate " << id << " updated.\n";
}

void CliApp::handleReports() const {
    const OccupancyStats occ = lot_.occupancy();
    out_ << "  Occupancy: " << occ.occupiedSpots << "/" << occ.totalSpots << " ("
         << static_cast<int>(occ.occupancyPercent) << "%)\n";

    const RevenueStats rev = lot_.revenue();
    out_ << "  Revenue: " << rev.totalCollected.toString() << " ("
         << rev.successfulPayments << " ok, " << rev.failedPayments << " failed, "
         << rev.refundedPayments << " refunded)\n";

    const TicketStats ts = lot_.ticketStats();
    out_ << "  Tickets: " << ts.total << " total, " << ts.active << " active, "
         << ts.closed << " closed\n";

    const auto dateLine = readLine("  Daily report date (blank = today): ");
    if (!dateLine) {
        return;
    }
    std::string date = trim(*dateLine);
    if (date.empty()) {
        date = lot_.today();
    }
    const DailyReport report = lot_.dailyReport(date);
    out_ << "  [" << report.date << "] issued=" << report.ticketsIssued
         << " closed=" << report.ticketsClosed
         << " revenue=" << report.revenue.toString() << "\n";
}

int CliApp::run() {
    out_ << "\n=== " << lot_.name() << " — Parking Management ===\n";
    while (true) {
        printMenu();
        const auto line = readLine("Select> ");
        if (!line) {
            out_ << "\n(end of input)\n";
            return 0;
        }
        const std::string command = trim(*line);
        if (command.empty()) {
            continue;
        }
        int choice = 0;
        if (!parseInt(command, choice)) {
            out_ << "Please enter a number.\n";
            continue;
        }
        try {
            switch (choice) {
                case 1: handlePark(); break;
                case 2: handleExit(); break;
                case 3: handleStatus(); break;
                case 4: handleGateAdmin(); break;
                case 5: handleReports(); break;
                case 0: out_ << "Goodbye.\n"; return 0;
                default: out_ << "Unknown option.\n"; break;
            }
        } catch (const ParkingException& ex) {
            out_ << "! " << ex.what() << "\n";  // typed domain errors -> friendly UX
        }
    }
}

void runDemo(ParkingLot& lot, std::ostream& out) {
    out << "[demo] " << lot.name() << " — scripted scenario\n";
    const std::shared_ptr<Ticket> t1 =
        lot.parkVehicle("GATE-IN-1", VehicleType::Car, "DEMO-CAR-1");
    lot.parkVehicle("GATE-IO-1", VehicleType::ElectricVehicle, "DEMO-EV-1");
    out << "[demo] parked 2; free " << lot.availableSpots() << "/" << lot.totalSpots()
        << "\n";
    const ExitReceipt receipt =
        lot.exitVehicle("GATE-OUT-1", t1->id(), PaymentMethod::Upi);
    out << "[demo] exited " << t1->id() << "; fee " << receipt.fee.toString()
        << "; free " << lot.availableSpots() << "/" << lot.totalSpots() << "\n";

    const OccupancyStats occ = lot.occupancy();
    const RevenueStats rev = lot.revenue();
    const DailyReport day = lot.dailyReport(lot.today());
    out << "[demo] occupancy " << occ.occupiedSpots << "/" << occ.totalSpots << " ("
        << static_cast<int>(occ.occupancyPercent) << "%)\n";
    out << "[demo] revenue " << rev.totalCollected.toString() << " from "
        << rev.successfulPayments << " payment(s)\n";
    out << "[demo] today " << day.date << ": issued=" << day.ticketsIssued
        << " closed=" << day.ticketsClosed << " revenue=" << day.revenue.toString()
        << "\n";
}

}  // namespace pms
