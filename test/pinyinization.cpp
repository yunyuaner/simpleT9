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

const std::string a_word_frequency_map_file = "30wChineseSeqDic_1.txt";
const std::string a_hanzi_pinyin_map_file = "hanzi_pinyin_map.txt";

std::map< std::string, std::set<std::pair<std::string, int>> * > a_word_frequency_map;
std::map< std::string, std::string > a_hanzi_pinyin_map;

bool split_by_hiphen(std::string &line, std::vector<std::string> &tokens)
{
    std::istringstream tokenStream(line);
    std::string token;
    
    while (std::getline(tokenStream, token, '-')) {
        token.erase(remove(token.begin(), token.end(), ' '), token.end());
        tokens.push_back(token);
    }

    if (tokens.size() != 2) {
        std::cout << "invalid parsing on - '" << line << "', count - " << tokens.size() << std::endl;
        return false;
    }

    return true;
}

void parse_hanzi_pinyin_map_file() 
{
    std::fstream fs;
    std::string line;
    std::vector<std::string> tokens;

    fs.open(a_hanzi_pinyin_map_file, std::fstream::in);

    while (std::getline(fs, line)) {
        if (! (!split_by_hiphen(line, tokens) && (a_hanzi_pinyin_map.find(tokens[0]) != a_hanzi_pinyin_map.end()))){
            a_hanzi_pinyin_map.insert(std::pair<std::string, std::string>(tokens[0], tokens[1]));
        }

#if 0
        for (std::string &str : tokens) {
            std::cout << str << std::endl;
        }
#endif

        tokens.clear();
    }

    fs.close();
}

std::string query_pinyin_by_word(UTF8string a_utf8_str)
{
    std::string query_result;
    
    for (auto &str : a_utf8_str) {
        if (a_hanzi_pinyin_map.find(str) != a_hanzi_pinyin_map.end()) {
            std::string pinyin = a_hanzi_pinyin_map[str];
            query_result.append(pinyin + "'");
        }
    }

    query_result.pop_back();

    return query_result;
}

void parse_word_freq_map_file()
{
    std::fstream fs;
    std::string line;
    std::vector<std::string> tokens;

    fs.open(a_word_frequency_map_file, std::fstream::in);

    while (std::getline(fs, line)) {
        if (!split_by_hiphen(line, tokens)) {
            tokens.clear();
            continue;
        }

        UTF8string a_utf8_str(tokens[0]);
        std::string a_segmentation_of_pinyin = query_pinyin_by_word(a_utf8_str);
        
        int freq = std::stoi(tokens[1]);
        std::pair<std::string, int> a_pair = { tokens[0], freq };
        std::set<std::pair<std::string, int>> *a_set;
        
        if (a_word_frequency_map.find(a_segmentation_of_pinyin) != a_word_frequency_map.end()) {
            a_set = a_word_frequency_map[a_segmentation_of_pinyin];
            a_set->insert(a_pair);
        } else {
            a_set = new std::set<std::pair<std::string, int>>;
            a_set->insert(a_pair);
            a_word_frequency_map.insert({a_segmentation_of_pinyin, a_set});
        }
        tokens.clear();
    }

    fs.close();
}

void show_word_freq_map()
{
    for (auto iter = a_word_frequency_map.begin(); iter != a_word_frequency_map.end(); iter++) {
        const std::string &pinyin = iter->first;
        std::cout << pinyin << " -> ";
        
        std::set<std::pair<std::string, int>> *a_set = iter->second;
        for (std::pair<std::string, int> a_pair : *a_set) {
            std::string &hanzi = a_pair.first;
            int freq = a_pair.second;
            std::cout << "{ " << hanzi << ", " << freq << " } ";
        }
        std::cout << std::endl;
    }
}

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

void map_serialize(std::map<std::string, std::set<std::pair<std::string, int>> *> *_map)
{ 
    std::ofstream outfile(sample_file, std::ofstream::binary);

    uint32_t map_size = _map->size();
    uint32_t map_size_big_endian = _size(map_size);
    outfile.write(reinterpret_cast<char *>(&map_size_big_endian), sizeof(uint32_t));

    for (auto iter = _map->begin(); iter != _map->end(); iter++) {
        std::string pinyin = iter->first;
        std::string pinyin_trans;

        std::cout << "Processing - " << pinyin << std::endl;

        for (auto iter = pinyin.begin(); iter != pinyin.end(); iter++) {
            pinyin_trans.append(1, ~(*iter));
        }
        uint32_t pinyin_size = pinyin_trans.size();
        uint32_t pinyin_size_big_endian = _size(pinyin_size);

        outfile.write(reinterpret_cast<char *>(&pinyin_size_big_endian), sizeof(uint32_t));
        outfile.write(pinyin_trans.c_str(), pinyin_size);

        uint32_t set_size = iter->second->size();
        uint32_t set_size_big_endian = _size(set_size);
        outfile.write(reinterpret_cast<char *>(&set_size_big_endian), sizeof(uint32_t));

        std::set<std::pair<std::string, int>> * a_set = iter->second;
        
        for (auto _pair : *a_set) {
            std::string word = _pair.first;
            uint32_t freq = static_cast<uint32_t>(_pair.second);
            uint32_t freq_big_endian = _size(freq);

            uint32_t word_size = word.size();
            uint32_t word_size_big_endian = _size(word_size);
            
            outfile.write(reinterpret_cast<char *>(&word_size_big_endian), sizeof(uint32_t));
            outfile.write(word.c_str(), word_size);

            outfile.write(reinterpret_cast<char *>(&freq_big_endian), sizeof(uint32_t));
        }
    }

    outfile.close();
}

static char a_buf[8192];

void map_deserialize(std::map<std::string, std::set<std::pair<std::string, int>> *> *_map)
{
    std::ifstream infile (sample_file, std::ofstream::binary);

    uint32_t map_size;

    infile.read(reinterpret_cast<char *>(&map_size), sizeof(uint32_t));
    map_size = size_(map_size);

    for (unsigned int i = 0; i < map_size; i++) {
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

        //std::cout << pinyin << std::endl;

        std::set<std::pair<std::string ,int>> *a_set;
        if (_map->find(pinyin) != _map->end()) {
            a_set = (*_map)[pinyin];
        } else {
            a_set = new std::set<std::pair<std::string ,int>>;
        }
        
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

            //std::cout << word << ", " << freq << std::endl;
            std::pair<std::string, int> a_pair = {word, freq};

            a_set->insert(a_pair);
        }

        if (_map->find(pinyin) == _map->end()) {
            _map->insert({pinyin, a_set});
        }
    }
    
    infile.close();

}

void generate_dictionary()
{
    parse_hanzi_pinyin_map_file();
    parse_word_freq_map_file();

    map_serialize(&a_word_frequency_map);
}

void recover_map_from_dictionary()
{
    map_deserialize(&a_word_frequency_map);
    show_word_freq_map();
}

int main()
{
    //generate_dictionary(); 
    recover_map_from_dictionary();
    return 0;
}
