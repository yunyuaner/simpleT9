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

#include <QHash>
#include <QString>
#include <QVector>
#include <string>
#include <unordered_map>
#include <vector>

class Vocabulary
{
public:
    Vocabulary();
    ~Vocabulary();

    void init();
    QVector<QString> *search(QString pinyin);

    static const std::string dsFile;

private:
    std::unordered_map< std::string, std::vector<std::string> * > a_expected_map;
    QVector<QString> *a_return_candidate_list;
};

#endif /* _VOCABULARY_ */
