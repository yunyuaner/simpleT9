#include <Qt>
#include "globals.h"
#include "keyboard.h"

const QString simpleT9glb::key_0_name = "0";
const QString simpleT9glb::key_1_name = "1";
const QString simpleT9glb::key_2_name = "2";
const QString simpleT9glb::key_3_name = "3";
const QString simpleT9glb::key_4_name = "4";
const QString simpleT9glb::key_5_name = "5";
const QString simpleT9glb::key_6_name = "6";
const QString simpleT9glb::key_7_name = "7";
const QString simpleT9glb::key_8_name = "8";
const QString simpleT9glb::key_9_name = "9";
 
const QString simpleT9glb::key_f1_name = "F1";
const QString simpleT9glb::key_f2_name = "F2";
const QString simpleT9glb::key_f3_name = "F3";
const QString simpleT9glb::key_f4_name = "F4";
const QString simpleT9glb::key_f5_name = "F5";
const QString simpleT9glb::key_f6_name = "F6";
const QString simpleT9glb::key_f7_name = "F7";
const QString simpleT9glb::key_f8_name = "F8";
const QString simpleT9glb::key_f9_name = "F9";
const QString simpleT9glb::key_f10_name = "F10";

const QString simpleT9glb::key_up_name = "Up";
const QString simpleT9glb::key_down_name = "Down";
const QString simpleT9glb::key_left_name = "Left";
const QString simpleT9glb::key_right_name = "Right";
const QString simpleT9glb::key_page_up_name = "Page_Up";
const QString simpleT9glb::key_page_down_name = "Page_Down";
const QString simpleT9glb::key_delete_name = "Delete";
const QString simpleT9glb::key_space_name = "Space";
const QString simpleT9glb::key_return_name = "Return";
const QString simpleT9glb::key_backspace_name = "Backspace";
const QString simpleT9glb::key_exit_name = "Exit";
const QString simpleT9glb::key_confirm_name = "Confirm";
const QString simpleT9glb::key_hyphen_name = "Hyphen";
const QString simpleT9glb::key_dot_name = "Dot";

const QString simpleT9glb::key_f1_value = QString::number(Qt::Key_F1, 16);
const QString simpleT9glb::key_f2_value = QString::number(Qt::Key_F2, 16);
const QString simpleT9glb::key_f3_value = QString::number(Qt::Key_F3, 16);
const QString simpleT9glb::key_f4_value = QString::number(Qt::Key_F4, 16);
const QString simpleT9glb::key_f5_value = QString::number(Qt::Key_F5, 16);
const QString simpleT9glb::key_f6_value = QString::number(Qt::Key_F6, 16);
const QString simpleT9glb::key_f7_value = QString::number(Qt::Key_F7, 16);
const QString simpleT9glb::key_f8_value = QString::number(Qt::Key_F8, 16);
const QString simpleT9glb::key_f9_value = QString::number(Qt::Key_F9, 16);
const QString simpleT9glb::key_f10_value = QString::number(Qt::Key_F10, 16);

const QHash<int, QString> simpleT9glb::key_0_value = {
		{ SimpleKeyboard::KR_Chinese, QString::number(Qt::Key_0, 16) },
		{ SimpleKeyboard::KR_English, QString::number(Qt::Key_0, 16) },
		{ SimpleKeyboard::KR_English_Capital, QString::number(Qt::Key_0, 16) },
		{ SimpleKeyboard::KR_Digit, "0" }
	};

const QHash<int, QString> simpleT9glb::key_1_value = {
		{ SimpleKeyboard::KR_Chinese, "'" },
		{ SimpleKeyboard::KR_English, QString::number(Qt::Key_1, 16) },
		{ SimpleKeyboard::KR_English_Capital, QString::number(Qt::Key_1, 16) },
		{ SimpleKeyboard::KR_Digit, "1" }
	};														

const QHash<int, QString> simpleT9glb::key_2_value = {
		{ SimpleKeyboard::KR_Chinese, "abc" },
		{ SimpleKeyboard::KR_English, "abc" },
		{ SimpleKeyboard::KR_English_Capital, "ABC" },
		{ SimpleKeyboard::KR_Digit, "2" }
	};

const QHash<int, QString> simpleT9glb::key_3_value = {
		{ SimpleKeyboard::KR_Chinese, "def" },
		{ SimpleKeyboard::KR_English, "def" },
		{ SimpleKeyboard::KR_English_Capital, "DEF" },
		{ SimpleKeyboard::KR_Digit, "3" }
	};

const QHash<int, QString> simpleT9glb::key_4_value = {
		{ SimpleKeyboard::KR_Chinese, "ghi" },
		{ SimpleKeyboard::KR_English, "ghi" },
		{ SimpleKeyboard::KR_English_Capital, "GHI" },
		{ SimpleKeyboard::KR_Digit, "4" }
	};

const QHash<int, QString> simpleT9glb::key_5_value = {
		{ SimpleKeyboard::KR_Chinese, "jkl" },
		{ SimpleKeyboard::KR_English, "jkl" },
		{ SimpleKeyboard::KR_English_Capital, "JKL" },
		{ SimpleKeyboard::KR_Digit, "5" }
	};

