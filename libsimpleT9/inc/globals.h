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

#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <QString>
#include <QHash>

class simpleT9glb 
{
public:
    static const QString key_0_name;
    static const QString key_1_name;
    static const QString key_2_name;
    static const QString key_3_name;
    static const QString key_4_name;
    static const QString key_5_name;
    static const QString key_6_name;
    static const QString key_7_name;
    static const QString key_8_name;
    static const QString key_9_name;

    static const QString key_f1_name;
    static const QString key_f2_name;
    static const QString key_f3_name;
    static const QString key_f4_name;
    static const QString key_f5_name;
    static const QString key_f6_name;
    static const QString key_f7_name;
    static const QString key_f8_name;
    static const QString key_f9_name;
    static const QString key_f10_name;

    static const QString key_up_name;
    static const QString key_down_name;
    static const QString key_left_name;
    static const QString key_right_name;
    static const QString key_page_up_name;
    static const QString key_page_down_name;
    static const QString key_delete_name;
    static const QString key_space_name;
    static const QString key_return_name;
    static const QString key_backspace_name;
    static const QString key_exit_name;
    static const QString key_confirm_name;
    static const QString key_hyphen_name;
    static const QString key_dot_name;

	static const QString key_up_value;
    static const QString key_down_value;
    static const QString key_left_value;
    static const QString key_right_value;
    static const QString key_page_up_value;
    static const QString key_page_down_value;
    static const QString key_delete_value;
    static const QString key_space_value;
    static const QString key_return_value;
    static const QString key_backspace_value;
    static const QString key_exit_value;
    static const QString key_confirm_value;
    static const QString key_hyphen_value;
    static const QString key_dot_value;

    static const QString key_f1_value;
    static const QString key_f2_value;
    static const QString key_f3_value;
    static const QString key_f4_value;
    static const QString key_f5_value;
    static const QString key_f6_value;
    static const QString key_f7_value;
    static const QString key_f8_value;
    static const QString key_f9_value;
    static const QString key_f10_value;

	static const QHash<int, QString> key_0_value;
	static const QHash<int, QString> key_1_value;
	static const QHash<int, QString> key_2_value;
	static const QHash<int, QString> key_3_value;
	static const QHash<int, QString> key_4_value;
	static const QHash<int, QString> key_5_value;
	static const QHash<int, QString> key_6_value;
	static const QHash<int, QString> key_7_value;
	static const QHash<int, QString> key_8_value;
	static const QHash<int, QString> key_9_value;

	static const QString key_punctuation_candidate;

    static const int multi_purpose_key_start;
    static const int multi_purpose_key_end;

    static const int digit_key_start;
    static const int digit_key_end;

    static const int max_chinese_char_candidate_per_page;
    static const char *ime_title_string;

	static const QString key_role_type_chinese_text;
	static const QString key_role_type_english_text;
	static const QString key_role_type_english_capital_text;
	static const QString key_role_type_digit_text;
    static const QString key_role_type_punctuation_text;

    static const int continuous_key_press_timeout;

	static const int input_method_count;

	static const QHash<int, QString> a_key_code_to_key_name_map;
};

#endif /* _GLOBALS_H */
