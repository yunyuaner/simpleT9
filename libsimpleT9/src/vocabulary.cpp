/**
 *      Copyright (c) 2020 Jia Guo <jiag@ntesec.com.cn>
 *          
 *          Shang Hai Hua Yuan Chuang Xin Co., Ltd
 *                  All Right Reserved
 * 
 *  simpleT9 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3
 *  as published by the Free Software Foundation.
 *   
 *  simpleT9 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  version 3 along with simpleT9; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>
#include <QDebug>
#include <cstring>
#include "vocabulary.h"
#include "utf8_string.hpp"
#include "utf8_iterator.hpp"

namespace hycx {
namespace libsimpleT9 {

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
        return ::__builtin_bswap32(rhs);
    }
}

uint32_t big_endian_to_cpu(uint32_t rhs)
{
    if (is_big_endian()) {
        return rhs;
    } else {
        return ::__builtin_bswap32(rhs);
    }
}

#define _size(_s) cpu_to_big_endian(_s)
#define size_(_s) big_endian_to_cpu(_s)

const std::string SimpleVocabulary::pinyin_vocalbulary_map = "./data/ds/pinyin_vocabulary_map.txt";
const std::string SimpleVocabulary::pinyin_hanzi_map_small = "./data/ds/pinyin_hanzi_map_small.txt";
const std::string SimpleVocabulary::pinyin_hanzi_map_large = "./data/ds/pinyin_hanzi_map_large.txt";

const std::string SimpleVocabulary::THUOCL_animal = "./data/ds/THUOCL/THUOCL_animal.txt";
const std::string SimpleVocabulary::THUOCL_caijing = "./data/ds/THUOCL/THUOCL_caijing.txt";
const std::string SimpleVocabulary::THUOCL_car = "./data/ds/THUOCL/THUOCL_car.txt";
const std::string SimpleVocabulary::THUOCL_chengyu = "./data/ds/THUOCL/THUOCL_chengyu.txt";
const std::string SimpleVocabulary::THUOCL_diming = "./data/ds/THUOCL/THUOCL_diming.txt";
const std::string SimpleVocabulary::THUOCL_food = "./data/ds/THUOCL/THUOCL_food.txt";
const std::string SimpleVocabulary::THUOCL_it = "./data/ds/THUOCL/THUOCL_it.txt";
const std::string SimpleVocabulary::THUOCL_law = "./data/ds/THUOCL/THUOCL_law.txt";
const std::string SimpleVocabulary::THUOCL_lishimingren = "./data/ds/THUOCL/THUOCL_lishimingren.txt";
const std::string SimpleVocabulary::THUOCL_medical = "./data/ds/THUOCL/THUOCL_medical.txt";
const std::string SimpleVocabulary::THUOCL_poem = "./data/ds/THUOCL/THUOCL_medical.txt";

const std::string SimpleVocabulary::dictionary_file = "./data/dictionary.bin";
char SimpleVocabulary::a_buf[8192];

SimpleVocabulary::SimpleVocabulary() : a_return_candidate_list(new QVector<QString>)
{
}

SimpleVocabulary::~SimpleVocabulary()
{
    for (auto iter = a_expected_map.begin(); iter != a_expected_map.end(); iter++) {
        std::set<std::string> *_v = iter->second;
        if (_v != nullptr) {
            delete _v;
        }
    }

    delete a_return_candidate_list;
}

void SimpleVocabulary::show()
{
    for (auto iter = a_expected_map.begin(); iter != a_expected_map.end(); iter++) {
        std::cout << iter->first << " - ";
        std::set<std::string> *_v = iter->second;
        for (std::string _s : *_v) {
            std::cout << _s << " ";
        }

        std::cout << std::endl;
    }
}

bool SimpleVocabulary::split_by_hiphen(std::string &line, std::vector<std::string> &tokens)
{
    std::istringstream tokenStream(line);
    std::string token;
    
    while (std::getline(tokenStream, token, '-')) {
        token.erase(remove(token.begin(), token.end(), ' '), token.end());
        tokens.push_back(token);
    }

    if (tokens.size() != 2) {
        std::cout << "invalid parsing on - '" << line << "'" << std::endl;
        return false;
    } else {
        return true;
    }
}

void SimpleVocabulary::map_insert(std::string key, std::string value_item)
{
    if (a_expected_map.find(key) != a_expected_map.end()) {
        std::set<std::string> *a_value = a_expected_map[key];
        a_value->insert(value_item);
    } else {
        std::set<std::string> *a_value_set = new std::set<std::string>;
        a_value_set->insert(value_item);
        a_expected_map.insert({key, a_value_set});
    }
}

void SimpleVocabulary::map_insert(std::string key, std::set<std::string> *value_items)
{
    if (a_expected_map.find(key) != a_expected_map.end()) {
        std::cout << "duplicated pinyin found - '" << key << "'" << std::endl; 
    } else {
        a_expected_map.insert({key, value_items});
    }
}

void SimpleVocabulary::parse_chinese_volcabulary(const std::string filename)
{
    std::fstream fs;
    std::string line;
    std::vector<std::string> tokens;
    
    fs.open(filename, std::fstream::in);
    
    while (std::getline(fs, line)) {
        if (!split_by_hiphen(line, tokens)) {
            continue;
        }
        
        map_insert(tokens[0], tokens[1]);
        tokens.clear();
    }

    fs.close();
}

void SimpleVocabulary::parse_chinese_word(const std::string filename)
{
    std::fstream fs;
    std::string line;
    std::vector<std::string> tokens;
    
    fs.open(filename, std::fstream::in);
    
    while (std::getline(fs, line)) {
        if (!split_by_hiphen(line, tokens)) {
            continue;
        }
      
        std::string &a_key = tokens[0];
        UTF8string word_list(tokens[1]);        
        
        std::set<std::string> *a_set = new std::set<std::string>;
        for (auto word : word_list) {
            a_set->insert(word);
        }
        
        map_insert(a_key, a_set);
        tokens.clear();
    }

    fs.close(); 
}

void SimpleVocabulary::map_deserialize()
{
    std::ifstream infile (SimpleVocabulary::dictionary_file, std::ofstream::binary);

    uint32_t map_size;

    infile.read(reinterpret_cast<char *>(&map_size), sizeof(uint32_t));
    map_size = size_(map_size);

    for (unsigned int i = 0; i < map_size; i++) {
        uint32_t pinyin_size;
        
        infile.read(reinterpret_cast<char *>(&pinyin_size), sizeof(uint32_t));
        pinyin_size = size_(pinyin_size);
        
        infile.read(SimpleVocabulary::a_buf, pinyin_size);
        SimpleVocabulary::a_buf[pinyin_size] = '\0';
        
        std::string pinyin_trans(SimpleVocabulary::a_buf);
        std::string pinyin;

        for (auto iter = pinyin_trans.begin(); iter != pinyin_trans.end(); iter++) {
            pinyin.append(1, ~(*iter));
        }

        //std::cout << pinyin << std::endl;

        std::set<std::pair<std::string ,int>> *a_set;
        if (a_word_frequency_map.find(pinyin) != a_word_frequency_map.end()) {
            a_set = a_word_frequency_map[pinyin];
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

            infile.read(SimpleVocabulary::a_buf, word_size);
            SimpleVocabulary::a_buf[word_size] = '\0';
            std::string word(SimpleVocabulary::a_buf);

            int32_t freq;
            infile.read(reinterpret_cast<char *>(&freq), sizeof(uint32_t));
            freq = size_(freq);

            //std::cout << word << ", " << freq << std::endl;
            std::pair<std::string, int> a_pair = {word, freq};

            a_set->insert(a_pair);
        }

        if (a_word_frequency_map.find(pinyin) == a_word_frequency_map.end()) {
            a_word_frequency_map.insert({pinyin, a_set});
        }
    }
    
    infile.close();

}

void SimpleVocabulary::init()
{
    parse_chinese_word(SimpleVocabulary::pinyin_hanzi_map_small);
    parse_chinese_volcabulary(SimpleVocabulary::pinyin_vocalbulary_map);
    
    for (auto iter = a_expected_map.begin(); iter != a_expected_map.end(); iter++) {
        a_compound_pinyin_set.insert(iter->first);
    }

    //for (std::string str : a_compound_pinyin_set) {
    //    std::cout << str << std::endl;
    //}
}

void SimpleVocabulary::init1()
{
    map_deserialize();

    for (auto iter = a_word_frequency_map.begin(); iter != a_word_frequency_map.end(); iter++) {
        a_compound_pinyin_set.insert(iter->first);
    }

    /*
     * http://www.cplusplus.com/reference/set/set/
     *
     * Internally, the elements in a set are always sorted following 
     * a specific strict weak ordering criterion indicated by its 
     * internal comparison object (of type Compare).
     */

    /* @a_compound_pinyin_set is now in alphabatical order */

    //for (std::string str : a_compound_pinyin_set) {
    //    std::cout << str << std::endl;
    //}
}

