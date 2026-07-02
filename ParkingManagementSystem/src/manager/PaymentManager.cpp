#include "manager/PaymentManager.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

PaymentManager::PaymentManager(IPaymentRepository& repository,
                               IIdGenerator& idGenerator, IClock& clock,
                               ILogger& logger)
    : repository_(repository),
      idGenerator_(idGenerator),
      clock_(clock),
      logger_(logger) {}

void PaymentManager::registerStrategy(std::unique_ptr<IPaymentStrategy> strategy) {
    if (!strategy) {
        throw InvalidArgumentException("PaymentManager: strategy must not be null");
    }
    const PaymentMethod method = strategy->method();
    strategies_[method] = std::move(strategy);
}

IPaymentStrategy& PaymentManager::requireStrategy(PaymentMethod method) const {
    const auto it = strategies_.find(method);
    if (it == strategies_.end()) {
        throw InvalidArgumentException(
            "PaymentManager: no strategy registered for method " + toString(method));
    }
    return *it->second;
}

std::shared_ptr<Payment> PaymentManager::process(const std::string& ticketId,
                                                 const Money& amount,
                                                 PaymentMethod method) {
    IPaymentStrategy& strategy = requireStrategy(method);
    const PaymentResult result = strategy.pay(amount);

    auto payment = std::make_shared<Payment>(
        idGenerator_.nextId("PAY"), ticketId, amount, method,
        result.success ? PaymentStatus::Success : PaymentStatus::Failed,
        result.reference, clock_.now());
    repository_.add(payment);  // persist the attempt regardless of outcome

    if (!result.success) {
        logger_.warn("Payment " + payment->id() + " for ticket " + ticketId +
                     " FAILED via " + toString(method) + ": " + result.message);
        throw PaymentFailedException("Payment " + payment->id() + " failed: " +
                                     result.message);
    }
    logger_.info("Payment " + payment->id() + " of " + amount.toString() +
                 " for ticket " + ticketId + " via " + toString(method) +
                 " succeeded (" + payment->reference() + ")");
    return payment;
}

std::shared_ptr<Payment> PaymentManager::refund(const std::string& paymentId) {
    std::shared_ptr<Payment> payment = repository_.findById(paymentId);
    if (!payment) {
        throw InvalidArgumentException("Unknown payment id: " + paymentId);
    }
    payment->markRefunded();
    logger_.info("Refunded payment " + paymentId + " (" + payment->amount().toString() +
                 ")");
    return payment;
}

std::shared_ptr<Payment> PaymentManager::findPayment(
    const std::string& paymentId) const {
    return repository_.findById(paymentId);
}

std::vector<std::shared_ptr<Payment>> PaymentManager::paymentsForTicket(
    const std::string& ticketId) const {
    return repository_.findByTicketId(ticketId);
}

}  // namespace pms
