#include <iostream>
#include <memory>
#include <string>
using namespace std;

#include "bms.h"
#include "cinema/cinema.h"
#include "location.h"
#include "screen/screen.h"
#include "seat.h"
#include "seat_type.h"
#include "show/show.h"

int main() {
  // seats
  Seat seat1 = Seat(1, SeatType::LUXERY);
  Seat seat2 = Seat(2, SeatType::LUXERY);

  Seat seat3 = Seat(3, SeatType::LUXERY);
  Seat seat4 = Seat(4, SeatType::LUXERY);

  Seat seat5 = Seat(5, SeatType::LUXERY);

  // location
  Location chandigarh = Location(1, "Chandigarh");

  // cinemas
  Cinema pvr = Cinema(1, "PVR");
  Cinema cinePolis = Cinema(2, "CinePolis");

  // Screens
  Screen screen1 = Screen(1, "Hall1");
  Screen screen2 = Screen(2, "Hall2");

  Screen screen3 = Screen(3, "Hall1");

  screen1.addSeat(seat1);
  screen1.addSeat(seat2);

  screen2.addSeat(seat3);
  screen2.addSeat(seat4);

  screen3.addSeat(seat5);

  // Cinema Screen

  pvr.addScreen(screen1);
  pvr.addScreen(screen2);

  cinePolis.addScreen(screen3);

  // Location Cinema
  chandigarh.addCinema(pvr);
  chandigarh.addCinema(cinePolis);

  BookMyShow bms = BookMyShow();
  bms.addLocation(chandigarh);

  // functionalities

  // get all Location  cinemas and screens
  const vector<unique_ptr<Location>> &locations = bms.getAllLocation();
  for (auto &it : locations) {
    cout << "======================================" << endl;
    cout << "Location ID:" << it->getLocationId() << endl;
    cout << "Location Name" << it->getLocationName() << endl;
    // ── Locations ──────────────────────────────────────────────
    const vector<unique_ptr<Location>> &locations = bms.getAllLocation();
    for (auto &loc : locations) {
      cout << "\n╔══════════════════════════════════════╗" << endl;
      cout << "  Location ID   : " << loc->getLocationId() << endl;
      cout << "  Location Name : " << loc->getLocationName() << endl;
      cout << "╚══════════════════════════════════════╝" << endl;
      // ── Cinemas at this Location ────────────────────────────
      const vector<unique_ptr<Cinema>> &cinemas = loc->getAllCinema();
      if (cinemas.empty()) {
        cout << "  [No cinemas at this location]" << endl;
        continue;
      }
      for (auto &cin : cinemas) {
        cout << "\n  ┌─── Cinema ───────────────────────────" << endl;
        cout << "  │  Cinema ID   : " << cin->getCinemaId() << endl;
        cout << "  │  Cinema Name : " << cin->getCinemaname() << endl;
        // ── Screens in this Cinema ──────────────────────────
        const vector<unique_ptr<Screen>> &screens = cin->getAllScreen();
        if (screens.empty()) {
          cout << "  │  [No screens in this cinema]" << endl;
        }
        for (auto &scr : screens) {
          cout << "  │" << endl;
          cout << "  │  ┌─ Screen ──────────────────────────" << endl;
          cout << "  │  │  Screen ID    : " << scr->getScreenId() << endl;
          cout << "  │  │  Screen Name  : " << scr->getScreenName() << endl;
          cout << "  │  │  Total Seats  : " << scr->getTotalSeat() << endl;
          cout << "  │  └───────────────────────────────────" << endl;
        }
        cout << "  └──────────────────────────────────────" << endl;
      }
    }
  }
}
