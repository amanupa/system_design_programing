#include "service/StatisticsService.hpp"

#include "common/enums/PaymentStatus.hpp"
#include "common/util/Time.hpp"
#include "domain/floor/ParkingFloor.hpp"
#include "domain/payment/Payment.hpp"
#include "domain/ticket/Ticket.hpp"

namespace pms {

StatisticsService::StatisticsService(
    const ISpotRepository& spotRepository,
    const ITicketRepository& ticketRepository,
    const IPaymentRepository& paymentRepository) noexcept
    : spotRepository_(spotRepository),
      ticketRepository_(ticketRepository),
      paymentRepository_(paymentRepository) {}

OccupancyStats StatisticsService::occupancy() const {
    OccupancyStats stats;
    stats.totalSpots = spotRepository_.totalSpots();
    stats.occupiedSpots = spotRepository_.occupiedCount();
    stats.availableSpots = spotRepository_.availableCount();
    stats.occupancyPercent =
        stats.totalSpots == 0
            ? 0.0
            : (static_cast<double>(stats.occupiedSpots) /
               static_cast<double>(stats.totalSpots)) * 100.0;
    return stats;
}

RevenueStats StatisticsService::revenue() const {
    RevenueStats stats;
    for (const std::shared_ptr<Payment>& payment : paymentRepository_.findAll()) {
        switch (payment->status()) {
            case PaymentStatus::Success:
                stats.totalCollected = stats.totalCollected + payment->amount();
                ++stats.successfulPayments;
                break;
            case PaymentStatus::Failed:
                ++stats.failedPayments;
                break;
            case PaymentStatus::Refunded:
                ++stats.refundedPayments;
                break;
            case PaymentStatus::Pending:
                break;
        }
    }
    return stats;
}

TicketStats StatisticsService::tickets() const {
    TicketStats stats;
    stats.total = ticketRepository_.count();
    stats.active = ticketRepository_.activeTickets().size();
    stats.closed = stats.total - stats.active;
    return stats;
}

DailyReport StatisticsService::dailyReport(const std::string& date) const {
    DailyReport report;
    report.date = date;
    for (const std::shared_ptr<Ticket>& ticket : ticketRepository_.findAll()) {
        if (toDateString(ticket->entryTime()) == date) {
            ++report.ticketsIssued;
        }
        if (ticket->exitTime().has_value() &&
            toDateString(*ticket->exitTime()) == date) {
            ++report.ticketsClosed;
        }
    }
    for (const std::shared_ptr<Payment>& payment : paymentRepository_.findAll()) {
        if (payment->isSuccessful() &&
            toDateString(payment->timestamp()) == date) {
            report.revenue = report.revenue + payment->amount();
        }
    }
    return report;
}

std::vector<std::pair<int, std::size_t>> StatisticsService::occupiedByFloor()
    const {
    std::vector<std::pair<int, std::size_t>> result;
    for (ParkingFloor* floor : spotRepository_.floors()) {
        result.emplace_back(floor->floorNumber(), floor->occupiedCount());
    }
    return result;
}

}  // namespace pms
