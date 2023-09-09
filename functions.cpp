#include "functions.hpp"

using namespace std;

bool prioritizeBookName(Book* book1, Book* book2)
{
    if (book1->getTitle() < book2->getTitle())
        return true;
    if (book1->getTitle() == book2->getTitle())
        return book1->getId() < book2->getId();
    return false;
}

bool prioritizeReviewsId(Review review1, Review review2)
{
    return review1.getId() < review2.getId();
}

bool prioritizeGenresName(string genre1, string genre2)
{
    return genre1 < genre2;
}