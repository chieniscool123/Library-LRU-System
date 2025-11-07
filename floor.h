/*
 * DO NOT MAKE ANY CHANGES
 */

#pragma once

#include "util.h"
#include "book.h"
#include "array_map.h"

#define SHELF_SIZE 1000

class Floor {
private:
    char start_letter;
    char end_letter;
    int trip_time_in_sec;

    bool is_within_range(char c) const {
        return c >= start_letter && c <= end_letter;
    }

    ArrayMap<std::string, Book> shelves;

public:
    Floor(char startLetter,
          char endLetter,
          int tripTimeInSec) : start_letter(startLetter),
                               end_letter(endLetter),
                               trip_time_in_sec(tripTimeInSec),
                               shelves(SHELF_SIZE) {}

    void put_book(const Book &book) {
        char first_letter = book.name[0];
        if (!is_within_range(first_letter)) {
            return; // book does not belong to this floor
        }

        Book found_book;
        if (shelves.get(book.name, found_book)) {
            return; // book already exists
        }

        shelves.put(book.name, book);
    }

    bool find_and_return_book(const std::string &book_name, Book &borrowed_book, int &time_in_sec) {

        char first_letter = book_name[0];
        if (!is_within_range(first_letter)) {
            return false;
        }

        time_in_sec = this->trip_time_in_sec;
        bool found = shelves.get(book_name, borrowed_book);
        if (found) {
            shelves.remove(book_name);
        }
        return found;
    }
};

