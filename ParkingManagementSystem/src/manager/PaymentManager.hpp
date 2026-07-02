#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/enums/PaymentMethod.hpp"
#include "common/logging/ILogger.hpp"
#include "common/util/IClock.hpp"
#include "common/util/IIdGenerator.hpp"
#include "common/util/Money.hpp"
#include "domain/payment/Payment.hpp"
#include "repository/IPaymentRepository.hpp"
#include "strategy/payment/IPaymentStrategy.hpp"

namespace pms {

/**
 * @class PaymentManager
 * @brief Settles fees through registered channel strategies and records them.
 *
 * Holds a registry of IPaymentStrategy keyed by method (a small Strategy-lookup,
 * like the factories). process() selects the channel, runs it, persists a
 * Payment record either way (audit), and throws on failure so the caller cannot
 * proceed as if paid.
 *
 * Collaborators (injected — DI): IPaymentRepository&, IIdGenerator&, IClock&,
 * ILogger&. Owns the strategies via unique_ptr.
 *
 * SOLID: SRP, OCP (register new channels), DIP.
 */
class PaymentManager {
public:
    PaymentManager(IPaymentRepository& repository, IIdGenerator& idGenerator,
                   IClock& clock, ILogger& logger);

    PaymentManager(const PaymentManager&) = delete;
    PaymentManager& operator=(const PaymentManager&) = delete;

    /// Register (or replace) the strategy for its declared method.
    void registerStrategy(std::unique_ptr<IPaymentStrategy> strategy);

    /**
     * Settle `amount` for `ticketId` via `method`.
     * @returns the (successful) Payment record.
     * @throws InvalidArgumentException if no strategy is registered for method.
     * @throws PaymentFailedException   if the channel declines (record still saved).
     */
    std::shared_ptr<Payment> process(const std::string& ticketId,
                                     const Money& amount, PaymentMethod method);

    /**
     * Refund a successful payment.
     * @throws TicketNotFoundException-like InvalidArgumentException if unknown,
     *         or if the payment is not currently successful.
     */
    std::shared_ptr<Payment> refund(const std::string& paymentId);

    std::shared_ptr<Payment> findPayment(const std::string& paymentId) const;
    std::vector<std::shared_ptr<Payment>> paymentsForTicket(
        const std::string& ticketId) const;

private:
    IPaymentStrategy& requireStrategy(PaymentMethod method) const;

    IPaymentRepository& repository_;
    IIdGenerator& idGenerator_;
    IClock& clock_;
    ILogger& logger_;
    std::unordered_map<PaymentMethod, std::unique_ptr<IPaymentStrategy>> strategies_;
};

}  // namespace pms
