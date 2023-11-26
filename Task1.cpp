#include <iostream>
#include <deque>
#include <string>
using namespace std;

static const int MAXIMUM_USER_ID = 1e+5 + 1;
static const size_t MAXIMUM_PAGE_NUMBER = 1000;

class Ebook {
public:
    Ebook() : user_page_count_(MAXIMUM_PAGE_NUMBER, 0), user_id_pages_(MAXIMUM_USER_ID, 0) {}

    double CalculateRatio(int user_id);
    void ReadPages(int user_id, size_t pages);
private:
    std::deque<int> user_page_count_;
    std::deque<size_t> user_id_pages_;
    int user_count_ = 0;
};


double Ebook::CalculateRatio(int user_id)
{
    if (!user_id_pages_[user_id])
    {
        return 0.0;

    }
    else if (!(user_count_ - 1))
    {
        return 1.0;

    }
    else
    {
        size_t pages_to_user = user_id_pages_[user_id];
        if (user_count_ == user_page_count_[pages_to_user - 1])
        {
            return 0.0;
        }
        else
        {
            return (user_count_ - user_page_count_[pages_to_user - 1]) / (user_count_ * 1.0 - 1.0);
        }
    }
}
void Ebook::ReadPages(int user_id, size_t pages)
{
    size_t prev_page_count = 0;
    if (user_id_pages_[user_id])
    {
        prev_page_count = user_id_pages_[user_id];
    }
    else
    {
        ++user_count_;
    }

    user_id_pages_[user_id] = pages;
    for (int i = prev_page_count; i < pages; ++i)
    {
        user_page_count_[i] += 1;

    }
}

void ShowInfo(std::istream& input, std::ostream& output, Ebook& book)
{
    std::string str;
    getline(input, str);
    int requests_amount = std::stoi(str);
    for (int i = 0; i < requests_amount; ++i)
    {
        std::string request_type;
        getline(input, request_type, ' ');
        if (request_type[0] == 'R')
        {
            std::string user_id;
            getline(input, user_id, ' ');
            std::string pages;
            getline(input, pages);
            book.ReadPages(std::stoi(user_id), std::stoi(pages));
        }
        else
        {
            std::string user_id;
            getline(input, user_id);
            output << book.CalculateRatio(std::stoi(user_id)) << std::endl;
        }
    }
}

int main() {
    Ebook book;
    ShowInfo(std::cin, std::cout, book);
}