#include "Book.h"
#include "User.h"
#include "Library.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>   // for exit()

using namespace std;

// Simple assert helper
void assertTrue(bool cond, const string &msg) {
    if (!cond) {
        cerr << "TEST FAILED: " << msg << endl;
        exit(1); // terminate immediately if a test fails
    } else {
        cout << "Success " << msg << endl;
    }
}

int main() {
    Library lib;
    string out;

    // --- Add books ---
    assertTrue(lib.addBook(Book(1,"The C++ Programming Language","Bjarne Stroustrup",2013), out), out);
    assertTrue(lib.addBook(Book(2,"Effective Modern C++","Scott Meyers",2014), out), out);
    assertTrue(lib.addBook(Book(3,"Clean Code","Robert C. Martin",2008), out), out);

    // Duplicate book
    bool r = lib.addBook(Book(1,"Duplicate","X",2020), out);
    assertTrue(!r && out=="Book with same ID already exists.", "reject duplicate book ID");

    // --- Register users ---
    assertTrue(lib.registerUser(User(100,"Alice"), out), out);
    assertTrue(lib.registerUser(User(101,"Bob"), out), out);

    // --- Borrow / return tests ---
    assertTrue(lib.borrowBook(100,1,out), out);
    r = lib.borrowBook(101,1,out);
    assertTrue(!r && out=="Book not available.", "can't borrow unavailable book");

    r = lib.returnBook(101,1,out);
    assertTrue(!r && out=="This user did not borrow this book.", "wrong user return blocked");

    assertTrue(lib.returnBook(100,1,out), out);

    // --- Remove book ---
    assertTrue(lib.removeBook(1,out), out);
    r = lib.removeBook(999,out);
    assertTrue(!r && out=="Book not found.", "remove non-existent book blocked");

    // --- Search ---
    auto res = lib.searchByAuthor("Scott");
    assertTrue(res.size()==1 && res[0].id()==2, "search by author works");

    res = lib.searchByTitle("clean");
    assertTrue(res.size()==1 && res[0].id()==3, "search by title works");

    auto byYear = lib.searchByYear(2014);
    assertTrue(byYear.size()==1 && byYear[0].id()==2, "search by year works");

    // --- Remove users ---
    assertTrue(lib.removeUser(101,out), out);
    r = lib.removeUser(999,out);
    assertTrue(!r && out=="User not found.", "remove non-existent user blocked");

    // --- Prevent removing user with borrowed books ---
    assertTrue(lib.registerUser(User(200,"Charlie"), out), out);
    assertTrue(lib.borrowBook(200,2,out), out);
    r = lib.removeUser(200,out);
    assertTrue(!r && out=="Cannot remove: user has borrowed books.", "block removing active borrower");

    assertTrue(lib.returnBook(200,2,out), out);
    assertTrue(lib.removeUser(200,out), out);

    cout << "\n All tests passed successfully!\n";
    return 0;
}

