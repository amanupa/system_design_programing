#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "common/util/Money.hpp"
#include "repository/IPaymentRepository.hpp"
#include "repository/ISpotRepository.hpp"
#include "repository/ITicketRepository.hpp"

namespace pms {

struct OccupancyStats {
    std::size_t totalSpots = 0;
    std::size_t occupiedSpots = 0;
    std::size_t availableSpots = 0;
    double occupancyPercent = 0.0;
};

struct RevenueStats {
    Money totalCollected = Money::zero();  // sum of successful (non-refunded) payments
    std::size_t successfulPayments = 0;
    std::size_t failedPayments = 0;
    std::size_t refundedPayments = 0;
};

struct TicketStats {
    std::size_t total = 0;
    std::size_t active = 0;
    std::size_t closed = 0;
};

struct DailyReport {
    std::string date;
    std::size_t ticketsIssued = 0;
    std::size_t ticketsClosed = 0;
    Money revenue = Money::zero();
};

/**
 * @class StatisticsService
 * @brief Read-only analytics over the lot's repositories.
 *
 * Injected with CONST references to the repository interfaces, so it can query
 * but is structurally unable to mutate state — read-only enforced by the type
 * system, not convention.
 *
 * SOLID: SRP (reporting only), DIP (depends on repo abstractions), ISP (uses
 * just the const query surface).
 */
class StatisticsService {
public:
    StatisticsService(const ISpotRepository& spotRepository,
                      const ITicketRepository& ticketRepository,
                      const IPaymentRepository& paymentRepository) noexcept;

    OccupancyStats occupancy() const;
    RevenueStats revenue() const;
    TicketStats tickets() const;
    DailyReport dailyReport(const std::string& date) const;

    /// (floorNumber, occupiedSpots) per floor — useful for "busiest floor".
    std::vector<std::pair<int, std::size_t>> occupiedByFloor() const;

private:
    const ISpotRepository& spotRepository_;
    const ITicketRepository& ticketRepository_;
    const IPaymentRepository& paymentRepository_;
};

}  // namespace pms
