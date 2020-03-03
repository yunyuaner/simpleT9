#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "vocabulary.h"

const std::string Vocabulary::dsFile = "./data/ds/pinyin_vocabulary_map.txt";

Vocabulary::Vocabulary() : a_return_candidate_list(new QVector<QString>)
{

}

Vocabulary::~Vocabulary()
{
    for (auto iter = a_expected_map.begin(); iter != a_expected_map.end(); iter++) {
        std::vector<std::string> *_v = iter->second;
        if (_v != nullptr) {
            delete _v;
        }
    }

    delete a_return_candidate_list;
}

void Vocabulary::init()
{
    std::fstream fs;
    fs.open(Vocabulary::dsFile, std::fstream::in);
    std::string line;

    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(fs, line)) {
        //std::cout << line << std::endl;
        std::istringstream tokenStream(line);
        while (std::getline(tokenStream, token, '-')) {
            token.erase(remove(token.begin(), token.end(), ' '), token.end());
            //std::cout << token << std::endl;
            tokens.push_back(token);
        }

        //std::cout << tokens[0] << "<->" << tokens[1] << std::endl;

        std::string &_k = tokens[0];
        if (a_expected_map.find(_k) != a_expected_map.end()) {
            std::vector<std::string> *_v = a_expected_map[_k];
            _v->push_back(tokens[1]);
        } else {
            std::vector<std::string> *_v = new std::vector<std::string>;
            _v->push_back(tokens[1]);
            a_expected_map.insert({_k, _v});
        }

        tokens.clear();
    }

#if 0
    for (auto iter = a_expected_map.begin(); iter != a_expected_map.end(); iter++) {
        std::cout << iter->first;
        std::vector<std::string> *_v = iter->second;
        for (std::string &_s : *_v) {
            std::cout << _s << " ";
        }

        std::cout << std::endl;
    }
#endif

    fs.close();
}

QVector<QString> *Vocabulary::search(QString pinyin)
{
    std::string _pinyin = pinyin.toStdString();
    auto iter = a_expected_map.find(_pinyin);

    std::cout << "Search - " << _pinyin << std::endl;

    a_return_candidate_list->clear();
    
    if (iter == a_expected_map.end()) {
        std::cout << _pinyin << " not found" << std::endl;
        return nullptr;
    } else {
        std::vector<std::string> *_v = a_expected_map[_pinyin];

        for (std::string &_s : *_v) {
            a_return_candidate_list->append(QString::fromStdString(_s));
        }

        return a_return_candidate_list;
    }
}
