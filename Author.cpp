#include "Author.hpp"
#include "functions.hpp"
#include <iostream>

using namespace std;

Author::Author(Id id, std::string n, Gender gend, Date memSince, Year yearOB, Country placeOB, GenreList genr)
{
    authorId = id;
    name = n;
    gender = gend;
    memberSince = memSince;
    yearOfBirth = yearOB;
    placeOfBirth = placeOB;
    genres = genr;
}

void Author::printAuthorInfo()
{
    cout << "id: " << authorId << endl;
    cout << "Name: " << name << endl;
    cout << "Year of Birth: " << yearOfBirth << endl;
    cout << "Place of Birth: " << placeOfBirth << endl;
    cout << "Member Since: " << memberSince << endl;
    printGenres();
}

void Author::printGenres()
{
    cout << "Genres: " ;
    sort(genres.begin(), genres.end(), prioritizeGenresName);
    for(int i = 0; i < genres.size() - 1; i++)
        cout << genres[i] << ", " ;
    cout << genres[genres.size() - 1] << endl;
}

void Author::printBooksId()
{
}

Id Author::getId()
{
    return authorId;
}

string Author::getName()
{
    return name;
}