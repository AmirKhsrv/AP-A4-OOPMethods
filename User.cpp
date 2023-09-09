#include "User.hpp"
#include <iostream>

using namespace std;

User::User(Id id, std::string n,Country placeOB, Date memSince, Authors faveAuthor, GenreList faveGenr, Shelf bShelf, ReviewList rev)
{
    userId = id;
    name = n;
    placeOfBirth = placeOB;
    memberSince = memSince;
    favoriteAuthors = faveAuthor;
    favoriteGenres = faveGenr;
    bookShelf = bShelf;
    reviews = rev;
}

void User::setAuthors(Authors authors)
{
    favoriteAuthors = authors;
}

void User::setShelf(Shelf bShelf)
{
    bookShelf = bShelf;
}

Id User::getId()
{
    return userId;
}

void User::setReview(Review rev)
{
    reviews.push_back(rev);
}

Books User::getShelf(ShelfType shelfType)
{
    if (shelfType == READ)
        return bookShelf.getReadBooks();
    if (shelfType == CURRENTLY_READING)
        return bookShelf.getCurrentlyReadingBooks();
    if (shelfType == WANT_TO_READ)
        return bookShelf.getWantToReadBooks();
}

int User::getNumberOfUserReviews()
{
    return reviews.size();
}

int User::getNumberOfUserReviewsLikes()
{
    return numberOfReviewsLikes;
}

ReviewList User::getReviews()
{
    return reviews;
}

void User::showUser()
{
    cout << "id: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Place of Birth: " << placeOfBirth << endl;
    cout << "Member Since: " << memberSince << endl;
    showFavoriteGenre();
    showFavoriteAuthors();
    cout << "Number of Books in Read Shelf: " << bookShelf.getReadBooks().size() << endl;
    cout << "Number of Books in Want to Read Shelf: " << bookShelf.getWantToReadBooks().size() << endl;   
    cout << "Number of Books in Currently Reading Shelf: " << bookShelf.getCurrentlyReadingBooks().size() << endl;
    cout << "Number of Likes: " << getNumberOfUserReviewsLikes() << endl;
}

void User::showFavoriteGenre()
{
    cout << "Favorite Genres: ";
    for (int i = 0; i < favoriteGenres.size() - 1; i++)
        cout << favoriteGenres[i] << ", ";
    cout << favoriteGenres[favoriteGenres.size() - 1] << endl;
}

void User::showFavoriteAuthors()
{
    IdList authorsId = sortFavoriteAuthors();
    cout << "Favorite Authors: ";
    for (int i = 0; i < authorsId.size() - 1; i++)
    {
        showAuthorById(authorsId[i]);
        cout << ", ";
    }
    showAuthorById(authorsId[authorsId.size() - 1]);
    cout << endl;
}

void User::showAuthorById(Id authorId)
{
    for (int j = 0; j < favoriteAuthors.size(); j++)
        if (authorId == favoriteAuthors[j]->getId())
            cout << favoriteAuthors[j]->getName();
}

IdList User::sortFavoriteAuthors()
{
    IdList authorsId;
    for (int i = 0; i < favoriteAuthors.size(); i++)
        authorsId.push_back(favoriteAuthors[i]->getId());
    sort(authorsId.begin(), authorsId.end());
    return authorsId;
}

void User::setBetterToReadBook(Book* book)
{
    betterToRead = book;
}

GenreList User::getGenres()
{
    return favoriteGenres;
}

Book* User::getBetterToReadBook()
{
    return betterToRead;
}

void User::setNumberOfUserReviewsLikes()
{
    numberOfReviewsLikes = 0;
    for (int i = 0; i < reviews.size(); i++)
        numberOfReviewsLikes += reviews[i].getNumberOfLikes();
}
void User::setUserCredit(double uC)
{
    userCredit = uC;
}

double User::getUserCredit()
{
    return userCredit;
}

void User::setFollowUsers(std::vector<User*> fingUsers, std::vector<User*> ferUsers)
{
    followings = fingUsers;
    followers = ferUsers;
}

Books User::getThreeHighRatingBooksRead()
{
    Books threeBooks;
    Books allReadBooks = bookShelf.getReadBooks();
    sortBooksByRating(allReadBooks);
    for (int i = 1; i < 4; i++)
        if (bookShelf.getReadBooks().size() >= i)
            threeBooks.push_back(allReadBooks[allReadBooks.size() - i]);
    return threeBooks;
}

void User::findFollowingsBestReadBooks(Books& allGoodBooks, vector<User*>& sawUsers)
{
    for (int i = 0; i < followings.size(); i++)
    {
        if (checkUserRepeat(followings[i], sawUsers)) 
            continue;
        for (int j = 0; j < followings[i]->getThreeHighRatingBooksRead().size(); j++)
        {
            allGoodBooks.push_back(followings[i]->getThreeHighRatingBooksRead()[j]);
        }
        sawUsers.push_back(followings[i]);
        followings[i]->findFollowingsBestReadBooks(allGoodBooks, sawUsers);
    }
}

bool User::checkUserRepeat(User* user, vector<User*>& allUsers)
{
    for (int i = 0; i < allUsers.size(); i++)
        if (user->getId() == allUsers[i]->getId())
            return true;
    return false;
}


void User::sortBooksByRating(Books& books)
{
    for (int i = 0; i < books.size(); i++)
        for (int j = i; j < books.size(); j++)
            if (books[j]->getBookRating() < books[i]->getBookRating())
                swapBooks(books, i, j);
}

void User::swapBooks(Books& books, int index1, int index2)
{
    Book* bookHelp;
    bookHelp = books[index1];
    books[index1] = books[index2];
    books[index2] = bookHelp;
}
