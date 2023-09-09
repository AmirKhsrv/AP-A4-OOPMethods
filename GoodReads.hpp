#ifndef GOODREADS_H
#define GOODREADS_H "GOODREADS_H"

#include <iostream>
#include <bits/stdc++.h> 
#include "Book.hpp"
#include "Author.hpp"
#include "User.hpp"
#include "functions.hpp"
#include "ReadData.hpp"

typedef std::vector<Book> BookList;
typedef std::vector<User> UserList;
typedef std::vector<Author> AuthorList;
typedef std::string Address;
typedef std::string AuthorData;
typedef std::string BookData;
typedef std::string AGenre;

class GoodReads
{
public:
    GoodReads(BookList b, UserList u, AuthorList a, ReadData& readData);
    void showAuthorInfo(Id authorId);
    void showSortedShelf(Id userId, std::string shelfType, AGenre genre);
    void showUserCredit(Id userId);
    void showBestBook();
    void showBestReviewer();
    void showRecommandedBookForUser(Id userId);
    void showRecommendedBookUsingFollowings(Id userId);

private:
    void printBooks(Books books);
    void showAuthorBooks(Id authorId);
    void showGenreMatchd(Books allBooks, AGenre genre);
    void showGenreUnmatchd(Books allBooks, AGenre genre);
    Book findBestBook();
    void setBooksAverageRating();
    void calculateBooksRating();
    void setRecommandedBookForUser();
    bool checkUserBookGenreMatching(Book book, User user);
    void showReviewsAbout(Book* book);
    void calculateUserCredit(User* user);
    void setExtraData();
    ReviewList findReviewsToShow(Book* book);

    BookList books;
    UserList users;
    AuthorList authors;
    int numberOfReviews;
    int numberOfReviewsLike;
};

#endif