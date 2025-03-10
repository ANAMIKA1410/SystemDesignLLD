#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Post;
class User;

// Comment class
class Comment {
public:
    string username;
    string text;

    Comment(string user, string content) : username(user), text(content) {}
};

// Post class
class Post {
public:
    int postId;
    string content;
    string author;
    int likes;
    vector<Comment> comments;

    Post(int id, string user, string text) : postId(id), author(user), content(text), likes(0) {}

    void addComment(string user, string text) {
        comments.push_back(Comment(user, text));
    }

    void likePost() { likes++; }
    void unlikePost() { if (likes > 0) likes--; }

    void display() {
        cout << "📢 " << author << ": " << content << " (" << likes << " Likes, " << comments.size() << " Comments)\n";
        for (auto &comment : comments) {
            cout << "   💬 " << comment.username << ": " << comment.text << "\n";
        }
    }
};

// User class
class User {
public:
    string username;
    unordered_set<string> following;
    vector<Post> posts;

    User(string name) : username(name) {}

    void follow(string otherUser) {
        following.insert(otherUser);
    }

    void unfollow(string otherUser) {
        following.erase(otherUser);
    }

    void createPost(int postId, string content) {
        posts.push_back(Post(postId, username, content));
    }

    void displayPosts() {
        for (auto &post : posts) {
            post.display();
        }
    }
};

// Feed class
class Feed {
public:
    unordered_map<string, User*> users;
    int postCounter = 1;

    void addUser(string username) {
        if (users.find(username) == users.end()) {
            users[username] = new User(username);
            cout << "👤 User \"" << username << "\" created an account!\n";
        }
    }

    void followUser(string user, string toFollow) {
        if (users.find(user) != users.end() && users.find(toFollow) != users.end()) {
            users[user]->follow(toFollow);
            cout << "✅ " << user << " is now following " << toFollow << "!\n";
        }
    }

    void createPost(string username, string content) {
        if (users.find(username) != users.end()) {
            users[username]->createPost(postCounter++, content);
            cout << "📝 New Post: \"" << content << "\" by @" << username << "\n";
        }
    }

    void likePost(string username, string userWhoPosted, int postId) {
        if (users.find(userWhoPosted) != users.end() && postId > 0 && postId <= users[userWhoPosted]->posts.size()) {
            users[userWhoPosted]->posts[postId - 1].likePost();
            cout << "👍 @" << username << " liked the post by @" << userWhoPosted << "!\n";
        }
    }

    void addComment(string username, string userWhoPosted, int postId, string commentText) {
        if (users.find(userWhoPosted) != users.end() && postId > 0 && postId <= users[userWhoPosted]->posts.size()) {
            users[userWhoPosted]->posts[postId - 1].addComment(username, commentText);
            cout << "💬 @" << username << " commented: \"" << commentText << "\" on @" << userWhoPosted << "'s post!\n";
        }
    }

    void showFeed(string username) {
        if (users.find(username) == users.end()) return;

        cout << "\n📢 News Feed for @" << username << ":\n";
        for (const string& followee : users[username]->following) {
            if (users.find(followee) != users.end()) {
                users[followee]->displayPosts();
            }
        }
    }
};

// Main function
int main() {
    Feed socialMedia;

    socialMedia.addUser("Anamika");
    socialMedia.addUser("John");

    socialMedia.followUser("Anamika", "John");

    socialMedia.createPost("John", "Excited to start my new project!");
    socialMedia.createPost("Anamika", "Learning C++ today!");

    socialMedia.likePost("Anamika", "John", 1);
    socialMedia.addComment("Anamika", "John", 1, "Good luck with your project!");

    socialMedia.showFeed("Anamika");

    return 0;
}
