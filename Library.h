#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <vector>
#include <string>

class Library {
private:
    std::vector<Book> books;   // define books here
    std::vector<User> users;   // define users here

public:
    Library() = default;

    // Book management
    bool addBook(const Book& book, std::string &msg);
    bool removeBook(int bookId, std::string &msg);
    std::vector<Book> searchByTitle(const std::string &title);
    std::vector<Book> searchByAuthor(const std::string &author);
    std::vector<Book> searchByYear(int year);

    // User management
    bool registerUser(const User& user, std::string &msg);
    bool removeUser(int userId, std::string &msg);

    // Borrow/return
    bool borrowBook(int userId, int bookId, std::string &msg);
    bool returnBook(int userId, int bookId, std::string &msg);

    // For main.cpp demo
    const std::vector<Book>& getAllBooks() const { return books; }
    const std::vector<User>& getAllUsers() const { return users; }
};

#endif

