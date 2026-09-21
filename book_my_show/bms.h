#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

#include "location.h"

class BookMyShow {
private:
  vector<unique_ptr<Location>> locations;

public:
  BookMyShow() {}

  void addLocation(Location &location) {
    locations.push_back(make_unique<Location>(std::move(location)));
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
    throw runtime_error("NO location found with this id.");
  }

  BookMyShow(BookMyShow &&) = default;
  BookMyShow &operator=(BookMyShow &&) = default;
  virtual ~BookMyShow() = default;
};