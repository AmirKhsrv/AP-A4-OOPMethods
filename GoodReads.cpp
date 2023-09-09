#include "GoodReads.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

typedef string Genre;       

GoodReads::GoodReads(BookList b, UserList u, AuthorList a, ReadData& readData)
{
    books = b;
    users = u;
    authors = a;
    books = readData.linkBookAuthor(books, authors);
    users = readData.linkUserAuthor(users, authors);
    users = readData.linkUserShelf(users, books);
    users = readData.readUserReview(users, books);
    readData.setUserFollowingsFollowers(users);
    setBooksAverageRating();
    numberOfReviewsLike = 0;
    numberOfReviews = 0;
    setExtraData();
}

void GoodReads::setExtraData()
{
    for (int i = 0; i < users.size(); i++)
    {
        users[i].setNumberOfUserReviewsLikes();
        numberOfReviewsLike += users[i].getNumberOfUserReviewsLikes();
        numberOfReviews += users[i].getNumberOfUserReviews();
    }
    for (int i = 0; i < users.size(); i++)
        calculateUserCredit(&users[i]);
    calculateBooksRating();
    setRecommandedBookForUser();
}

void GoodReads::showAuthorInfo(Id authorId)
{
    for (int i = 0; i < authors.size(); i++)
        if (authorId == authors[i].getId())
            authors[i].printAuthorInfo();
    showAuthorBooks(authorId);
}

void GoodReads::showAuthorBooks(Id authorId)
{
    cout << "Books:" << endl;
    for (int i = 0; i < books.size(); i++)
        if (authorId == books[i].getAuthor()->getId())
            cout << "id: " << books[i].getId() << " Title: " << books[i].getTitle() << endl;
}

void GoodReads::showSortedShelf(Id userId, string shelfType, AGenre genre)
{
    for (int i = 0; i < users.size(); i++)
        if (users[i].getId() == userId)
        {
            Books allBooks = users[i].getShelf(shelfType);
            showGenreMatchd(allBooks, genre);
            showGenreUnmatchd(allBooks, genre);
        }
}

void GoodReads::printBooks(Books books)
{
    for (int i = 0; i < books.size(); i++)
    {
        books[i]->showBook();
        cout << "***" << endl;
    }
}

void GoodReads::showGenreMatchd(Books allBooks, AGenre genre)
{
    Books resultBooks;
    for (int i = 0; i < allBooks.size(); i++)
        if (allBooks[i]->getGenre() == genre)
            resultBooks.push_back(allBooks[i]);
    sort(resultBooks.begin(), resultBooks.end(), prioritizeBookName);
    printBooks(resultBooks);
}

void GoodReads::showGenreUnmatchd(Books allBooks, AGenre genre)
{
    Books resultBooks;
    for (int i = 0; i < allBooks.size(); i++)
        if (allBooks[i]->getGenre() != genre)
            resultBooks.push_back(allBooks[i]);
    sort(resultBooks.begin(), resultBooks.end(), prioritizeBookName);
    printBooks(resultBooks);
}

void GoodReads::calculateUserCredit(User* user)
{
    double userCredit;
    double numberOfUserReviewsLikes;
    double numberOfUserReviews;
    numberOfUserReviewsLikes = (double)user->getNumberOfUserReviewsLikes();
    numberOfUserReviews = (double)user->getNumberOfUserReviews();
    userCredit = (numberOfUserReviewsLikes / numberOfReviewsLike + numberOfUserReviews / numberOfReviews) / 2;
    user->setUserCredit(userCredit);
}

void GoodReads::showUserCredit(Id userId)
{
    for (int i = 0; i < users.size(); i++)
        if (users[i].getId() == userId)
            cout << fixed << setprecision(6) << users[i].getUserCredit() << endl; 
}

void GoodReads::showBestBook()
{
        Book bestBook = findBestBook();
        bestBook.showBook();
        cout << "Average Rating: " << fixed << setprecision(2) << bestBook.getAverageRating() << endl;        
}

