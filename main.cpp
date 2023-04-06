#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

int main() {
    std::vector<std::pair<std::string, std::tm>> birthdays;

    std::time_t t = std::time(nullptr);
    std::tm * current_date = std::localtime(&t);

    while (true) {
        std::string name;

        std::cout << "Enter name: ";
        std::getline(std::cin, name);

        if ((name == "end" || name == "End") && !birthdays.empty()) {
            break;
        } else if (name == "end" && birthdays.empty()) {
            return 0;
        }


        std::cout << "Enter birthday (YYYY/MM/DD): ";

        std::cin >> std::get_time(current_date, "%Y/%m/%d");

        while (!std::cin) {
            std::cin.clear();
            while (std::cin.get() != '\n')
                continue;
            std::cout << "Wrong format, try again" << std::endl;
            std::cout << "Enter birthday (YYYY/MM/DD): ";
            std::cin >> std::get_time(current_date, "%Y/%m/%d");
        }

        std::cin.get();

        std::pair<std::string, std::tm> b_pair;
        b_pair.first = name;
        b_pair.second = *current_date;

        birthdays.push_back(b_pair);
    }

    current_date = std::localtime(&t);
    std::cout << "Local time: " << std::put_time(current_date, "%d/%m/%Y") << std::endl;


    std::pair<std::string, std::tm> bd_closest_pair = birthdays[0];

    for (size_t i = 0; i < birthdays.size(); i++) {
        if (current_date->tm_mon == birthdays[i].second.tm_mon) {

            if (current_date->tm_mday == birthdays[i].second.tm_mday) {
                bd_closest_pair = birthdays[i];
            } else if (current_date->tm_mday < birthdays[i].second.tm_mday
                     && birthdays[i].second.tm_mday < bd_closest_pair.second.tm_mday) {
                bd_closest_pair = birthdays[i];
            }

        } else if (current_date->tm_mon < birthdays[i].second.tm_mon
                 && birthdays[i].second.tm_mon < bd_closest_pair.second.tm_mon) {
            bd_closest_pair = birthdays[i];

            if (birthdays[i].second.tm_mday < bd_closest_pair.second.tm_mday) {
                bd_closest_pair = birthdays[i];
            }
        }
    }

    std::vector<std::pair<std::string, std::tm>> closest_bd;

    for (size_t i = 0; i < birthdays.size(); i++) {

        if (bd_closest_pair.second.tm_mon == birthdays[i].second.tm_mon
            && bd_closest_pair.second.tm_mday == birthdays[i].second.tm_mday)
        {
            closest_bd.push_back(birthdays[i]);
        }
    }

    if (bd_closest_pair.second.tm_mon < current_date->tm_mon
        || (bd_closest_pair.second.tm_mon == current_date->tm_mon
            && bd_closest_pair.second.tm_mday < current_date->tm_mday)) {
        std::cout << "No closest birthdays" << std::endl;
    } else {
        for (size_t i = 0; i < closest_bd.size(); i++) {
            // специальное сообщение, если день рождения сегодня
            if (closest_bd[i].second.tm_mon == current_date->tm_mon
                && closest_bd[i].second.tm_mday == current_date->tm_mday) {

                std::cout << "This guy's birthday is today: "
                            << closest_bd[i].first << " - "
                            << std::put_time(&closest_bd[i].second, "%d.%m.%Y") << std::endl;

            } else {
                std::cout << "Closest birthday: " << closest_bd[i].first << " - "
                            << std::put_time(&closest_bd[i].second, "%d.%m.%Y") << std::endl;
            }
        }
    }

    return 0;
}