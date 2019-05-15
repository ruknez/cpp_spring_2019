#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

const std::string file_name = "lolo.txt";
using my_map = std::map <std::string, int>;

void readfile (my_map &voc);
void show_result (const my_map &voc);

int main () {

    my_map my_voc;

    readfile (my_voc);
/*
    for (const auto & m : my_voc) {
        std::cout << m.first << " " << m.second << std::endl;
    }
*/
    show_result (my_voc);

    return 0;
}



void readfile (my_map &voc) {

    std::ifstream read_file(file_name);
    if (!read_file.is_open()) {
        std::cerr << "Fiel " << file_name << " is NOT open ! \n";
        exit(1);
    }

    std::string a;
    while (read_file >> a) {
        //std::cout << "a = " << a << std::endl;

        auto search = voc.find(a);

        if (search != voc.end()) {
            search->second++;
            //std::cout << "Found " << search->first << " " << search->second << '\n';
        } else {
            voc [a] = 1;
        }
    }
}


void show_result (const my_map &voc) {
    
    std::vector<std::pair<int, std::string>> items (voc.size ());
    
    int count = 0;
    for (const auto & m : voc) {
        items [count].first = m.second;
        items [count].second = m.first;
        count++;
    }

    auto cmp = [](std::pair<int, std::string> const & a, std::pair<int, std::string> const & b) { 
        return a.first > b.first;
    };

    sort (items.begin (), items.end (), cmp);

    std::cout << "Five of the most common \n";
    for (std::size_t i = 0; i < items.size () && i < 5; i++) {
        std::cout << items [i].first << "  " << items [i].second << std::endl;
    }

    std::cout << "\n \n";
    
    std::cout << "Five last \n";
    for (int i = items.size () - 1; i >= 0 && i - items.size () > -6; i--) {
        std::cout << items [i].first << "  " << items [i].second << std::endl;
    }

}