#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;
#include "show_seat.h"

class Show {
private:
  int id;
  string name;
  string stTime;
  string enTime;
  double duration;
  string date;
  bool active;
  vector<unique_ptr<ShowSeat>> showSeats;

public:
  Show(int id, string name, string stTime, string enTime, double duration,
       string date, bool active = true)
      : id(id), name(name), stTime(stTime), enTime(enTime), date(date),
        duration(duration), active(active) {}

  int getShowId() const { return id; }
  string getStTime() const { return stTime; }
  string getEtTime() const { return enTime; }
  string getShowName() const { return name; }
  bool isActive() const { return active; }

  void changeStatus(bool status) { active = status; }

  void updateShowTiming(string newSt, string newEn) {
    this->stTime = newSt;
    this->enTime = newEn;
  }

  void addShowSeat(Seat *seat, int showSeatId, double price) {
    showSeats.push_back(make_unique<ShowSeat>(showSeatId, seat, price));
  }

  const vector<unique_ptr<ShowSeat>> &getShowSeats() const { return showSeats; }

  vector<ShowSeat *> getAvailableSeats() const {
    vector<ShowSeat *> available;
    for (const auto &ss : showSeats) {
      if (ss->isAvailable())
        available.push_back(ss.get());
    }
    return available;
  }

  string getDate() const { return date; }
  double getDuration() const { return duration; }

  int getAvailableSeatCount() const { return (int)getAvailableSeats().size(); }

  ShowSeat *findShowSeat(int showSeatId) {
    for (auto &ss : showSeats) {
      if (ss->getShowSeatId() == showSeatId)
        return ss.get();
    }
    return nullptr;
  }

  ShowSeat *findShowSeatBySeatId(int physicalSeatId) {
    for (auto &ss : showSeats) {
      if (ss->getSeatId() == physicalSeatId)
        return ss.get();
    }
    return nullptr;
  }

  void printSeatLayout() const {
    cout << "\n  ┌─── Seat Layout for Show: " << name << " (" << stTime << " - " << enTime << ") ───" << endl;
    for (const auto &ss : showSeats) {
      string statusStr;
      if (ss->isAvailable())
        statusStr = "[AVAILABLE]";
      else if (ss->getStatus() == ShowSeatStatus::LOCKED)
        statusStr = "[LOCKED]";
      else
        statusStr = "[BOOKED]";

      cout << "  │  Seat #" << ss->getSeatId()
           << " | Type: " << seatTypeToString(ss->getSeatType())
           << " | Price: Rs." << ss->getPrice()
           << " | Status: " << statusStr << endl;
    }
    cout << "  └────────────────────────────────────────────────────────" << endl;
  }

  virtual ~Show() = default;

  Show(Show &&) = default;
  Show &operator=(Show &&) = default;
};