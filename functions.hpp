#ifndef FUNCTIONS
#define FUNCTIONS "FUNCTIONS"

#include <iostream>

#include "Book.hpp"
#include "User.hpp"

bool prioritizeBookName(Book* book1, Book* book2);
bool prioritizeReviewsId(Review review1, Review review2);
bool prioritizeGenresName(std::string genre1, std::string genre2);

#endif