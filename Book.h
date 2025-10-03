#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    int id_;
    std::string title_;
    std::string author_;
    int year_;
    bool available_;

public:
    Book();
    Book(int id, std::string title, std::string author, int year);

    int id() const noexcept;
    const std::string& title() const noexcept;
    const std::string& author() const noexcept;
    int year() const noexcept;
    bool available() const noexcept;

    void setAvailable(bool v) noexcept;

    std::string toString() const;
};

#endif
