#include "facade/ParkingLot.hpp"

#include <iomanip>
#include <sstream>
#include <utility>

#include "common/exceptions/ParkingException.hpp"
#include "common/util/Time.hpp"
#include "config/ConfigTypes.hpp"
#include "display/AvailabilityBoard.hpp"
#include "display/ElectricBoard.hpp"
#include "display/VipBoard.hpp"
#include "domain/floor/ParkingFloor.hpp"
#include "strategy/BestFitStrategy.hpp"
#include "strategy/VipPriorityStrategy.hpp"
#include "strategy/fee/FeeStrategyFactory.hpp"
#include "strategy/payment/CardPayment.hpp"
#include "strategy/payment/CashPayment.hpp"
#include "strategy/payment/UpiPayment.hpp"

namespace pms {

namespace {

/// Short code per spot type for readable spot ids ("F1-CR-001").
std::string spotPrefix(SpotType type) {
    switch (type) {
        case SpotType::Bike:        return "BK";
        case SpotType::Compact:     return "CP";
        case SpotType::Car:         return "CR";
        case SpotType::Large:       return "LG";
        case SpotType::Truck:       return "TR";
        case SpotType::Electric:    return "EV";
        case SpotType::Vip:         return "VP";
        case SpotType::Handicapped: return "HC";
    }
    return "SP";
}

std::string pad3(int n) {
    std::ostringstream out;
    out << std::setw(3) << std::setfill('0') << n;
    return out.str();
}

}  // namespace

std::unique_ptr<ISpotAllocationStrategy> ParkingLot::makeAllocationStrategy() {
    // Default policy: VIP rules layered over best-fit (Decorator over Strategy).
    return std::make_unique<VipPriorityStrategy>(std::make_unique<BestFitStrategy>());
}

ParkingLot::ParkingLot(const ParkingLotConfig& config, ILogger& logger,
                       IClock& clock, IIdGenerator& idGenerator)
    : name_(config.name()),
      logger_(logger),
      clock_(clock),
      idGenerator_(idGenerator),
      config_(config),
      spotFactory_(SpotFactory::createDefault()),
      vehicleFactory_(VehicleFactory::createDefault()),
      gateFactory_(GateFactory::createDefault()),
      spotRepository_(),
      ticketRepository_(),
      paymentRepository_(),
      spotManager_(spotRepository_, makeAllocationStrategy(), logger_),
      ticketManager_(ticketRepository_, clock_, idGenerator_, logger_),
      feeCalculator_(FeeStrategyFactory::build(config.pricing()), logger_),
      paymentManager_(paymentRepository_, idGenerator_, clock_, logger_),
      gateManager_(logger_),
      displayManager_(spotManager_.events(), logger_),
      parkingService_(spotManager_, ticketManager_, feeCalculator_, paymentManager_,
                      clock_, logger_),
      statisticsService_(spotRepository_, ticketRepository_, paymentRepository_) {
    buildInventory();
    buildGates();
    registerPaymentStrategies();
    buildDisplays();
    logger_.info("ParkingLot '" + name_ + "' assembled: " +
                 std::to_string(totalSpots()) + " spots, " +
                 std::to_string(config_.gateCount()) + " gates, fee policy " +
                 feeCalculator_.strategyName());
}

void ParkingLot::buildInventory() {
    for (const FloorConfig& floorConfig : config_.floors()) {
        auto floor = std::make_unique<ParkingFloor>(floorConfig.floorNumber);
        for (const auto& [type, count] : floorConfig.spotCounts) {
            for (int i = 1; i <= count; ++i) {
                const std::string id = "F" + std::to_string(floorConfig.floorNumber) +
                                       "-" + spotPrefix(type) + "-" + pad3(i);
                floor->addSpot(spotFactory_.create(type, id, floorConfig.floorNumber));
            }
        }
        spotRepository_.addFloor(std::move(floor));
    }
}

void ParkingLot::buildGates() {
    for (const GateConfig& gateConfig : config_.gates()) {
        gateManager_.addGate(gateFactory_.create(gateConfig.type, gateConfig.id));
    }
}

void ParkingLot::registerPaymentStrategies() {
    paymentManager_.registerStrategy(std::make_unique<CashPayment>());
    paymentManager_.registerStrategy(std::make_unique<CardPayment>());
    paymentManager_.registerStrategy(std::make_unique<UpiPayment>());
}

void ParkingLot::buildDisplays() {
    displayManager_.addBoard(std::make_unique<AvailabilityBoard>(logger_));
    displayManager_.addBoard(std::make_unique<VipBoard>(logger_));
    displayManager_.addBoard(std::make_unique<ElectricBoard>(logger_));
}

std::shared_ptr<Ticket> ParkingLot::parkVehicle(const std::string& entryGateId,
                                                VehicleType type,
                                                const std::string& plate) {
    std::shared_ptr<const Vehicle> vehicle = vehicleFactory_.create(type, plate);
    IEntryGate& gate = gateManager_.requireEntryGate(entryGateId);
    return parkingService_.parkVehicle(gate, std::move(vehicle));
}

ExitReceipt ParkingLot::exitVehicle(const std::string& exitGateId,
                                    const std::string& ticketId,
                                    PaymentMethod method) {
    IExitGate& gate = gateManager_.requireExitGate(exitGateId);
    return parkingService_.exitVehicle(gate, ticketId, method);
}

std::string ParkingLot::today() const { return toDateString(clock_.now()); }

std::vector<std::string> ParkingLot::gateSummaries() const {
    std::vector<std::string> summaries;
    for (Gate* gate : gateManager_.listGates()) {
        summaries.push_back(gate->id() + " (" + toString(gate->type()) + ", " +
                            toString(gate->status()) + ")");
    }
    return summaries;
}

void ParkingLot::enableGate(const std::string& id) { gateManager_.enableGate(id); }
void ParkingLot::disableGate(const std::string& id) { gateManager_.disableGate(id); }
void ParkingLot::sendGateToMaintenance(const std::string& id) {
    gateManager_.sendToMaintenance(id);
}

}  // namespace pms
