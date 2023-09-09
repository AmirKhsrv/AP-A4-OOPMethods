#include "ReadData.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const char DELIMITER = ',';
const char SAME_DATA_DELIMITER = '$';

ReadData::ReadData(Address folderAddress)
{
    usersFileAddress.append(folderAddress);
    usersFileAddress.append("/");
    usersFileAddress.append(USERS_FILE_ADDRESS);

    authorsFileAddress.append(folderAddress);
    authorsFileAddress.append("/");
    authorsFileAddress.append(AUTHORS_FILE_ADDRESS);

    booksFileAddress.append(folderAddress);
    booksFileAddress.append("/");
    booksFileAddress.append(BOOKS_FILE_ADDRESS);

    reviewsFileAddress.append(folderAddress);
    reviewsFileAddress.append("/");
    reviewsFileAddress.append(REVIEWS_FILE_ADDRESS);

    followEdgesFileAddress.append(folderAddress);
    followEdgesFileAddress.append("/");
    followEdgesFileAddress.append(FOLLOW_EDGES_FILE_ADDRESS);
}


Author ReadData::setAuthorData(AuthorData authorDataStr)
{
    stringstream  authorData;
    authorData << authorDataStr;
    Id authorId;
    string authorName;
    Gender authorGender;
    Date memberSince;
    Year yearOfBirth;
    Country placeOfBirth;
    GenreList genres;
    AGenre genre;
    string readPart;
    getline(authorData, readPart, DELIMITER);
    authorId = stoi(readPart);
    getline(authorData, authorName, DELIMITER);
    getline(authorData, readPart, DELIMITER);
    if (readPart == "male")
        authorGender = male;
    else
        authorGender = female;
    getline(authorData, memberSince, DELIMITER);
    getline(authorData, readPart, DELIMITER);
    yearOfBirth = stoi(readPart);
    getline(authorData, placeOfBirth, DELIMITER);
    getline(authorData, genre, DELIMITER);
    genres = makeGenreList(genre);
    return Author(authorId, authorName, authorGender, memberSince, yearOfBirth, placeOfBirth, genres);
}

AuthorList ReadData::readAuthorListDataFromFile()
{
    AuthorList authorList;
    ifstream authorsData;
    authorsData.open(authorsFileAddress);
    AuthorData authorDataStr;
    getline(authorsData, authorDataStr);
    while (getline(authorsData, authorDataStr)) 
        authorList.push_back(setAuthorData(authorDataStr));         
    return authorList;
}

Book ReadData::setBookData(BookData bookDataStr)
{
    stringstream  bookData;
    bookData << bookDataStr;
    Id bookId;
    string bookTitle;
    GenreList genres;
    AGenre genre;
    string readPart;
    getline(bookData, readPart, DELIMITER);
    bookId = stoi(readPart);
    getline(bookData, bookTitle, DELIMITER);
    getline(bookData, readPart, DELIMITER);
    getline(bookData, genre, DELIMITER);
    genres = makeGenreList(genre);
    return Book(bookId, bookTitle, NULL, genres);
}

BookList ReadData::readBookListDataFromFile()
{
    BookList bookList;
    ifstream booksData;
    booksData.open(booksFileAddress);
    BookData bookDataStr;
    getline(booksData, bookDataStr);
    while (getline(booksData, bookDataStr)) 
        bookList.push_back(setBookData(bookDataStr));            
    return bookList;
}

BookList ReadData::linkBookAuthor(BookList unlinkedBooks, AuthorList& authorList)
{
    ifstream booksData;
    Data readData;
    booksData.open(booksFileAddress);
    getline(booksData, readData);
    for (int i = 0; i < unlinkedBooks.size(); i++)
    {
        Id authorId;
        getline(booksData, readData, DELIMITER);
        getline(booksData, readData, DELIMITER);
        getline(booksData, readData, DELIMITER);
        authorId = stoi(readData);
        for (int j = 0; j < authorList.size(); j++)
            if (authorId == authorList[j].getId())
                unlinkedBooks[i].setAuthor(&authorList[j]);        
    }
    return unlinkedBooks;
}   

UserList ReadData::readUserListDataFromFile()
{
    UserList userList;
    ifstream usersData;
    usersData.open(usersFileAddress);
    UserData userDataStr;
    getline(usersData, userDataStr);
    while (getline(usersData, userDataStr)) 
        userList.push_back(setUserData(userDataStr));            
    return userList;
}

