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
