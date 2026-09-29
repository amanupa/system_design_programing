#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

#include "show.h"

class ShowServices {
private:
  vector<unique_ptr<Show>> shows;

public:
  ShowServices() = default;

  void addShow(Show show) {
    shows.push_back(make_unique<Show>(std::move(show)));
  }

  const vector<unique_ptr<Show>> &getAllShows() const { return shows; }

  Show &getShow(int showId) {
    for (auto &show : shows) {
      if (show->getShowId() == showId) {
        return *show;
      }
    }
    throw runtime_error("Show not found");
  }

  void updateShowTiming(int id, string stTime, string enTime) {
    for (auto &show : shows) {
      if (show->getShowId() == id) {
        show->updateShowTiming(stTime, enTime);
        return;
      }
    }
  }

  void changeStatus(int id, bool newStatus) {
    for (auto &show : shows) {
      if (show->getShowId() == id) {
        cout << "Current Show Status is: " << show->isActive() << endl;
        show->changeStatus(newStatus);
        cout << "new show status is: " << show->isActive() << endl;
      }
    }
  }
};
