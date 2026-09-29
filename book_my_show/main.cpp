#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

#include "bms.h"
#include "cinema/cinema.h"
#include "location.h"
#include "screen/screen.h"
#include "seat.h"
#include "seat_type.h"
#include "show/show.h"

int main() {
  cout << "================================================================" << endl;
  cout << "              BOOK MY SHOW - SYSTEM DESIGN DEMO                 " << endl;
  cout << "================================================================" << endl;

  // 1. Setup physical seats with different tiers
  Seat seat1(1, SeatType::BASIC);    // 1x base price
  Seat seat2(2, SeatType::PREMIUM);  // 2x base price
  Seat seat3(3, SeatType::LUXERY);   // 3x base price
  Seat seat4(4, SeatType::LUXERY);   // 3x base price
  Seat seat5(5, SeatType::BASIC);

  // 2. Setup Screens and add seats
  Screen screen1(1, "Hall 1");
  screen1.addSeat(seat1);
  screen1.addSeat(seat2);
  screen1.addSeat(seat3);

  Screen screen2(2, "Hall 2");
  screen2.addSeat(seat4);

  Screen screen3(3, "IMAX Screen");
  screen3.addSeat(seat5);

  // 3. Setup Cinemas and add Screens
  Cinema pvr(1, "PVR Cinemas");
  pvr.addScreen(screen1);
  pvr.addScreen(screen2);

  Cinema cinepolis(2, "Cinepolis");
  cinepolis.addScreen(screen3);

  // 4. Setup Location and add Cinemas
  Location chandigarh(1, "Chandigarh");
  chandigarh.addCinema(pvr);
  chandigarh.addCinema(cinepolis);

  // 5. Initialize BookMyShow system
  BookMyShow bms;
  bms.addLocation(chandigarh);

  // 6. Setup Shows
  Show show1(101, "Oppenheimer", "18:00", "21:00", 3.0, "2026-09-30");
  Show show2(102, "Interstellar", "21:30", "00:15", 2.75, "2026-09-30");

  // Schedule shows on screens (this populates ShowSeat inventory with pricing)
  Screen &activeScreen1 = bms.getLocation(1).getCinema(1).getScreen(1); // PVR -> Hall 1
  activeScreen1.addScreenShow(show1, 200.0); // Base price Rs. 200 (Basic: 200, Premium: 400, Luxury: 600)

  Screen &activeScreen2 = bms.getLocation(1).getCinema(1).getScreen(2); // PVR -> Hall 2
  activeScreen2.addScreenShow(show2, 250.0);

  // ── Display System Hierarchy ──────────────────────────────────
  cout << "\n>>> 1. INITIAL SYSTEM SETUP & HIERARCHY" << endl;
  const vector<unique_ptr<Location>> &locations = bms.getAllLocation();
  for (const auto &loc : locations) {
    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "  Location ID   : " << loc->getLocationId() << " | Name: " << loc->getLocationName() << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;

    const vector<unique_ptr<Cinema>> &cinemas = loc->getAllCinema();
    for (const auto &cin : cinemas) {
      cout << "  ┌── Cinema: " << cin->getCinemaname() << " (ID: " << cin->getCinemaId() << ")" << endl;
      const vector<unique_ptr<Screen>> &screens = cin->getAllScreen();
      for (const auto &scr : screens) {
        cout << "  │  ├─ Screen: " << scr->getScreenName() 
             << " | Seats: " << scr->getTotalSeat() << endl;
      }
      cout << "  │  └──────────────────────────────────────────────────" << endl;
    }
  }

  // ── Show Details & Initial Seat Layout ────────────────────────
  cout << "\n>>> 2. SHOW DETAILS & INITIAL SEAT STATUS FOR 'Oppenheimer'" << endl;
  show1.printSeatLayout();

  // ── Scenario 1: Successful Booking ────────────────────────────
  cout << "\n>>> 3. SCENARIO 1: Aman books Seats [1, 2] for 'Oppenheimer'" << endl;
  try {
    Booking *booking1 = bms.createBooking(
        "Aman Upadhyay", show1, {1, 2},
        "PVR Cinemas", "Hall 1", "Chandigarh"
    );
    cout << "[SUCCESS] Booking created successfully!" << endl;
    booking1->printBookingDetails();
  } catch (const exception &e) {
    cout << "[FAILED] " << e.what() << endl;
  }

  // ── Scenario 2: Booking Conflict (Seat Already Booked) ────────
  cout << "\n>>> 4. SCENARIO 2: Rahul attempts to book conflicting Seats [2, 3]" << endl;
  cout << "    (Seat #2 is already booked by Aman, Seat #3 is available)" << endl;
  try {
    Booking *booking2 = bms.createBooking(
        "Rahul Sharma", show1, {2, 3},
        "PVR Cinemas", "Hall 1", "Chandigarh"
    );
    cout << "[SUCCESS] Booking created successfully!" << endl;
    booking2->printBookingDetails();
  } catch (const exception &e) {
    cout << "[EXPECTED FAILURE] " << e.what() << endl;
  }

  // ── Scenario 3: Rahul books available seat instead ───────────
  cout << "\n>>> 5. SCENARIO 3: Rahul modifies selection to book available Seat [3]" << endl;
  try {
    Booking *booking3 = bms.createBooking(
        "Rahul Sharma", show1, {3},
        "PVR Cinemas", "Hall 1", "Chandigarh"
    );
    cout << "[SUCCESS] Booking created successfully!" << endl;
    booking3->printBookingDetails();
  } catch (const exception &e) {
    cout << "[FAILED] " << e.what() << endl;
  }

  // ── Verify Seat Layout After Bookings ─────────────────────────
  cout << "\n>>> 6. CURRENT SEAT LAYOUT AFTER BOOKINGS" << endl;
  show1.printSeatLayout();

  // ── Scenario 4: Booking Cancellation & Seat Release ──────────
  cout << "\n>>> 7. SCENARIO 4: Aman cancels Booking #1001" << endl;
  try {
    bms.cancelBooking(1001);
    cout << "[SUCCESS] Booking #1001 cancelled successfully! Seats [1, 2] have been released." << endl;
  } catch (const exception &e) {
    cout << "[FAILED] " << e.what() << endl;
  }

  // Verify that seats are released back to AVAILABLE
  cout << "\n>>> 8. SEAT LAYOUT AFTER AMAN'S CANCELLATION" << endl;
  show1.printSeatLayout();

  // ── Scenario 5: Another User Books Newly Released Seat ────────
  cout << "\n>>> 9. SCENARIO 5: Priya books newly freed Seat [2]" << endl;
  try {
    Booking *booking4 = bms.createBooking(
        "Priya Patel", show1, {2},
        "PVR Cinemas", "Hall 1", "Chandigarh"
    );
    cout << "[SUCCESS] Booking created successfully!" << endl;
    booking4->printBookingDetails();
  } catch (const exception &e) {
    cout << "[FAILED] " << e.what() << endl;
  }

  // ── Final Seat Status & Booking Audit ─────────────────────────
  cout << "\n>>> 10. FINAL SEAT LAYOUT" << endl;
  show1.printSeatLayout();

  cout << "\n>>> 11. ALL BOOKINGS IN THE SYSTEM AUDIT" << endl;
  vector<Booking*> allBookings = bms.getAllBookings();
  for (const auto* b : allBookings) {
    cout << "  • ID: #" << b->getBookingId()
         << " | Customer: " << b->getUserName()
         << " | Status: " << bookingStatusToString(b->getStatus())
         << " | Amount: Rs." << b->getTotalAmount() << endl;
  }

  cout << "\n================================================================" << endl;
  cout << "                DEMO COMPLETED SUCCESSFULLY                     " << endl;
  cout << "================================================================" << endl;

  return 0;
}
