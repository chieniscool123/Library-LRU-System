/*
 * DO NOT MAKE ANY CHANGES
 */

#include "library.h"

bool Library::borrow_book(const std::string &book_name, Book &borrowed_book, int &time_of_operation_in_sec) {
    bool found = front_desk_shelf.get(book_name, borrowed_book);
    if (found) {
        time_of_operation_in_sec = front_desk_shelf.get_capacity();
        // each book in the front desk shelf takes 1 sec to search
        front_desk_shelf.remove(book_name); // We didn't remove it after we borrow it so I remove the book from the LRU
        return true;
    }

    return find_book_in_floors(book_name, borrowed_book, time_of_operation_in_sec);
}

void Library::return_book(const Book &book_to_return) {
    Book evicted_book;
    bool book_evicted = front_desk_shelf.put(book_to_return.name, book_to_return, evicted_book);

    // walk each floor and find the book
    if (book_evicted) {
        for (Floor &floor: floors) {
            floor.put_book(evicted_book);
        }
    }
}

bool Library::find_book_in_floors(const std::string &book_name, Book &borrowed_book, int &time_of_operation_in_sec) {
    // walk each floor and find the book
    for (Floor &floor: floors) {
        bool found = floor.find_and_return_book(book_name, borrowed_book, time_of_operation_in_sec);
        if (found) {
            return true;
        }
    }
    return false;
}
