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

#ifndef _VOCABULARY_H
#define _VOCABULARY_H

#include <QString>
#include <QVector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>

class SimpleVocabulary
{
public:
    SimpleVocabulary();
    ~SimpleVocabulary();

    void init();
    void init1();
    void show();
    QVector<QString> *search(QString pinyin);
    QVector<QString> *search1(QString pinyin);
    QVector<QString> *ambiguous_search(QString pinyin);

private:
    const static std::string pinyin_vocalbulary_map;
    
    const static std::string pinyin_hanzi_map_small;
    const static std::string pinyin_hanzi_map_large;
    
    const static std::string THUOCL_animal;
    const static std::string THUOCL_caijing;
    const static std::string THUOCL_car;
    const static std::string THUOCL_chengyu;
    const static std::string THUOCL_diming;
    const static std::string THUOCL_food;
    const static std::string THUOCL_it;
    const static std::string THUOCL_law;
    const static std::string THUOCL_lishimingren;
    const static std::string THUOCL_medical;
    const static std::string THUOCL_poem;

    const static std::string dictionary_file;

private:
    bool split_by_hiphen(std::string &line, std::vector<std::string> &tokens);
    void map_insert(std::string key, std::string value_item);
    void map_insert(std::string key, std::set<std::string> *value_items);
    void parse_chinese_volcabulary(const std::string filename);
    void parse_chinese_word(const std::string filename);
    void map_deserialize();

private:
    std::unordered_map< std::string, std::set<std::string> * > a_expected_map;  /* Will be removed later */
    std::set<std::string> a_compound_pinyin_set;
    QVector<QString> *a_return_candidate_list;
    
    /**
     * @a_word_frequency_map structure:
     * { pinyin -> [ <words, frequency>, <words, frequency>, ... , <words, frequency> ] }
     */
    std::map< std::string, std::set<std::pair<std::string, int>> * > a_word_frequency_map;

    static char a_buf[8192];
};

#endif /* _VOCABULARY_ */
