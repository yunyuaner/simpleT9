#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include "../data/utf8_string/src/utf8_string.hpp"
#include "../data/utf8_string/src/utf8_iterator.hpp"

const static std::string sample_file = "dictionary.bin";

bool is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}

extern uint32_t __builtin_bswap32 (uint32_t x);

uint32_t cpu_to_big_endian(uint32_t rhs)
{
    if (is_big_endian()) {
        return rhs;
    } else {
        return __builtin_bswap32(rhs);
    }
}

uint32_t big_endian_to_cpu(uint32_t rhs)
{
    if (is_big_endian()) {
        return rhs;
    } else {
        return __builtin_bswap32(rhs);
    }
}

#define _size(_s) cpu_to_big_endian(_s)
#define size_(_s) big_endian_to_cpu(_s)

void map_serialize()
{
    std::string pinyin = "ba'ba";
    std::string pinyin_trans;

    for (auto iter = pinyin.begin(); iter != pinyin.end(); iter++) {
        pinyin_trans.append(1, ~(*iter));
    }

    std::pair<std::string ,int> a_pair = {"爸爸", 200};
    std::pair<std::string, int> another_pair = {"粑粑", 120};
    std::map<std::string, std::set<std::pair<std::string, int>>> a_map;
    std::set<std::pair<std::string ,int>> a_set;

    a_set.insert(a_pair);
    a_set.insert(another_pair);
    a_map.insert({pinyin, a_set});

    std::ofstream outfile(sample_file, std::ofstream::binary);
    
    uint32_t pinyin_size = pinyin_trans.size();
    uint32_t pinyin_size_big_endian = _size(pinyin_size);

    outfile.write(reinterpret_cast<char *>(&pinyin_size_big_endian), sizeof(uint32_t));
    outfile.write(pinyin_trans.c_str(), pinyin_size);

    uint32_t set_size = _size(a_set.size());
    outfile.write(reinterpret_cast<char *>(&set_size), sizeof(uint32_t));

    std::cout << "set_size - " << set_size << std::endl;

    for (auto _pair : a_set) {
        std::string word = _pair.first;
        uint32_t freq = static_cast<uint32_t>(_pair.second);
        uint32_t freq_big_endian = _size(freq);

        uint32_t word_size = word.size();
        uint32_t word_size_big_endian = _size(word_size);
        
        outfile.write(reinterpret_cast<char *>(&word_size_big_endian), sizeof(uint32_t));
        outfile.write(word.c_str(), word_size);

        outfile.write(reinterpret_cast<char *>(&freq_big_endian), sizeof(uint32_t));
    }

    outfile.close();
}

static char a_buf[8192];

void map_deserialize()
{
    std::ifstream infile (sample_file, std::ofstream::binary);

    uint32_t pinyin_size;
    
    infile.read(reinterpret_cast<char *>(&pinyin_size), sizeof(uint32_t));
    pinyin_size = size_(pinyin_size);
    infile.read(a_buf, pinyin_size);
    a_buf[pinyin_size] = '\0';
    
    std::string pinyin_trans(a_buf);
    std::string pinyin;

    for (auto iter = pinyin_trans.begin(); iter != pinyin_trans.end(); iter++) {
        pinyin.append(1, ~(*iter));
    }

    std::cout << pinyin << std::endl;
    
    uint32_t set_size;
    infile.read(reinterpret_cast<char *>(&set_size), sizeof(uint32_t));
    set_size = size_(set_size);

    for (unsigned int i = 0; i < set_size; i++) {
        uint32_t word_size;
        infile.read(reinterpret_cast<char *>(&word_size), sizeof(uint32_t));
        word_size = size_(word_size);

        infile.read(a_buf, word_size);
        a_buf[word_size] = '\0';
        std::string word(a_buf);

        int32_t freq;
        infile.read(reinterpret_cast<char *>(&freq), sizeof(uint32_t));
        freq = size_(freq);

        std::cout << word << ", " << freq << std::endl;
    }
    
    infile.close();

}

int main()
{
    map_serialize();
    map_deserialize();
}
