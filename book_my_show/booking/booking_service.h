#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
using namespace std;

#include "booking.h"
#include "../show/show.h"

class BookingService {
private:
    int bookingIdCounter = 1000;
    unordered_map<int, unique_ptr<Booking>> bookings;

public:
    BookingService() = default;

    // Create booking by physical seat IDs
    Booking* createBooking(const string& userName, Show& show,
                           const vector<int>& physicalSeatIds,
                           const string& cinemaName = "",
                           const string& hallName = "",
                           const string& locationName = "") {
        if (!show.isActive()) {
            throw runtime_error("Booking failed: Show '" + show.getShowName() + "' is currently inactive.");
        }

        if (physicalSeatIds.empty()) {
            throw runtime_error("Booking failed: No seats specified for booking.");
        }

        // 1. Validate that all requested physical seats exist in this show
        vector<ShowSeat*> selectedSeats;
        for (int seatId : physicalSeatIds) {
            ShowSeat* ss = show.findShowSeatBySeatId(seatId);
            if (!ss) {
                throw runtime_error("Booking failed: Seat #" + to_string(seatId) + " does not exist in show '" + show.getShowName() + "'.");
            }
            selectedSeats.push_back(ss);
        }

        // 2. Atomic check: Validate that ALL selected seats are AVAILABLE
        for (ShowSeat* ss : selectedSeats) {
            if (!ss->isAvailable()) {
                string statusStr = (ss->getStatus() == ShowSeatStatus::BOOKED) ? "BOOKED" : "LOCKED";
                throw runtime_error("Booking failed: Seat #" + to_string(ss->getSeatId()) + " is already " + statusStr + ".");
            }
        }

        // 3. Lock all selected seats (prevent race conditions during payment)
        for (ShowSeat* ss : selectedSeats) {
            ss->lock();
        }

        // 4. Calculate total amount and confirm seats to BOOKED
        double totalAmount = 0.0;
        for (ShowSeat* ss : selectedSeats) {
            totalAmount += ss->getPrice();
            ss->book();
        }

        // 5. Create confirmed Booking record
        int id = ++bookingIdCounter;
        auto booking = make_unique<Booking>(
            id, userName, &show,
            cinemaName, hallName, locationName,
            selectedSeats, totalAmount, BookingStatus::CONFIRMED
        );

        Booking* ptr = booking.get();
        bookings[id] = std::move(booking);
        return ptr;
    }

    // Cancel booking and release seats back to AVAILABLE
    bool cancelBooking(int bookingId) {
        auto it = bookings.find(bookingId);
        if (it == bookings.end()) {
            throw runtime_error("Cancellation failed: No booking found with ID #" + to_string(bookingId));
        }

        Booking* booking = it->second.get();
        if (booking->getStatus() == BookingStatus::CANCELLED) {
            throw runtime_error("Cancellation failed: Booking #" + to_string(bookingId) + " is already cancelled.");
        }

        booking->cancel();
        return true;
    }

    Booking* getBooking(int bookingId) const {
        auto it = bookings.find(bookingId);
        if (it != bookings.end()) {
            return it->second.get();
        }
        return nullptr;
    }

    vector<Booking*> getAllBookings() const {
        vector<Booking*> list;
        for (const auto& pair : bookings) {
            list.push_back(pair.second.get());
        }
        return list;
    }

    vector<Booking*> getBookingsByUser(const string& userName) const {
        vector<Booking*> list;
        for (const auto& pair : bookings) {
            if (pair.second->getUserName() == userName) {
                list.push_back(pair.second.get());
            }
        }
        return list;
    }
};
