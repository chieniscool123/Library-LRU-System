/*
 * DO NOT MAKE ANY CHANGES
 */

#include "gtest/gtest.h"
#include "problem_1/book.h"
#include "problem_1/floor.h"
#include "problem_1/library.h"

std::vector<Book> get_books();

TEST(problem_1, library) {
    int wait_time = 0;

    // Create a library with floors and books
    std::vector<Floor> floors = {
        Floor('A', 'E', 120),
        Floor('F', 'J', 240),
        Floor('K', 'O', 360),
        Floor('P', 'T', 480),
        Floor('U', 'Z', 600),
    };
    std::vector<Book> books = get_books(); // create a vectors of books
    ArrayMap<std::string, Book &> book_by_title; // create a array map of book
    for (auto &book: books) {
        book_by_title.put(book.get_name(), book);
        // putting the book name as the key and the reference to the book in the as the value
    }
    Library library(floors, books, 5); // Create a library object with 5 floors and the vectors of books

    // Borrow a book
    Book borrowed_book;
    bool found = library.borrow_book("Frankenstein", borrowed_book, wait_time);
    // borrowed book = Frank, wait time = 240
    ASSERT_TRUE(found); // True
    Book expect; //
    book_by_title.get("Frankenstein", expect); // expect = reference to the book
    ASSERT_EQ(expect, borrowed_book);
    ASSERT_EQ(240, wait_time);

    // Borrow the same book again, and it shouldn't exist
    found = library.borrow_book("Frankenstein", borrowed_book, wait_time);
    ASSERT_FALSE(found);

    // Return the book
    library.return_book(borrowed_book);

    // Borrow the same book again, and it should exist, because it's been returned
    // And this time the wait time is only 5 seconds because it's retrieved from the front desk shelf
    found = library.borrow_book("Frankenstein", borrowed_book, wait_time);
    ASSERT_TRUE(found);
    ASSERT_EQ(expect, borrowed_book);
    ASSERT_EQ(5, wait_time);

    /*
     * Need to return the Frankenstein book
     *
     **/
    library.return_book(borrowed_book);

    /*
     * Borrow and return another 5 other books, just to get "Frankenstein" evicted from the front desk shelf
     */
    for (int i = 0; i < 5; ++i) {
        library.borrow_book(books[i].get_name(), borrowed_book, wait_time);
        library.return_book(borrowed_book);
    }

    /*
     * Borrow "Frankenstein", and now it has to be retrieved from its floor
     */
    found = library.borrow_book("Frankenstein", borrowed_book, wait_time);
    ASSERT_TRUE(found);
    ASSERT_EQ(expect, borrowed_book);
    ASSERT_EQ(240, wait_time);
}

std::vector<Book> get_books() {
    return {
        Book("A Tale of Two Cities", "9780141439600", 1859),
        Book("Brave New World", "9780060850524", 1932),
        Book("Catch-22", "9781451626650", 1961),
        Book("Dracula", "9780141439846", 1897),
        Book("Emma", "9780141439587", 1815),
        Book("Frankenstein", "9780486282114", 1818),
        Book("Gone with the Wind", "9781451635621", 1936),
        Book("Hamlet", "9780743477123", 1603),
        Book("Invisible Man", "9780679732761", 1952),
        Book("Jane Eyre", "9780141441146", 1847),
        Book("King Solomon's Mines", "9780141439525", 1885),
        Book("Lord of the Flies", "9780399501487", 1954),
        Book("Moby-Dick", "9781503280786", 1851),
        Book("Nineteen Eighty-Four", "9780451524935", 1949),
        Book("Oliver Twist", "9780141439747", 1838),
        Book("Pride and Prejudice", "9781503290563", 1813),
        Book("Quiet: The Power of Introverts in a World That Can't Stop Talking", "9780307352156", 2012),
        Book("Rebecca", "9780380730407", 1938),
        Book("Sense and Sensibility", "9780141439661", 1811),
        Book("To Kill a Mockingbird", "9780060935467", 1960),
        Book("Ulysses", "9780199535675", 1922),
        Book("Vanity Fair", "9780141439838", 1847),
        Book("War and Peace", "9781505237665", 1869),
        Book("Xenophon: The Persian Expedition", "9780140440072", -370),
        Book("The Yearling", "9781442487400", 1938),
        Book("Zorba the Greek", "9780684825548", 1946),
        Book("Anna Karenina", "9780143035008", 1877),
        Book("Beloved", "9781400033416", 1987),
        Book("Crime and Punishment", "9780140449136", 1866),
        Book("Don Quixote", "9780060934347", 1605)
    };
}