User ReadData::setUserData(UserData userDataStr)
{
    stringstream  userData;
    userData << userDataStr;
    Id userId;
    string userName;
    Country placeOfBirth;
    Date memberSince;
    Authors favoriteAuthors;
    AnAuthor author;
    GenreList favoriteGenres;
    AGenre genre;
    string readPart;
    getline(userData, readPart, DELIMITER);
    userId = stoi(readPart);
    getline(userData, userName, DELIMITER);
    getline(userData, placeOfBirth, DELIMITER);
    getline(userData, memberSince, DELIMITER);
    getline(userData, author, DELIMITER);
    getline(userData, genre, DELIMITER);
    favoriteGenres = makeGenreList(genre);
    Books emptyBooks;
    Shelf emptyShelf(emptyBooks, emptyBooks, emptyBooks);
    ReviewList emptyReviews;
    return User(userId, userName, placeOfBirth, memberSince, favoriteAuthors,favoriteGenres, emptyShelf, emptyReviews);
}

UserList ReadData::linkUserAuthor(UserList unlinkedUsers, AuthorList& authorList)
{
    ifstream usersData;
    usersData.open(usersFileAddress);
    UserData userData;
    getline(usersData, userData);
    int i = 0;
    while (getline(usersData, userData, DELIMITER))
    {
        getline(usersData, userData, DELIMITER);
        getline(usersData, userData, DELIMITER);
        getline(usersData, userData, DELIMITER);
        getline(usersData, userData, DELIMITER);
        unlinkedUsers[i] = setUserFavoriteAuthors(unlinkedUsers[i], authorList, userData);
        i++;
        getline(usersData, userData);
    }
    return unlinkedUsers;
}

User ReadData::setUserFavoriteAuthors(User unlinkedUser, AuthorList& authorList, UserData userDataStr)
{
    stringstream  userData;
    userData << userDataStr;
    userData << SAME_DATA_DELIMITER;
    Authors authors;
    AnAuthor anAuthor;
    Id authorId;
    while (getline(userData, anAuthor, SAME_DATA_DELIMITER))
    {
        authorId = stoi(anAuthor);
        for (int j = 0; j < authorList.size(); j++)
            if (authorId == authorList[j].getId())
                authors.push_back(&authorList[j]);
    }
    unlinkedUser.setAuthors(authors);
    return unlinkedUser;
}

UserList ReadData::linkUserShelf(UserList unlinkedUsers, BookList& bookList)
{
    ifstream usersData;
    usersData.open(usersFileAddress);
    UserData userData;
    getline(usersData, userData);
    int i = 0;
    while (getline(usersData, userData, DELIMITER))
    {
        getline(usersData, userData, DELIMITER);
        getline(usersData, userData, DELIMITER);
        getline(usersData, userData, DELIMITER);
        getline(usersData, userData, DELIMITER);
        getline(usersData, userData, DELIMITER);
        getline(usersData, userData);
        unlinkedUsers[i] = setUserShelf(unlinkedUsers[i], bookList, userData);
        i++;
    }
    return unlinkedUsers;
}

User ReadData::setUserShelf(User unlinkedUser, BookList& bookList, UserData userDataStr)
{
    Books read;
    Books currentlyReading;
    Books wantToRead;
    stringstream  userData;
    userData << userDataStr;
    UserData booksStr;
    getline(userData, booksStr, DELIMITER);
    wantToRead = makeBookList(bookList, booksStr);
    getline(userData, booksStr, DELIMITER);
    currentlyReading = makeBookList(bookList, booksStr);
    getline(userData, booksStr);
    read = makeBookList(bookList, booksStr);
    Shelf userShelf(read, currentlyReading, wantToRead);
    unlinkedUser.setShelf(userShelf);
    return unlinkedUser;
}

Books ReadData::makeBookList(BookList& bookList, UserData userDataStr)
{
    Books books;
    stringstream  booksData;
    booksData << userDataStr;
    booksData << SAME_DATA_DELIMITER;
    BookData bookname;
    Id bookId;
    while (getline(booksData, bookname, SAME_DATA_DELIMITER))
    {
        bookId = stoi(bookname);
        for (int i = 0; i < bookList.size(); i++)
            if (bookId == bookList[i].getId())
                books.push_back(&bookList[i]);
    }
    return books;
}

