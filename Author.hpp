#ifndef AUTHOR_H
#define AUTHOR_H "AUTHOR_H"

#include <iostream>
#include <vector>

typedef std::string Country;
typedef std::string Date;
typedef std::vector<std::string> GenreList;
typedef int Id;
typedef int Year;       
enum Gender {male, female};

class Author
{
public:
    Author(Id id, std::string n, Gender gend, Date memSince, Year yearOB, Country placeOB, GenreList genr);
    void printAuthorInfo();
    void printGenres();
    void printBooksId();
    Id getId();
    std::string getName();

private:
    Id authorId;
    std::string name;
    Gender gender;
    Date memberSince;
    Year yearOfBirth;
    Country placeOfBirth;
    GenreList genres;
};

#endif