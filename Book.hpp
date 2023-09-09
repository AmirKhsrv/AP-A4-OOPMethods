#ifndef BOOK_H
#define BOOK_H "BOOK_H"

#include <iostream>
#include "Author.hpp"

typedef std::vector<std::string> GenreList;
typedef int Id;
typedef std::string Address;
typedef std::string AGenre;
typedef double Score;

class Book
{
public:
    Book(Id id, std::string t, Author* auth, GenreList genr);
    void setAuthor(Author* auth);
    Id getId();
    Author* getAuthor();
    std::string getTitle();
    void showBook();
    AGenre getGenre();
    void setScore(int addedScore);
    Score getAverageRating();
    void setBookRating(double addedScore);
    Score getBookRating();
    void refreshNumberOfReviewsAbout();

private:
    Id bookId;
    std::string title;
    Author* author;
    GenreList genres;
    int totalScore;
    int numberOfReviewsAbout;
    Score totalBookRating;
};

#endif