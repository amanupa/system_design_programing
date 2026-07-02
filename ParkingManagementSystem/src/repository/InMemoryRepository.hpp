#pragma once

#include <functional>
#include <unordered_map>
#include <utility>

#include "common/exceptions/ParkingException.hpp"
#include "repository/IRepository.hpp"

namespace pms {

/**
 * @class InMemoryRepository
 * @brief Hash-map backed generic IRepository<TEntity, TId>.
 *
 * Header-only because it is a template (definitions must be visible to every
 * instantiation).
 *
 * Key extraction:
 *   The repository is generic, so it cannot assume how to read an entity's id.
 *   A KeyExtractor callable is injected at construction — this keeps the store
 *   fully reusable (composition over a hard-coded `entity.id()` assumption) and
 *   is itself a small Strategy for "how to key an entity".
 *
 * Complexity: add/findById/remove are O(1) average; findAll is O(n).
 */
template <typename TEntity, typename TId>
class InMemoryRepository : public IRepository<TEntity, TId> {
public:
    using KeyExtractor = std::function<TId(const TEntity&)>;

    explicit InMemoryRepository(KeyExtractor keyOf) : keyOf_(std::move(keyOf)) {
        if (!keyOf_) {
            throw InvalidArgumentException("InMemoryRepository: key extractor is null");
        }
    }

    void add(std::shared_ptr<TEntity> entity) override {
        if (!entity) {
            throw InvalidArgumentException("InMemoryRepository::add: entity is null");
        }
        items_[keyOf_(*entity)] = std::move(entity);
    }

    std::shared_ptr<TEntity> findById(const TId& id) const override {
        const auto it = items_.find(id);
        return it == items_.end() ? nullptr : it->second;
    }

    std::vector<std::shared_ptr<TEntity>> findAll() const override {
        std::vector<std::shared_ptr<TEntity>> all;
        all.reserve(items_.size());
        for (const auto& [id, entity] : items_) {
            all.push_back(entity);
        }
        return all;
    }

    bool remove(const TId& id) override { return items_.erase(id) > 0; }

    std::size_t count() const override { return items_.size(); }

private:
    KeyExtractor keyOf_;
    std::unordered_map<TId, std::shared_ptr<TEntity>> items_;
};

}  // namespace pms
