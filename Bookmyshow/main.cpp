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
    unordered_map<int, User*> userMap;
    unordered_map<int, Movie*> movieMap;
    unordered_map<int, Theater*> theaterMap;
    unordered_map<int, Show*> showMap;
    
    int choice;
    while (true) {
        cout << "\n===== Movie Booking System =====" << endl;
        cout << "1. Add User" << endl;
        cout << "2. Add Movie" << endl;
        cout << "3. Add Theater & Screen" << endl;
        cout << "4. Add Show" << endl;
        cout << "5. Book Ticket" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 1) {
            int id;
            string name, contact;
            cout << "Enter User ID, Name, and Contact: ";
            cin >> id >> name >> contact;
            userMap[id] = system.addUser(id, name, contact);
            cout << "User added successfully!" << endl;
        } 
        else if (choice == 2) {
            int id, duration;
            string title, language;
            float rating;
            cout << "Enter Movie ID, Title, Duration, Language, Rating: ";
            cin >> id >> title >> duration >> language >> rating;
            movieMap[id] = system.addMovie(id, title, duration, language, rating);
            cout << "Movie added successfully!" << endl;
        } 
        else if (choice == 3) {
            int id;
            string name, city;
            cout << "Enter Theater ID, Name, City: ";
            cin >> id >> name >> city;
            theaterMap[id] = system.addTheater(id, name, city);
            cout << "Theater added successfully!" << endl;
        } 
        else if (choice == 4) {
            int showId, movieId, theaterId, screenId, rows, cols;
            string time;
            cout << "Enter Show ID, Movie ID, Theater ID, Screen ID, Start Time, Rows, Cols: ";
            cin >> showId >> movieId >> theaterId >> screenId >> time >> rows >> cols;
            if (movieMap.find(movieId) == movieMap.end() || theaterMap.find(theaterId) == theaterMap.end()) {
                cout << "Invalid Movie or Theater ID!" << endl;
                continue;
            }
            Show* show = new Show(showId, movieMap[movieId], time, rows, cols);
            showMap[showId] = show;
            theaterMap[theaterId]->screens.push_back(new Screen(screenId));
            theaterMap[theaterId]->screens.back()->addShow(show);
            cout << "Show added successfully!" << endl;
        } 
        else if (choice == 5) {
            int userId, showId, row, col;
            cout << "Enter User ID, Show ID, Row, Column: ";
            cin >> userId >> showId >> row >> col;
            if (userMap.find(userId) == userMap.end() || showMap.find(showId) == showMap.end()) {
                cout << "Invalid User or Show ID!" << endl;
                continue;
            }
            Booking* booking = system.bookTicket(userMap[userId], showMap[showId], row, col);
            if (booking) {
                cout << "\n✅ Booking Successful!" << endl;
                booking->printBookingDetails();
            }
        } 
        else if (choice == 6) {
            cout << "Exiting system. Goodbye!" << endl;
            break;
        } 
        else {
            cout << "Invalid choice! Try again." << endl;
        }
    }
    return 0;
}


