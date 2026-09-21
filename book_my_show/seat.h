#pragma once
#include "seat_type.h"
class Seat {
public:
  int id;
  SeatType type;

  Seat(int id, SeatType type) : id(id), type(type) {}

  SeatType getSeatType() const { return type; }

  int getSeatId() const { return id; }

  virtual ~Seat() = default;
};