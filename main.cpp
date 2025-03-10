#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// 🟢 User Class
class User {
public:
    int userId;
    string name;
    string contact;

    User(int id, string n, string c) : userId(id), name(n), contact(c) {}
};

// 🟢 Movie Class
class Movie {
public:
    int movieId;
    string title;
    int duration;
    string language;
    float rating;

    Movie(int id, string t, int d, string lang, float r) 
        : movieId(id), title(t), duration(d), language(lang), rating(r) {}
};

// 🟢 Seat Class
class Seat {
public:
    int row, number;
    bool isBooked;

    Seat(int r, int n) : row(r), number(n), isBooked(false) {}

    void bookSeat() { isBooked = true; }
};

// 🟢 Show Class (Represents a Movie Show)
class Show {
public:
    int showId;
    Movie* movie;
    string startTime;
    vector<Seat> seats;

    Show(int id, Movie* m, string time, int rows, int cols) 
        : showId(id), movie(m), startTime(time) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                seats.emplace_back(r, c);
            }
        }
    }

    // Check seat availability
    bool isSeatAvailable(int row, int col) {
        for (Seat &seat : seats) {
            if (seat.row == row && seat.number == col)
                return !seat.isBooked;
        }
        return false;
    }

    // Book a seat
    bool bookSeat(int row, int col) {
        for (Seat &seat : seats) {
            if (seat.row == row && seat.number == col && !seat.isBooked) {
                seat.bookSeat();
                return true;
            }
        }
        return false;
    }
};

// 🟢 Screen Class
class Screen {
public:
    int screenId;
    vector<Show*> shows;

    Screen(int id) : screenId(id) {}

    void addShow(Show* show) {
        shows.push_back(show);
    }
};

// 🟢 Theater Class
class Theater {
public:
    int theaterId;
    string name;
    string city;
    vector<Screen*> screens;

    Theater(int id, string n, string c) : theaterId(id), name(n), city(c) {}

    void addScreen(Screen* screen) {
        screens.push_back(screen);
    }
};

// 🟢 Booking Class
class Booking {
public:
    int bookingId;
    User* user;
    Show* show;
    int seatRow, seatNumber;

    Booking(int id, User* u, Show* s, int row, int col) 
        : bookingId(id), user(u), show(s), seatRow(row), seatNumber(col) {}

    void printBookingDetails() {
        cout << "Booking ID: " << bookingId << endl;
        cout << "User: " << user->name << " (" << user->contact << ")" << endl;
        cout << "Movie: " << show->movie->title << " | Time: " << show->startTime << endl;
        cout << "Seat: Row " << seatRow << ", Number " << seatNumber << endl;
    }
};

// 🟢 Movie Booking System
class MovieBookingSystem {
public:
    vector<User*> users;
    vector<Movie*> movies;
    vector<Theater*> theaters;
    vector<Booking*> bookings;
    int bookingCounter = 1;

    // Add a new user
    User* addUser(int id, string name, string contact) {
        User* user = new User(id, name, contact);
        users.push_back(user);
        return user;
    }

    // Add a new movie
    Movie* addMovie(int id, string title, int duration, string language, float rating) {
        Movie* movie = new Movie(id, title, duration, language, rating);
        movies.push_back(movie);
        return movie;
    }

    // Add a theater
    Theater* addTheater(int id, string name, string city) {
        Theater* theater = new Theater(id, name, city);
        theaters.push_back(theater);
        return theater;
    }

    // Book a ticket
    Booking* bookTicket(User* user, Show* show, int row, int col) {
        if (show->bookSeat(row, col)) {
            Booking* booking = new Booking(bookingCounter++, user, show, row, col);
            bookings.push_back(booking);
            return booking;
        } else {
            cout << "⚠️ Seat is already booked!" << endl;
            return nullptr;
        }
    }
};

// 🟢 Main Function to Test the System
int main() {
    MovieBookingSystem system;

    // Adding Users
    User* user1 = system.addUser(1, "Anamika", "9876543210");

    // Adding Movies
    Movie* movie1 = system.addMovie(1, "Inception", 150, "English", 8.8);

    // Adding Theaters
    Theater* theater1 = system.addTheater(1, "PVR Indore", "Indore");

    // Adding Screens
    Screen* screen1 = new Screen(1);
    theater1->addScreen(screen1);

    // Adding a Show
    Show* show1 = new Show(1, movie1, "6:00 PM", 5, 5);
    screen1->addShow(show1);

    // Booking a Ticket
    Booking* booking1 = system.bookTicket(user1, show1, 2, 3);

    // Printing Booking Details
    if (booking1) {
        cout << "\n✅ Booking Successful!" << endl;
        booking1->printBookingDetails();
    }

    return 0;
}
