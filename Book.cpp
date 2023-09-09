#include "Book.hpp"
#include <iostream>

using namespace std;

Book::Book(Id id, std::string t, Author* auth, GenreList genr)
{
    bookId = id;
    title = t;
    author = auth;
    genres = genr;
    totalScore = 0;
    numberOfReviewsAbout = 0;
    totalBookRating = 0;
}

void Book::setAuthor(Author* auth)
{
    author = auth;
}

Id Book::getId()
{
    return bookId;
}

string Book::getTitle()
{
    return title;
}

Author* Book::getAuthor()
{
    return author;
}

AGenre Book::getGenre()
{
    return genres[genres.size()-1];
}

void Book::setScore(int addedScore)
{
    totalScore +=  addedScore;
    numberOfReviewsAbout++;
}

Score Book::getAverageRating()
{
    if (numberOfReviewsAbout == 0)
        return 0;
    return (double)totalScore / (double)numberOfReviewsAbout;
}

void Book::showBook()
{
    cout << "id: " << bookId << endl;
    cout << "Title: " << title << endl;
    cout << "Genre: " << genres[0] << endl;
    cout << "Author: " << author->getName() << endl;
}

Score Book::getBookRating()
{
    if (numberOfReviewsAbout == 0)
        return 0;
    return totalBookRating / numberOfReviewsAbout;
}

void Book::setBookRating(double addedScore)
{
    totalBookRating += addedScore;
}

void Book::refreshNumberOfReviewsAbout()
{
    numberOfReviewsAbout = 0;
}

