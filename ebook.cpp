#include <iostream>
#include <vector>
#include <string>

using uint = unsigned int;

const uint MAX_USER_ID = 1e5;
const uint MAX_BOOK_PAGE = 1e3;

class ReadingStimulator {
public:
    ReadingStimulator() : users_on_page_(MAX_BOOK_PAGE, 0),
        pages_by_user_(MAX_USER_ID, 0) {}

    void Read(uint user_id, uint count_pages);

    double Cheer(uint user_id);

private:
    std::vector<uint> users_on_page_;
    std::vector<uint> pages_by_user_;

    uint count_people_ = 0;
};

void ReadingStimulator::Read(uint user_id, uint count_pages) {

    if (pages_by_user_[user_id] == 0) { ++count_people_; }

    for (uint i = pages_by_user_[user_id]; i < count_pages; ++i) {
        ++users_on_page_[i];
    }

    pages_by_user_[user_id] = count_pages;
}

double ReadingStimulator::Cheer(uint user_id) {

    if (pages_by_user_[user_id] == 0) { return 0.0; }

    if (count_people_ == 1) { return 1.0; }

    size_t pages_to_user = pages_by_user_[user_id];
    if (count_people_ == users_on_page_[pages_to_user - 1]) { return 0.0; }

    return (count_people_ - users_on_page_[pages_to_user - 1]) / (count_people_ - 1.0);
}

void ProcessInputRequests(std::istream& input, std::ostream& output, ReadingStimulator& stimulator) {

    using namespace std::literals;

    std::string text;
    std::getline(input, text);

    uint requests_count = std::stoi(text);
    for (size_t i = 0; i < requests_count; ++i) {

        std::string type;
        std::getline(input, type, ' ');
        if (type == "READ"s) {

            std::string user_id;
            std::getline(input, user_id, ' ');

            std::string count_pages;
            std::getline(input, count_pages);

            stimulator.Read(std::stoi(user_id), std::stoi(count_pages));
        }
        else if (type == "CHEER"s) {
            
            std::string user_id;
            std::getline(input, user_id);

            output << stimulator.Cheer(std::stoi(user_id)) << std::endl;
        }
    }
}

int main() {
    ReadingStimulator stimulator;
    ProcessInputRequests(std::cin, std::cout, stimulator);
}
