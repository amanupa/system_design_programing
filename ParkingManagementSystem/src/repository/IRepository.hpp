#pragma once

#include <cstddef>
#include <memory>
#include <vector>

namespace pms {

/**
 * @class IRepository
 * @brief Generic CRUD storage contract for an aggregate of type T keyed by Id.
 *
 * Reusable persistence abstraction shared by every entity store (tickets now,
 * payments later) so the storage contract is defined exactly once (DRY). Domain
 * code depends on this interface, never on a concrete container or database —
 * the Repository pattern in service of Dependency Inversion.
 *
 * Entities are held by shared_ptr because they are referenced from multiple
 * places (e.g. a ticket is in the repo and also handed to a caller/history).
 *
 * SOLID: SRP (storage only), DIP, OCP (new backends = new implementations).
 */
template <typename TEntity, typename TId>
class IRepository {
public:
    virtual ~IRepository() = default;

    /// Insert or replace the entity (keyed by its extracted id).
    virtual void add(std::shared_ptr<TEntity> entity) = 0;

    /// Find by id, or nullptr if absent.
    virtual std::shared_ptr<TEntity> findById(const TId& id) const = 0;

    /// Snapshot of all stored entities.
    virtual std::vector<std::shared_ptr<TEntity>> findAll() const = 0;

    /// Remove by id; returns true if something was removed.
    virtual bool remove(const TId& id) = 0;

    virtual std::size_t count() const = 0;
};

}  // namespace pms
