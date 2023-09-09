#ifndef INTERFACE
#define INTERFACE "INTERFACE"

#include <iostream>
#include <string>
#include "GoodReads.hpp"

const std::string SHOW_AUTHOR_INFO = "show_author_info";
const std::string SHOW_SORTED_SHELF = "show_sorted_shelf";
const std::string CREDIT = "credit";
const std::string BEST_BOOK = "best_book";
const std::string BEST_REVIEWER = "best_reviewer"; 
const std::string RECOMMEND_FIRST_APPROACH = "recommend_first_approach"; 
const std::string RECOMMEND_SECOND_APPROACH = "recommend_second_approach"; 

class Interface
{
public:
    Interface(GoodReads* gD);
    void getOrder();

private:
    void showAuthrorInfo();
    void showSortedShelf();
    void showUserCredit();
    void showBestBook();
    void showBestReviewer();
    void showRecommendedBook();
    void showRecommendedBookByFollowing();

    GoodReads* goodReads;
};

#endif