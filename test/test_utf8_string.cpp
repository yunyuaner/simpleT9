#include <iostream>
#include <string>
#include "../data/utf8_string/src/utf8_string.hpp"
#include "../data/utf8_string/src/utf8_iterator.hpp"


int main() 
{
    const std::string word_list = "我握窝蜗涡沃挝卧斡倭莴喔幄渥肟硪龌";
    UTF8string str(word_list);
    
    for (auto s : str) {
        std::cout << "-> " << s << std::endl;
    }
    return 0;
}
