#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>


using namespace std;

bool Library::addBook(const Book& book, string &msg) {
    for (const auto &b : books) {
        if (b.id() == book.id()) {
            msg = "Book with same ID already exists.";
            return false;
        }
    }
    books.push_back(book);   // ✅ now books exists
    msg = "Book added.";
    return true;
}

bool Library::removeBook(int bookId, string &msg) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->id() == bookId) {
            books.erase(it);
            msg = "Book removed.";
            return true;
        }
    }
    msg = "Book not found.";
    return false;
}

vector<Book> Library::searchByTitle(const string &title) {
    vector<Book> results;
    for (const auto &b : books) {
        string t = b.title();
        string key = title;
        transform(t.begin(), t.end(), t.begin(), [](unsigned char c){ return tolower(c); });
        transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return tolower(c); });

        if (t.find(key) != string::npos) {
            results.push_back(b);
        }
    }
    sort(results.begin(), results.end(),
         [](const Book &a, const Book &b){ return a.title() < b.title(); });
    return results;
}

vector<Book> Library::searchByAuthor(const string &author) {
    vector<Book> results;
    for (const auto &b : books) {
        string a = b.author();
        string key = author;
        transform(a.begin(), a.end(), a.begin(), [](unsigned char c){ return tolower(c); });
        transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return tolower(c); });

        if (a.find(key) != string::npos) {
            results.push_back(b);
        }
    }
    sort(results.begin(), results.end(),
         [](const Book &a, const Book &b){ return a.title() < b.title(); });
    return results;
}

vector<Book> Library::searchByYear(int year) {
    vector<Book> results;
    for (const auto &b : books) {
        if (b.year() == year) {
            results.push_back(b);
        }
    }
    return results;
}

bool Library::registerUser(const User& user, string &msg) {
    for (const auto &u : users) {
        if (u.id() == user.id()) {
            msg = "User with same ID already exists.";
            return false;
        }
    }
    users.push_back(user);
    msg = "User registered.";
    return true;
}

bool Library::removeUser(int userId, string &msg) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->id() == userId) {
            if (!it->borrowedBooks().empty()) {
                msg = "Cannot remove: user has borrowed books.";
                return false;
            }
            users.erase(it);
            msg = "User removed.";
            return true;
        }
    }
    msg = "User not found.";
    return false;
}

bool Library::borrowBook(int userId, int bookId, string &msg) {
    for (auto &b : books) {
        if (b.id() == bookId) {
            if (!b.isAvailable()) {
                msg = "Book not available.";
                return false;
            }
            for (auto &u : users) {
                if (u.id() == userId) {
                    b.setAvailable(false);
                    u.borrowBook(bookId);
                    msg = "Borrow successful.";
                    return true;
                }
            }
            msg = "User not found.";
            return false;
        }
    }
    msg = "Book not found.";
    return false;
}

bool Library::returnBook(int userId, int bookId, string &msg) {
    for (auto &u : users) {
        if (u.id() == userId) {
            if (u.returnBook(bookId)) {
                for (auto &b : books) {
                    if (b.id() == bookId) {
                        b.setAvailable(true);
                        msg = "Return successful.";
                        return true;
                    }
                }
            } else {
                msg = "This user did not borrow this book.";
                return false;
            }
        }
    }
    msg = "User not found.";
    return false;
}
