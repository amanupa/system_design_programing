#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "../seat.h"
#include "../show/show.h"

class Screen {
private:
  int id;
  string name;
  vector<Show *> screenShows;
  vector<unique_ptr<Seat>> seats;
  int showSeatIdCounter = 0;

public:
  Screen(int id, string name) : id(id), name(name) {}

  void addSeat(Seat &seat) {
    seats.push_back(make_unique<Seat>(std::move(seat)));
  }

  // Schedule a show in this screen.
  // This creates one ShowSeat per physical seat, linked to this show.
  // So the same screen can run 5 shows and each has 100 independent ShowSeats.
  void addScreenShow(Show &show, double defaultPrice = 200.0) {
    screenShows.push_back(&show);
    for (auto &seat : seats) {
      double price = defaultPrice;
      if (seat->getSeatType() == SeatType::PREMIUM) {
        price *= 2;
      }
      if (seat->getSeatType() == SeatType::LUXERY) {
        price *= 3;
      }
      show.addShowSeat(seat.get(), ++showSeatIdCounter, price);
    }
  }

  int getTotalSeat() const { return seats.size(); }

  vector<Show *> getScreenShows() const { return screenShows; }

  string getScreenName() const { return name; }

  int getScreenId() const { return id; }

  Screen(Screen &&) = default;
  Screen &operator=(Screen &&) = default;
  virtual ~Screen() = default;
};