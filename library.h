/*
 * DO NOT MAKE ANY CHANGES
 */

#pragma once

#include "util.h"
#include "floor.h"
#include "LRU.hpp"
#include "book.h"

class Library {
private:
    std::vector<Floor> floors;
    LRUCache<Book> front_desk_shelf;

    bool find_book_in_floors(const std::string &basicString, Book &book, int &sec);

public:
    Library(const std::vector<Floor> &floors,
            const std::vector<Book> &books,
            int book_shelf_capacity) : floors(floors), front_desk_shelf(book_shelf_capacity) {
        for (Floor &floor: this->floors) {
            for (const Book &book: books) {
                floor.put_book(book);
            }
        }
    };

    bool borrow_book(const std::string &name, Book &borrowed_book, int &time_of_operation_in_sec);

    void return_book(const Book &book_to_return);
};