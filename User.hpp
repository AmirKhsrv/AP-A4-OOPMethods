#ifndef USER_H
#define USER_H "USER_H"

#include <iostream>
#include <algorithm>
#include "Shelf.hpp"
#include "Author.hpp"
#include "Review.hpp"

typedef std::string Country;
typedef std::string Date;
typedef std::vector<std::string> GenreList;
typedef std::vector<Author*> Authors;
typedef std::vector<Id> IdList;
typedef std::vector<Review> ReviewList;
typedef std::string ShelfType;

const std::string READ = "read";
const std::string WANT_TO_READ = "want_to_read";
const std::string CURRENTLY_READING = "currently_reading";

class User
{
public:
    User(Id id, std::string n,Country placeOB, Date memSince, Authors faveAuthor, GenreList faveGenr, Shelf bShelf, ReviewList rev);
    void setAuthors(Authors authors);
    void setShelf(Shelf bShelf);
    Id getId();
    void setReview(Review rev);
    Books getShelf(ShelfType shelfType);
    int getNumberOfUserReviews();
    int getNumberOfUserReviewsLikes();
    ReviewList getReviews();
    void showUser();
    void setBetterToReadBook(Book* book);
    GenreList getGenres();
    Book* getBetterToReadBook();
    void setNumberOfUserReviewsLikes();
    void setUserCredit(double uC);
    double getUserCredit();
    void setFollowUsers(std::vector<User*> fingUsers, std::vector<User*> ferUsers);
    void findFollowingsBestReadBooks(Books& allGoodBooks, std::vector<User*>& sawUsers);

private:
    IdList sortFavoriteAuthors();
    void showFavoriteGenre();
    void showFavoriteAuthors();
    void showAuthorById(Id authorId);
    bool checkUserRepeat(User* user, std::vector<User*>& allUsers);
    void sortBooksByRating(Books& books);
    void swapBooks(Books& books, int index1, int index2);
    Books getThreeHighRatingBooksRead();

    Id userId;
    std::string name;
    Country placeOfBirth;
    Date memberSince;
    Authors favoriteAuthors;
    GenreList favoriteGenres;
    Shelf bookShelf;
    ReviewList reviews;
    Book* betterToRead;
    Book* recommendedBook;
    int numberOfReviewsLikes;
    double userCredit;
    std::vector<User*> followings;
    std::vector<User*> followers;
};

#endif