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
 *  version 3 along with MediaTomb; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "vocabulary.h"
#include <QDebug>

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

    qDebug() << "Search - " << _pinyin.c_str();

    a_return_candidate_list->clear();
    
    if (iter == a_expected_map.end()) {
        qDebug() << QString::fromStdString(_pinyin) << " not found";
        return nullptr;
    } else {
        std::vector<std::string> *_v = a_expected_map[_pinyin];

        for (std::string &_s : *_v) {
            a_return_candidate_list->append(QString::fromStdString(_s));
        }

        return a_return_candidate_list;
    }
}
