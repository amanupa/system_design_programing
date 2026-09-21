#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

#include "cinema/cinema.h"

class Location {
private:
  int id;
  string name;
  vector<unique_ptr<Cinema>> cinemas;

public:
  Location(int id, string name) : id(id), name(name) {}

  void addCinema(Cinema &cinema) {
    cinemas.push_back(make_unique<Cinema>(std::move(cinema)));
  }

  const vector<unique_ptr<Cinema>> &getAllCinema() const { return cinemas; }

  Cinema &getCinema(int id) const {
    for (auto &cinema : cinemas) {
      if (cinema->getCinemaId() == id) {
        return *cinema;
      }
    }
    throw runtime_error("No cinema found with this id.");
  }

  int getLocationId() const { return id; }

  string getLocationName() const { return name; }

  Location(Location &&) = default;
  Location &operator=(Location &&) = default;
  virtual ~Location() = default;
};