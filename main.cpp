#include <iostream>
#include "GoodReads.hpp"
#include "ReadData.hpp"
#include "Interface.hpp"

using namespace std;
 
int main(int argc, char* argv[])
{        
    ReadData readData(argv[1]);
    UserList users = readData.readUserListDataFromFile();
    BookList books = readData.readBookListDataFromFile();
    AuthorList authors = readData.readAuthorListDataFromFile();
    GoodReads goodReads(books, users, authors, readData);
    Interface interface(&goodReads);
    interface.getOrder();
    return 0;
}