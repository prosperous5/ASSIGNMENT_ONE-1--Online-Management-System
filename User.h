#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_set>

class User {
private:
    int id_;
    std::string name_;
    std::unordered_set<int> borrowed_;

public:
    User();
    User(int id, std::string name);

    int id() const noexcept;
    const std::string& name() const noexcept;

    const std::unordered_set<int>& borrowedBooks() const noexcept;
    bool hasBorrowed(int bookId) const noexcept;

    void borrowBook(int bookId);
    bool returnBook(int bookId);

    std::string toString() const;
};

#endif
