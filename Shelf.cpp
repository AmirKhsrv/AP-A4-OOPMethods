#include "Shelf.hpp"
#include <iostream>

using namespace std;    
    
Shelf::Shelf(Books r, Books cR, Books wTR)
{
    read = r;
    currentlyReading = cR;
    wantToRead = wTR;
}

Shelf::Shelf()
{
}

Books Shelf::getReadBooks()
{
    return read;
}

Books Shelf::getCurrentlyReadingBooks()
{
    return currentlyReading;
}

Books Shelf::getWantToReadBooks()
{
    return wantToRead;
}
