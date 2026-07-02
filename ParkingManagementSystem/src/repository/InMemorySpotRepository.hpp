#pragma once

#include <memory>
#include <vector>

#include "repository/ISpotRepository.hpp"

namespace pms {

/**
 * @class InMemorySpotRepository
 * @brief In-memory ISpotRepository — owns the floors (and through them, spots).
 *
 * The reference implementation used in tests and the default runtime. A future
 * SqlSpotRepository / MongoSpotRepository would implement the same interface and
 * drop in with no changes to SpotManager (OCP + Liskov).
 *
 * Ownership: holds floors as unique_ptr — destroying the repository tears down
 * the whole inventory (RAII).
 */
class InMemorySpotRepository : public ISpotRepository {
public:
    void addFloor(std::unique_ptr<ParkingFloor> floor) override;
    std::vector<ParkingFloor*> floors() const override;
    ParkingSpot* findSpotById(const std::string& id) const override;
    std::size_t totalSpots() const override;
    std::size_t availableCount() const override;
    std::size_t occupiedCount() const override;

private:
    std::vector<std::unique_ptr<ParkingFloor>> floors_;
};

}  // namespace pms
