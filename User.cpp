#include "User.h"
#include <sstream>

User::User() = default;

User::User(int id, std::string name) : id_(id), name_(std::move(name)) {}

int User::id() const noexcept { return id_; }
const std::string& User::name() const noexcept { return name_; }

const std::unordered_set<int>& User::borrowedBooks() const noexcept { return borrowed_; }
bool User::hasBorrowed(int bookId) const noexcept { return borrowed_.count(bookId) > 0; }

void User::borrowBook(int bookId) { borrowed_.insert(bookId); }
bool User::returnBook(int bookId) { return borrowed_.erase(bookId) > 0; }

std::string User::toString() const {
    std::ostringstream oss;
    oss << "User[" << id_ << "] " << name_ << " - borrowed(" << borrowed_.size() << ")";
    return oss.str();
}