QVector<QString> *SimpleVocabulary::search(QString pinyin)
{
    std::string _pinyin = pinyin.toStdString();
    auto iter = a_expected_map.find(_pinyin);

    qDebug() << "Search - " << _pinyin.c_str();

    a_return_candidate_list->clear();
    
    if (iter == a_expected_map.end()) {
        qDebug() << QString::fromStdString(_pinyin) << " not found";
        return nullptr;
    } else {
        std::set<std::string> *_v = a_expected_map[_pinyin];

        for (std::string _s : *_v) {
            a_return_candidate_list->append(QString::fromStdString(_s));
        }

        return a_return_candidate_list;
    }
}

QVector<QString> *SimpleVocabulary::search1(QString pinyin)
{
    std::string _pinyin = pinyin.toStdString();
    auto iter = a_word_frequency_map.find(_pinyin);

    qDebug() << "Search - " << _pinyin.c_str();

    a_return_candidate_list->clear();
    
    if (iter == a_word_frequency_map.end()) {
        qDebug() << QString::fromStdString(_pinyin) << " not found, use ambiguous search";
        //return nullptr;
        return ambiguous_search(pinyin);
    } else {
        std::set<std::pair<std::string, int>> *_v = a_word_frequency_map[_pinyin];

        for (auto _s : *_v) {
            a_return_candidate_list->append(QString::fromStdString(_s.first));
        }

        return a_return_candidate_list;
    }
}

QVector<QString> *SimpleVocabulary::ambiguous_search(QString pinyin)
{
    std::string _pinyin = pinyin.toStdString();

    for (std::string str : a_compound_pinyin_set) {
        int result = str.compare(0, _pinyin.size(), _pinyin);
#if 0
        qDebug() << "ambiguous search on - " 
                 << QString::fromStdString(str) 
                 << ", _pinyin - " 
                 << QString::fromStdString(_pinyin) 
                 << ", size - " 
                 << _pinyin.size()
                 << ", str - "
                 << QString::fromStdString(str)
                 << ", size - "
                 << str.size()
                 << ", result - "
                 << result;
#endif   
        if (result == 0) {
            std::set<std::pair<std::string, int>> *_v = a_word_frequency_map[str];

            for (auto _s : *_v) {
                a_return_candidate_list->append(QString::fromStdString(_s.first));
            }

            if (a_return_candidate_list->size() < 30) {
                continue;
            } else {
                return a_return_candidate_list;
            }
        }
    }

    if (a_return_candidate_list->size() == 0) {
        qDebug() << QString::fromStdString(_pinyin) << " not found in ambiguous search";
    }

    return a_return_candidate_list->size() > 0 ? a_return_candidate_list : nullptr;
}

}} /* namespace */
