#pragma once
#include "../seat.h"
#include "show_seat_status.h"

// ShowSeat represents a physical Seat's booking state for ONE specific Show.
// A Screen with 100 seats will generate 100 ShowSeats per Show it runs.
// This lets the same physical seat be booked independently across different
// shows.
class ShowSeat {
private:
  int showSeatId;
  Seat *seat;
  ShowSeatStatus status;
  double price;

public:
  ShowSeat(int showSeatId, Seat *seat, double price)
      : showSeatId(showSeatId), seat(seat), status(ShowSeatStatus::AVAILABLE),
        price(price) {}

  int getShowSeatId() const { return showSeatId; }

  int getSeatId() const { return seat->id; }

  SeatType getSeatType() const { return seat->type; }

  ShowSeatStatus getStatus() const { return status; }

  double getPrice() const { return price; }

  bool isAvailable() const { return status == ShowSeatStatus::AVAILABLE; }
  bool isLocked() const { return status == ShowSeatStatus::LOCKED; }
  bool isBooked() const { return status == ShowSeatStatus::BOOKED; }

  void lock() {
    if (status == ShowSeatStatus::AVAILABLE)
      status = ShowSeatStatus::LOCKED;
  }

  void book() { status = ShowSeatStatus::BOOKED; }

  void release() {
    if (status == ShowSeatStatus::LOCKED || status == ShowSeatStatus::BOOKED)
      status = ShowSeatStatus::AVAILABLE;
  }

  virtual ~ShowSeat() = default;
};
