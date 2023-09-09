#ifndef SHELF_H
#define SHELF_H "SHELF_H"

#include <iostream>
#include "Book.hpp"

typedef std::vector<Book*> Books;

class Shelf
{
public:
    Shelf(Books r, Books cR, Books wTR);
    Shelf();
    Books getReadBooks();
    Books getCurrentlyReadingBooks();
    Books getWantToReadBooks();

private:
    Books read;
    Books currentlyReading;
    Books wantToRead;
};

#endif