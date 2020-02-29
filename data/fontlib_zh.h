#ifndef FONTLIB_ZH_H
#define FONTLIB_ZH_H
//"拼音输入法汉字排列表"

#include <QHash>
#include <QString>

namespace hycx {
namespace wuhan {
namespace simpleT9 {



/*英文输入查询码表*/
/*
typedef struct
{
    const int key;
    const char* Letter;
}T9EN_IDX;

const T9EN_IDX t9EN_index[] = {
    {2,"abcABC"},
    {3,"defDEF"},
    {4,"ghiGHI"},
    {5,"jklJKL"},
    {6,"mnoMNO"},
    {7,"pqrsPQRS"},
    {8,"tuvTUV"},
    {9,"wxyzWXYZ"}
};
*/
/*拼音输入法查询码表*/

typedef struct
{
    const char *T9;
    const char *PY;
    const unsigned char *MB;
} T9PY_IDX;

int strMatch(unsigned char* str1, unsigned char* str2);
int getMatchedPymb(unsigned char *strin, T9PY_IDX **matchlist);
bool getMatchedPyEn(int nIn, char *matchstr);

const QHash<QString, QString> *init_db();

}}}

#endif // FONTLIB_ZH_H
