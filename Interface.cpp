#include "Interface.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Interface::Interface(GoodReads* gD)
{
    goodReads = gD;
}

void Interface::getOrder()
{
    string order;
    while (cin >> order)
    {
        if (order == SHOW_AUTHOR_INFO)
            showAuthrorInfo();
        if (order == SHOW_SORTED_SHELF)
            showSortedShelf();
        if (order == CREDIT)
            showUserCredit();
        if (order == BEST_BOOK)
            showBestBook();
        if (order == BEST_REVIEWER)
            showBestReviewer();
        if (order == RECOMMEND_FIRST_APPROACH)
            showRecommendedBook();
        if (order == RECOMMEND_SECOND_APPROACH)
            showRecommendedBookByFollowing();
    }
}

void Interface::showAuthrorInfo()
{
    Id authorId;
    cin >> authorId;
    goodReads->showAuthorInfo(authorId);
}

void Interface::showSortedShelf()
{
    Id userId;
    cin >> userId;
    string shelfType;
    cin >> shelfType;
    char temp;
    cin.get(temp);
    AGenre genre;
    getline(std::cin, genre);
    goodReads->showSortedShelf(userId, shelfType, genre);
}

void Interface::showUserCredit()
{
    Id userId;
    cin >> userId;
    goodReads->showUserCredit(userId);
}

void Interface::showBestBook()
{
    goodReads->showBestBook();
}
void Interface::showBestReviewer()
{
    goodReads->showBestReviewer();
}

void Interface::showRecommendedBook()
{
    Id userId;
    cin >> userId;
    goodReads->showRecommandedBookForUser(userId);
}

void Interface::showRecommendedBookByFollowing()
{
    Id userId;
    cin >> userId;
    goodReads->showRecommendedBookUsingFollowings(userId);
}
