#ifndef READ_DATA_H
#define READ_DATA_H "READ_DATA_H"

#include <iostream>
#include <vector>
#include <string>
#include "Book.hpp"
#include "Author.hpp"
#include "User.hpp"

const std::string COMMA = ",";
const std::string USERS_FILE_ADDRESS = "users.csv";
const std::string REVIEWS_FILE_ADDRESS = "reviews.csv";
const std::string BOOKS_FILE_ADDRESS = "books.csv";
const std::string AUTHORS_FILE_ADDRESS = "authors.csv";
const std::string FOLLOW_EDGES_FILE_ADDRESS = "follow_edges.csv";

typedef std::vector<Book> BookList;
typedef std::vector<User> UserList;
typedef std::vector<Author> AuthorList;
typedef std::string Address;
typedef std::string AuthorData;
typedef std::string BookData;
typedef std::string UserData;
typedef std::string Data;
typedef std::string AGenre;
typedef std::string AnAuthor;    
typedef std::vector<Id> IdList; 
typedef std::vector<User*> Users;  

class ReadData
{
public:
    ReadData(Address folderAddress);
    AuthorList readAuthorListDataFromFile();
    BookList readBookListDataFromFile();
    UserList readUserListDataFromFile();
    UserList readUserReview(UserList unlinkedUsers, BookList& unlinkedBooks);
    BookList linkBookAuthor(BookList unlinkedBooks, AuthorList& authorList);   
    UserList linkUserAuthor(UserList unlinkedUsers, AuthorList& authorList);
    UserList linkUserShelf(UserList unlinkedUsers, BookList& bookList);
    UserList setUserFollowingsFollowers(UserList& unlinkedUsers);

private:
    Review readReview(BookList& unlinkedBooks, UserData userReviewStr);
    Author setAuthorData(AuthorData authorDataStr);
    Book setBookData(BookData BookDataStr);
    User setUserData(UserData userDataStr);
    User setUserShelf(User unlinkedUser, BookList& bookList, UserData userDataStr);
    User setUserFavoriteAuthors(User unlinkedUser, AuthorList& authorList, UserData userDataStr);
    Books makeBookList(BookList& bookList, UserData userDataStr);
    GenreList makeGenreList(BookData genresDataStr);
    User* findUserById(UserList* allUsers, Id userId);
    Users readFollowData(UserList* allUsers, Data followDataStr);

    Address usersFileAddress;
    Address authorsFileAddress;
    Address booksFileAddress;
    Address reviewsFileAddress;
    Address followEdgesFileAddress;
};

#endif