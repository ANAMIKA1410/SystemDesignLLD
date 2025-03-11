#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

// User Class
class User {
public:
    string userId;
    string name;
    string email;

    User(string id, string n, string e) : userId(id), name(n), email(e) {}
};

// Meeting Class
class Meeting {
public:
    int meetingId;
    string title;
    string organizerId;
    vector<string> participants;
    time_t startTime;
    time_t endTime;

    Meeting(int id, string t, string orgId, time_t start, time_t end)
        : meetingId(id), title(t), organizerId(orgId), startTime(start), endTime(end) {}
    Meeting() {}  // ✅ Default constructor to avoid error
};

// Meeting Scheduler Class
class MeetingScheduler {
private:
    unordered_map<string, vector<Meeting>> userMeetings; // User ID -> List of Meetings
    unordered_map<int, Meeting> meetings; // Meeting ID -> Meeting details
    int nextMeetingId = 1;

    // Check if a user is available for the given time slot
    bool isUserAvailable(string userId, time_t startTime, time_t endTime) {
        if (userMeetings.find(userId) == userMeetings.end()) return true;

        for (const auto &meeting : userMeetings[userId]) {
            if (!(endTime <= meeting.startTime || startTime >= meeting.endTime)) {
                return false; // Conflict detected
            }
        }
        return true;
    }

public:
    // Schedule a Meeting
    int scheduleMeeting(string organizerId, string title, vector<string> participants, time_t startTime, time_t endTime) {
        // Check conflicts
        for (const auto &participant : participants) {
            if (!isUserAvailable(participant, startTime, endTime)) {
                cout << "❌ Meeting conflict for user: " << participant << endl;
                return -1; // Conflict detected
            }
        }

        // Create a meeting
        Meeting newMeeting(nextMeetingId, title, organizerId, startTime, endTime);
        newMeeting.participants = participants;
        meetings.emplace(nextMeetingId, newMeeting);  // ✅ Fix the insertion error

        // Add to each participant's schedule
        for (const auto &participant : participants) {
            userMeetings[participant].push_back(newMeeting);
        }
        userMeetings[organizerId].push_back(newMeeting);

        cout << "✅ Meeting '" << title << "' scheduled successfully with ID: " << nextMeetingId << endl;
        return nextMeetingId++;
    }

    // Cancel a Meeting
    bool cancelMeeting(int meetingId, string organizerId) {
        if (meetings.find(meetingId) == meetings.end()) {
            cout << "❌ Meeting not found!" << endl;
            return false;
        }

        Meeting meeting = meetings[meetingId];
        if (meeting.organizerId != organizerId) {
            cout << "❌ Only the organizer can cancel the meeting!" << endl;
            return false;
        }

        // Remove from user schedules
        for (const auto &participant : meeting.participants) {
            auto &schedule = userMeetings[participant];
            schedule.erase(remove_if(schedule.begin(), schedule.end(),
                                     [meetingId](const Meeting &m) { return m.meetingId == meetingId; }),
                           schedule.end());
        }
        userMeetings[meeting.organizerId].erase(
            remove_if(userMeetings[meeting.organizerId].begin(), userMeetings[meeting.organizerId].end(),
                      [meetingId](const Meeting &m) { return m.meetingId == meetingId; }),
            userMeetings[meeting.organizerId].end());

        meetings.erase(meetingId);
        cout << "✅ Meeting " << meetingId << " cancelled successfully!\n";
        return true;
    }

    // Display all meetings for a user
    void showMeetings(string userId) {
        if (userMeetings.find(userId) == userMeetings.end() || userMeetings[userId].empty()) {
            cout << "🚫 No meetings scheduled for " << userId << endl;
            return;
        }

        cout << "📅 Meetings for " << userId << ":\n";
        for (const auto &meeting : userMeetings[userId]) {
            cout << "🆔 " << meeting.meetingId << " | " << meeting.title << " | Start: " << ctime(&meeting.startTime)
                 << " | End: " << ctime(&meeting.endTime) << endl;
        }
    }
};

// Interactive Console Interface
void interactiveScheduler(MeetingScheduler &scheduler) {
    int choice;
    string organizerId, userId, title;
    vector<string> participants;
    time_t startTime, endTime;
    int meetingId;

    do {
        cout << "\n========== Meeting Scheduler ==========\n";
        cout << "1️⃣ Schedule Meeting\n";
        cout << "2️⃣ Cancel Meeting\n";
        cout << "3️⃣ View User Meetings\n";
        cout << "4️⃣ Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "👤 Enter Organizer ID: ";
                cin >> organizerId;
                cout << "📌 Enter Meeting Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "⏳ Enter Start Time (epoch): ";
                cin >> startTime;
                cout << "⏳ Enter End Time (epoch): ";
                cin >> endTime;

                cout << "👥 Enter number of participants: ";
                int num;
                cin >> num;
                participants.clear();
                for (int i = 0; i < num; ++i) {
                    string participant;
                    cout << "👤 Enter participant ID " << i + 1 << ": ";
                    cin >> participant;
                    participants.push_back(participant);
                }

                scheduler.scheduleMeeting(organizerId, title, participants, startTime, endTime);
                break;

            case 2:
                cout << "🆔 Enter Meeting ID to cancel: ";
                cin >> meetingId;
                cout << "👤 Enter Organizer ID: ";
                cin >> organizerId;
                scheduler.cancelMeeting(meetingId, organizerId);
                break;

            case 3:
                cout << "👤 Enter User ID: ";
                cin >> userId;
                scheduler.showMeetings(userId);
                break;

            case 4:
                cout << "🚪 Exiting Meeting Scheduler. Have a great day!\n";
                break;

            default:
                cout << "❌ Invalid choice! Try again.\n";
        }
    } while (choice != 4);
}

// Main Function
int main() {
    MeetingScheduler scheduler;
    interactiveScheduler(scheduler);
    return 0;
}