Book GoodReads::findBestBook()
{
    Book bestBook = books[0];
    for (int i = 0; i < books.size(); i++)
        if (books[i].getAverageRating() > bestBook.getAverageRating())
            bestBook = books[i];
    return bestBook;
}

void GoodReads::setBooksAverageRating()
{
    ReviewList userReviewList;
    for (int i = 0; i < users.size(); i++)
    {
        userReviewList = users[i].getReviews();
        for (int j = 0; j < userReviewList.size(); j++)
            userReviewList[j].getBook()->setScore(userReviewList[j].getRating());
    }
}

void GoodReads::showBestReviewer()
{
    User bestReviewer = users[0];
    for (int i = 0; i < users.size(); i++)
        if (users[i].getNumberOfUserReviewsLikes() > bestReviewer.getNumberOfUserReviewsLikes())
            bestReviewer = users[i];
    bestReviewer.showUser();
}

void GoodReads::calculateBooksRating()
{
    for (int i = 0; i < users.size(); i++)
    {
        ReviewList reviews = users[i].getReviews();
        for (int j = 0; j < reviews.size(); j++)
            reviews[j].getBook()->setBookRating((double)reviews[j].getRating() * users[i].getUserCredit());
    }
}

void GoodReads::setRecommandedBookForUser()
{
    Score bestScore = 0;
    for (int i = 0; i < users.size(); i++)
    {
        bestScore = 0;
        for (int j = 0; j < books.size(); j++)
        {
            Score bookScore = books[j].getBookRating();
            if (checkUserBookGenreMatching(books[j], users[i]))
                bookScore += 5; 
            if ((bookScore > bestScore) || ((bookScore == bestScore) 
                && (users[i].getBetterToReadBook()->getId()) < books[j].getId()))
            {
                users[i].setBetterToReadBook(&books[j]);
                bestScore = bookScore;
            }
        } 
    }
}

bool GoodReads::checkUserBookGenreMatching(Book book, User user)
{
    for (int i = 0; i < user.getGenres().size(); i++)
        if (book.getGenre() == user.getGenres()[i])
            return true;
    return false;
}

void GoodReads::showRecommandedBookForUser(Id userId)
{
    for (int i = 0; i < users.size(); i++)
        if (users[i].getId() == userId)
        {
            users[i].getBetterToReadBook()->showBook();
            showReviewsAbout(users[i].getBetterToReadBook());
        }        
}
void GoodReads::showReviewsAbout(Book* book)
{
    cout << "Reviews:" << endl;
    ReviewList reviewsToShow = findReviewsToShow(book);
    sort(reviewsToShow.begin(), reviewsToShow.end(), prioritizeReviewsId);
    for (int i = 0; i < reviewsToShow.size(); i++)
        reviewsToShow[i].showReview();
}

ReviewList GoodReads::findReviewsToShow(Book* book)
{
    ReviewList reviewsToShow;
    for (int i = 0; i < users.size(); i++)
        for (int j = 0; j < users[i].getReviews().size(); j++)
            if (users[i].getReviews()[j].getBook()->getId() == book->getId())
                reviewsToShow.push_back(users[i].getReviews()[j]);
    return reviewsToShow;
}

void GoodReads::showRecommendedBookUsingFollowings(Id userId)
{
    Users null;
    Books allGoodBooks;
    for (int i = 0; i < users.size(); i++)
        if (users[i].getId() == userId)
        {
            null.push_back(&users[i]);
            users[50].findFollowingsBestReadBooks(allGoodBooks, null);
        }
    int mostCount = 0;
    int counter = 0;
    int index;
    for (int i = 0; i < allGoodBooks.size(); i++)
    {
        counter = 0;
        for (int j = 0; j < allGoodBooks.size(); j++)
            if (allGoodBooks[j]->getId() == allGoodBooks[i]->getId())
                counter++;
        if (counter > mostCount)
        {
            mostCount = counter;
            index = i;
        }
        if (mostCount == counter && allGoodBooks[i]->getId() < allGoodBooks[index]->getId())
        {
            mostCount = counter;
            index = i;
        }
    }
    allGoodBooks[index]->showBook();
    showReviewsAbout(allGoodBooks[index]);
}
