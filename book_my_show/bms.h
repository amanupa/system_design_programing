#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

#include "location.h"
#include "booking/booking_service.h"

class BookMyShow {
private:
  vector<unique_ptr<Location>> locations;
  BookingService bookingService;

public:
  BookMyShow() = default;

  void addLocation(unique_ptr<Location> location) {
    locations.push_back(std::move(location));
  }

  const vector<unique_ptr<Location>> &getAllLocation() const {
    return locations;
  }

  Location &getLocation(int id) const {
    for (auto &location : locations) {
      if (location->getLocationId() == id) {
        return *location;
      }
    }
    throw runtime_error("No location found with this id.");
  }

  BookingService &getBookingService() { return bookingService; }
  const BookingService &getBookingService() const { return bookingService; }

  //convenience methods for booking operations
  Booking *createBooking(const string &userName, Show &show,
                         const vector<int> &physicalSeatIds,
                         const string &cinemaName = "",
                         const string &hallName = "",
                         const string &locationName = "") {
    return bookingService.createBooking(userName, show, physicalSeatIds, cinemaName,
                                        hallName, locationName);
  }

  bool cancelBooking(int bookingId) {
    return bookingService.cancelBooking(bookingId);
  }

  Booking *getBooking(int bookingId) const {
    return bookingService.getBooking(bookingId);
  }

  vector<Booking*> getAllBookings() const {
    return bookingService.getAllBookings();
  }

  vector<Booking*> getBookingsByUser(const string &userName) const {
    return bookingService.getBookingsByUser(userName);
  }

  BookMyShow(BookMyShow &&) = default;
  BookMyShow &operator=(BookMyShow &&) = default;
  virtual ~BookMyShow() = default;
};