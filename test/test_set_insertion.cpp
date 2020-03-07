#include <set>
#include <string>
#include <iostream>

int main(int argc, const char *argv[])
{
    std::set<std::string> a_set;
    std::pair<std::set<std::string>::iterator, bool> a_pair;

    a_pair = a_set.insert("nihao");
    if (!a_pair.second) {
        std::cout << "already exist in set" << std::endl;
    } else {
        std::cout << "inserted" << std::endl;
    }
    
    a_pair = a_set.insert("nihao");
    if (!a_pair.second) {
        std::cout << "already exist in set" << std::endl;
    } else {
        std::cout << "inserted" << std::endl;
    }

    for (auto iter = a_set.begin(); iter != a_set.end(); iter++) {
        std::cout << *iter << std::endl;
    }
}
