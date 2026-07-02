#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "common/enums/PaymentMethod.hpp"
#include "common/enums/VehicleType.hpp"
#include "common/logging/ILogger.hpp"
#include "common/util/IClock.hpp"
#include "common/util/IIdGenerator.hpp"
#include "config/ParkingLotConfig.hpp"
#include "display/DisplayManager.hpp"
#include "domain/ticket/Ticket.hpp"
#include "factory/GateFactory.hpp"
#include "factory/SpotFactory.hpp"
#include "factory/VehicleFactory.hpp"
#include "manager/FeeCalculator.hpp"
#include "manager/GateManager.hpp"
#include "manager/PaymentManager.hpp"
#include "manager/SpotManager.hpp"
#include "manager/TicketManager.hpp"
#include "repository/InMemoryPaymentRepository.hpp"
#include "repository/InMemorySpotRepository.hpp"
#include "repository/InMemoryTicketRepository.hpp"
#include "service/ParkingService.hpp"
#include "service/StatisticsService.hpp"
#include "strategy/ISpotAllocationStrategy.hpp"

namespace pms {

/**
 * @class ParkingLot
 * @brief Facade + composition root for the whole system.
 *
 * Constructs and OWNS the entire object graph from a ParkingLotConfig, then
 * exposes a minimal surface (park, exit, status, gate admin). Clients deal only
 * with this class — they never see managers, repositories, or strategies (Law of
 * Demeter; Facade).
 *
 * Deliberately NOT a Singleton: a single instance is created in the composition
 * root and injected. That keeps it testable (tests build isolated lots) and
 * dependency-explicit, which a global Singleton would sacrifice.
 *
 * Member order mirrors dependency order so RAII builds and tears down the graph
 * correctly (e.g. DisplayManager is declared after SpotManager, so it
 * unsubscribes its boards before the event publisher is destroyed).
 *
 * SOLID: Facade simplifies; the lot still depends on abstractions (logger,
 * clock, id-gen) injected via the constructor (DIP).
 */
class ParkingLot {
public:
    ParkingLot(const ParkingLotConfig& config, ILogger& logger, IClock& clock,
               IIdGenerator& idGenerator);

    ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;

    // --- Use-cases -----------------------------------------------------------
    std::shared_ptr<Ticket> parkVehicle(const std::string& entryGateId,
                                        VehicleType type, const std::string& plate);
    ExitReceipt exitVehicle(const std::string& exitGateId,
                            const std::string& ticketId, PaymentMethod method);

    // --- Gate administration -------------------------------------------------
    void enableGate(const std::string& id);
    void disableGate(const std::string& id);
    void sendGateToMaintenance(const std::string& id);

    // --- Status --------------------------------------------------------------
    const std::string& name() const noexcept { return name_; }
    std::size_t totalSpots() const { return spotManager_.totalSpots(); }
    std::size_t availableSpots() const { return spotManager_.availableCount(); }
    std::size_t activeTicketCount() const { return ticketManager_.activeCount(); }
    std::string feeStrategyName() const { return feeCalculator_.strategyName(); }

    /// One "id (type, status)" line per gate — so the UI can show valid ids.
    std::vector<std::string> gateSummaries() const;

    // --- Reporting -----------------------------------------------------------
    OccupancyStats occupancy() const { return statisticsService_.occupancy(); }
    RevenueStats revenue() const { return statisticsService_.revenue(); }
    TicketStats ticketStats() const { return statisticsService_.tickets(); }
    DailyReport dailyReport(const std::string& date) const {
        return statisticsService_.dailyReport(date);
    }
    /// Today's UTC date ("YYYY-MM-DD") from the injected clock.
    std::string today() const;

private:
    void buildInventory();
    void buildGates();
    void registerPaymentStrategies();
    void buildDisplays();
    static std::unique_ptr<ISpotAllocationStrategy> makeAllocationStrategy();

    std::string name_;
    ILogger& logger_;
    IClock& clock_;
    IIdGenerator& idGenerator_;
    const ParkingLotConfig& config_;

    SpotFactory spotFactory_;
    VehicleFactory vehicleFactory_;
    GateFactory gateFactory_;

    InMemorySpotRepository spotRepository_;
    InMemoryTicketRepository ticketRepository_;
    InMemoryPaymentRepository paymentRepository_;

    SpotManager spotManager_;
    TicketManager ticketManager_;
    FeeCalculator feeCalculator_;
    PaymentManager paymentManager_;
    GateManager gateManager_;
    DisplayManager displayManager_;
    ParkingService parkingService_;
    StatisticsService statisticsService_;
};

}  // namespace pms
