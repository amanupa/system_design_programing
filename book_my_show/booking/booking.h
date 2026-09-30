#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#include "booking_status.h"
#include "../show/show.h"
#include "../show/show_seat.h"

class Booking {
private:
    int bookingId;
    string userName;
    Show* show;
    string cinemaName;
    string hallName;
    string locationName;
    vector<ShowSeat*> bookedSeats;
    double totalAmount;
    BookingStatus status;

public:
    Booking(int bookingId, const string& userName, Show* show,
            const string& cinemaName, const string& hallName, const string& locationName,
            const vector<ShowSeat*>& seats, double totalAmount,
            BookingStatus status = BookingStatus::CONFIRMED)
        : bookingId(bookingId), userName(userName), show(show),
          cinemaName(cinemaName), hallName(hallName), locationName(locationName),
          bookedSeats(seats), totalAmount(totalAmount), status(status) {}

    int getBookingId() const { return bookingId; }
    string getUserName() const { return userName; }
    Show* getShow() const { return show; }
    string getCinemaName() const { return cinemaName; }
    string getHallName() const { return hallName; }
    string getLocationName() const { return locationName; }
    const vector<ShowSeat*>& getBookedSeats() const { return bookedSeats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }

    void confirm() {
        status = BookingStatus::CONFIRMED;
        for (auto* seat : bookedSeats) {
            seat->book();
        }
    }

    void cancel() {
        if (status == BookingStatus::CANCELLED) return;
        status = BookingStatus::CANCELLED;
        for (auto* seat : bookedSeats) {
            seat->release();
        }
    }

    void printBookingDetails() const {
        cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
        cout << "║                 BOOKING TICKET CONFIRMATION              ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════╣" << endl;
        cout << "  Booking ID   : #" << bookingId << endl;
        cout << "  Customer     : " << userName << endl;
        cout << "  Status       : " << bookingStatusToString(status) << endl;
        if (show) {
            cout << "  Movie        : " << show->getShowName() << endl;
            cout << "  Date & Time  : " << show->getDate() << " (" << show->getStTime() << " - " << show->getEtTime() << ")" << endl;
        }
        cout << "  Location     : " << locationName << endl;
        cout << "  Cinema       : " << cinemaName << endl;
        cout << "  Screen/Hall  : " << hallName << endl;
        cout << "  Seats (" << bookedSeats.size() << ")      :" << endl;
        for (const auto* ss : bookedSeats) {
            cout << "    • Seat #" << ss->getSeatId()
                 << " [" << seatTypeToString(ss->getSeatType()) << "]"
                 << " - Rs." << fixed << setprecision(2) << ss->getPrice() << endl;
        }
        cout << "  ──────────────────────────────────────────────────────────" << endl;
        cout << "  Total Amount : Rs." << fixed << setprecision(2) << totalAmount << endl;
        cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    }

    virtual ~Booking() = default;
};