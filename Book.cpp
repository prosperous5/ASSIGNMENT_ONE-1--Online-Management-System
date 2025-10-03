#include "Book.h"
#include <sstream>

Book::Book() = default;

Book::Book(int id, std::string title, std::string author, int year)
    : id_(id), title_(std::move(title)), author_(std::move(author)), year_(year), available_(true) {}

int Book::id() const noexcept { return id_; }
const std::string& Book::title() const noexcept { return title_; }
const std::string& Book::author() const noexcept { return author_; }
int Book::year() const noexcept { return year_; }
bool Book::available() const noexcept { return available_; }

void Book::setAvailable(bool v) noexcept { available_ = v; }

std::string Book::toString() const {
    std::ostringstream oss;
    oss << "Book[" << id_ << "] \"" << title_ << "\" by " << author_ << " (" << year_ << ") "
        << (available_ ? "[available]" : "[borrowed]");
    return oss.str();
}
