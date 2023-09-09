#ifndef REVIEW_H
#define REVIEW_H "REVIEW_H"

#include <iostream>
#include "Book.hpp"

typedef std::string Date;
typedef int Id;

class Review
{
public:
    Review(Id id, Book* b, int rate, Date d, int nOL);
    int getNumberOfLikes();
    int getRating();
    Book* getBook();
    void showReview();
    Id getId();
    
private:
    Id reviewId;
    Book* book;
    int rating;
    Date date;
    int numberOfLikes;
};

#endif