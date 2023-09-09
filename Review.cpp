#include "Review.hpp"
#include <iostream>

using namespace std;

Review::Review(Id id, Book* b, int rate, Date d, int nOL)
{
    reviewId = id;
    book = b;
    rating = rate;
    date = d;
    numberOfLikes = nOL;
}

int Review::getNumberOfLikes()
{
    return numberOfLikes;
}

int Review::getRating()
{
    return rating;
}

Book* Review::getBook()
{
    return book;
}

void Review::showReview()
{
    cout << "id: " << reviewId;
    cout << " Rating: " << rating;
    cout << " Likes: " << numberOfLikes;
    cout << " Date: " << date << endl;
}

Id Review::getId()
{
    return reviewId;
}