const QHash<int, QString> simpleT9glb::key_6_value = {
		{ SimpleKeyboard::KR_Chinese, "mno" },
		{ SimpleKeyboard::KR_English, "mno" },
		{ SimpleKeyboard::KR_English_Capital, "MNO" },
		{ SimpleKeyboard::KR_Digit, "6" }
	};														

const QHash<int, QString> simpleT9glb::key_7_value = {
		{ SimpleKeyboard::KR_Chinese, "pqrs" },
		{ SimpleKeyboard::KR_English, "pqrs" },
		{ SimpleKeyboard::KR_English_Capital, "PQRS" },
		{ SimpleKeyboard::KR_Digit, "7" }
	};

const QHash<int, QString> simpleT9glb::key_8_value = {
		{ SimpleKeyboard::KR_Chinese, "tuv" },
		{ SimpleKeyboard::KR_English, "tuv" },
		{ SimpleKeyboard::KR_English_Capital, "TUV" },
		{ SimpleKeyboard::KR_Digit, "8" }
	};

const QHash<int, QString> simpleT9glb::key_9_value = {
		{ SimpleKeyboard::KR_Chinese, "wxyz" },
		{ SimpleKeyboard::KR_English, "wxyz" },
		{ SimpleKeyboard::KR_English_Capital, "WXYZ" },
		{ SimpleKeyboard::KR_Digit, "9" }
	};

const QString simpleT9glb::key_up_value = "";
const QString simpleT9glb::key_down_value = "";
const QString simpleT9glb::key_left_value = "";
const QString simpleT9glb::key_right_value = "";
const QString simpleT9glb::key_page_up_value = "";
const QString simpleT9glb::key_page_down_value = "";
const QString simpleT9glb::key_delete_value = "";
const QString simpleT9glb::key_space_value = "";
const QString simpleT9glb::key_return_value = "";
const QString simpleT9glb::key_backspace_value = "";
const QString simpleT9glb::key_exit_value = "";
const QString simpleT9glb::key_confirm_value = "";
const QString simpleT9glb::key_hyphen_value = "";
const QString simpleT9glb::key_dot_value = "";
	
const QString simpleT9glb::key_punctuation_candidate = ",.?;:!/@#$%^&*'()[]-=\\`+-{}|\"<>~";

const int simpleT9glb::multi_purpose_key_start = Qt::Key_2;
const int simpleT9glb::multi_purpose_key_end = Qt::Key_9;

const int simpleT9glb::digit_key_start = Qt::Key_0;
const int simpleT9glb::digit_key_end = Qt::Key_9;

const int simpleT9glb::max_chinese_char_candidate_per_page = 6;
const char *simpleT9glb::ime_title_string = "华创拼音";

const QString simpleT9glb::key_role_type_chinese_text = "[中文]";
const QString simpleT9glb::key_role_type_english_text = "[英文小写]";
const QString simpleT9glb::key_role_type_english_capital_text = "[英文大写]";
const QString simpleT9glb::key_role_type_digit_text = "[数字]";
const QString simpleT9glb::key_role_type_punctuation_text = "[符号]";

const int simpleT9glb::input_method_count = 5;

const QHash<int, QString> simpleT9glb::a_key_code_to_key_name_map = {
		{ Qt::Key_0, 			simpleT9glb::key_0_name },
		{ Qt::Key_1, 			simpleT9glb::key_1_name },
		{ Qt::Key_2, 			simpleT9glb::key_2_name },
		{ Qt::Key_3, 			simpleT9glb::key_3_name },
		{ Qt::Key_4, 			simpleT9glb::key_4_name },
		{ Qt::Key_5, 			simpleT9glb::key_5_name },
		{ Qt::Key_6, 			simpleT9glb::key_6_name },
		{ Qt::Key_7, 			simpleT9glb::key_7_name },
		{ Qt::Key_8, 			simpleT9glb::key_8_name },
		{ Qt::Key_9, 			simpleT9glb::key_9_name },
		{ Qt::Key_Backspace, 	simpleT9glb::key_backspace_name },
		{ Qt::Key_Right, 		simpleT9glb::key_right_name },
		{ Qt::Key_Left, 		simpleT9glb::key_left_name },
		{ Qt::Key_Up, 			simpleT9glb::key_up_name },
		{ Qt::Key_Down, 		simpleT9glb::key_down_name },
		{ Qt::Key_F1, 			simpleT9glb::key_f1_name },
		{ Qt::Key_F2, 			simpleT9glb::key_f2_name },
		{ Qt::Key_F3, 			simpleT9glb::key_f3_name },
		{ Qt::Key_F4, 			simpleT9glb::key_f4_name },
		{ Qt::Key_F5, 			simpleT9glb::key_f5_name },
		{ Qt::Key_F6, 			simpleT9glb::key_f6_name },
		{ Qt::Key_F7, 			simpleT9glb::key_f7_name },
		{ Qt::Key_F8, 			simpleT9glb::key_f8_name },
		{ Qt::Key_F9, 			simpleT9glb::key_f9_name },
		{ Qt::Key_F10, 			simpleT9glb::key_f10_name }
	};

const int simpleT9glb::continuous_key_press_timeout = 1000;