GenreList ReadData::makeGenreList(BookData genresDataStr)
{
    GenreList genres;
    AGenre genre;
    stringstream  genresData;
    genresData << genresDataStr;
    genresData << SAME_DATA_DELIMITER;
    while (getline(genresData, genre, SAME_DATA_DELIMITER))
        genres.push_back(genre);
    return genres;
}

UserList ReadData::readUserReview(UserList unlinkedUsers, BookList& unlinkedBooks)
{
    ifstream reviewData;
    reviewData.open(reviewsFileAddress);
    Data userReviewStr;
    Data readPart;
    stringstream reviewDataStream;
    Id userId;
    getline(reviewData, readPart);
    while (getline(reviewData, readPart, DELIMITER))
    {
        userReviewStr.append(readPart);
        userReviewStr.append(COMMA);        
        getline(reviewData, readPart, DELIMITER);
        userReviewStr.append(readPart);
        userReviewStr.append(COMMA);        
        getline(reviewData, readPart, DELIMITER);
        userReviewStr.append(readPart);
        userReviewStr.append(COMMA);
        userId = stoi(readPart);
        getline(reviewData, readPart, DELIMITER);
        userReviewStr.append(readPart);
        userReviewStr.append(COMMA);
        getline(reviewData, readPart, DELIMITER);
        userReviewStr.append(readPart);
        userReviewStr.append(COMMA);
        getline(reviewData, readPart);
        userReviewStr.append(readPart);
        userReviewStr.append(COMMA);
        for (int i = 0; i < unlinkedUsers.size(); i++)
        {
            if (userId == unlinkedUsers[i].getId())
            {
                unlinkedUsers[i].setReview(readReview(unlinkedBooks, userReviewStr));
                break;
            }
        }
        userReviewStr = "";
    }          
    return unlinkedUsers;
}

Review ReadData::readReview(BookList& unlinkedBooks, UserData userReviewStr)
{
    Data readPart;
    Id reviewId;
    int rating;
    Date date;
    Id bookId;
    Book* book;
    int numberOfLikes;
    stringstream reviewDataStream;
    reviewDataStream << userReviewStr;
    getline(reviewDataStream, readPart, DELIMITER);
    reviewId = stoi(readPart);
    getline(reviewDataStream, readPart, DELIMITER);
    bookId = stoi(readPart);
    for (int i = 0; i < unlinkedBooks.size(); i++)
        if (bookId == unlinkedBooks[i].getId())
            book = &unlinkedBooks[i];
    getline(reviewDataStream, readPart, DELIMITER);
    getline(reviewDataStream, readPart, DELIMITER);
    rating = stoi(readPart);
    getline(reviewDataStream, date, DELIMITER);
    getline(reviewDataStream, readPart, DELIMITER);
    numberOfLikes = stoi(readPart);
    return Review(reviewId, book, rating, date, numberOfLikes);
}

UserList ReadData::setUserFollowingsFollowers(UserList& unlinkedUsers)
{
    ifstream followData;
    followData.open(followEdgesFileAddress);
    Data readData;
    Id userId;
    getline(followData, readData);
    while (getline(followData, readData, DELIMITER))
    {
        userId = stoi(readData);
        Users followingUsers, followerUsers;
        getline(followData, readData, DELIMITER);
        if (readData != "")
            followingUsers = readFollowData(&unlinkedUsers, readData);
        getline(followData, readData);
        if (readData != "")
            followerUsers = readFollowData(&unlinkedUsers, readData);
        findUserById(&unlinkedUsers, userId)->setFollowUsers(followingUsers, followerUsers);
    }
    return unlinkedUsers;
}

User* ReadData::findUserById(UserList* allUsers, Id userId)
{
    for (int i = 0; i < (*allUsers).size(); i++)
        if ((*allUsers)[i].getId() == userId)
            return &(*allUsers)[i];
}

Users ReadData::readFollowData(UserList* allUsers, Data followDataStr)
{
    stringstream followDataStream;
    followDataStream << followDataStr;
    followDataStream << SAME_DATA_DELIMITER;
    Data readData;
    Id userId;
    Users users;
    while (getline(followDataStream, readData, SAME_DATA_DELIMITER))
    {
        userId = stoi(readData);
        users.push_back(findUserById(allUsers, userId));
    }
    return users;
}

