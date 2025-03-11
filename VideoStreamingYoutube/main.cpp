#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Video {
public:
    string title;
    string genre;
    int duration; // in minutes
    Video() {} // Default constructor
    Video(string title, string genre, int duration) : title(title), genre(genre), duration(duration) {}
};

class User {
public:
    string username;
    vector<string> watchHistory;
    User() {} // Default constructor
    User(string username) : username(username) {}
    void watchVideo(string videoTitle) { watchHistory.push_back(videoTitle); }
};

class VideoStreamingPlatform {
private:
    map<string, Video> videos;
    map<string, User> users;
public:
    void addVideo(string title, string genre, int duration) {
        videos[title] = Video(title, genre, duration);
    }
    void addUser(string username) {
        users[username] = User(username);
    }
    void watchVideo(string username, string videoTitle) {
        if (users.find(username) != users.end() && videos.find(videoTitle) != videos.end()) {
            users[username].watchVideo(videoTitle);
            cout << username << " watched " << videoTitle << "\n";
        } else {
            cout << "Invalid user or video.\n";
        }
    }
    void showWatchHistory(string username) {
        if (users.find(username) != users.end()) {
            cout << "Watch History of " << username << ": ";
            for (auto &video : users[username].watchHistory)
                cout << video << " ";
            cout << "\n";
        } else {
            cout << "User not found.\n";
        }
    }
};

// void interactiveMenu() {
//     VideoStreamingPlatform platform;
//     int choice;
//     string title, genre, username;
//     int duration;

//     while (true) {
//         cout << "\nVideo Streaming Platform\n";
//         cout << "1. Add Video\n2. Add User\n3. Watch Video\n4. Show Watch History\n5. Exit\nEnter choice: ";
//         cin >> choice;

//         switch (choice) {
//             case 1:
//                 cout << "Enter video title: ";
//                 cin >> title;
//                 cout << "Enter genre: ";
//                 cin >> genre;
//                 cout << "Enter duration (minutes): ";
//                 cin >> duration;
//                 platform.addVideo(title, genre, duration);
//                 break;
//             case 2:
//                 cout << "Enter username: ";
//                 cin >> username;
//                 platform.addUser(username);
//                 break;
//             case 3:
//                 cout << "Enter username: ";
//                 cin >> username;
//                 cout << "Enter video title: ";
//                 cin >> title;
//                 platform.watchVideo(username, title);
//                 break;
//             case 4:
//                 cout << "Enter username: ";
//                 cin >> username;
//                 platform.showWatchHistory(username);
//                 break;
//             case 5:
//                 cout << "Exiting...\n";
//                 return;
//             default:
//                 cout << "Invalid choice, try again.\n";
//         }
//     }
// }

int main() {
    
    
    
    VideoStreamingPlatform platform;
    int choice;
    string title, genre, username;
    int duration;

    while (true) {
        cout << "\nVideo Streaming Platform\n";
        cout << "1. Add Video\n2. Add User\n3. Watch Video\n4. Show Watch History\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter video title: ";
                cin >> title;
                cout << "Enter genre: ";
                cin >> genre;
                cout << "Enter duration (minutes): ";
                cin >> duration;
                platform.addVideo(title, genre, duration);
                break;
            case 2:
                cout << "Enter username: ";
                cin >> username;
                platform.addUser(username);
                break;
            case 3:
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter video title: ";
                cin >> title;
                platform.watchVideo(username, title);
                break;
            case 4:
                cout << "Enter username: ";
                cin >> username;
                platform.showWatchHistory(username);
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }

    
   // interactiveMenu();
    return 0;
}
