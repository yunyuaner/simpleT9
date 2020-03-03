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

#include "keyboard.h"
#include "globals.h"

#define insert_multi_purpose_key(_key, _val, _keyRole) ({ a_key = new MultiPurposeKey(_key, _val, this);	\
	keys[_keyRole].insert(a_key->getKeyName(), a_key);	})

#define insert_function_key(_key, _val, _keyRole) ({ a_key = new FunctionKey(_key, _val, this);		\
	keys[_keyRole].insert(a_key->getKeyName(), a_key); })

#define insert_digit_key(_key, _val, _keyRole) ({ a_key = new DigitKey(_key, _val, this);		\
	keys[_keyRole].insert(a_key->getKeyName(), a_key); })

#define multi_purpose_kv(_x) simpleT9glb::key_##_x##_value[a_key_role]
#define multi_purpose_kn(_x) simpleT9glb::key_##_x##_name
#define function_kv(_x) simpleT9glb::key_##_x##_value
#define function_kv_ex(_x) simpleT9glb::key_##_x##_value[a_key_role]
#define function_kn(_x) simpleT9glb::key_##_x##_name
#define digit_kv_ex(_x) simpleT9glb::key_##_x##_value[a_key_role]
#define digit_kn(_x) simpleT9glb::key_##_x##_name

NonStandardKeyboard::NonStandardKeyboard() : 
	keys(new QHash<QString, SimpleKey *>[simpleT9glb::input_method_count]),
	capsLockPressed(false),
	keyRole(NonStandardKeyboard::KR_Chinese)
{

}

NonStandardKeyboard::~NonStandardKeyboard()
{
	for (int i = 0; i < simpleT9glb::input_method_count; i++) {
		QHash<QString, SimpleKey *> &_keys = keys[i];

		for (auto iter = _keys.begin(); iter != _keys.end(); iter++) {
			SimpleKey *_sk = *iter;	/* Shouldn't use iter->sencond, QHash iteration is different from STL */
			if (_sk != nullptr) {
				delete _sk;
			}
		}
    }

	delete [] keys;
}

QString NonStandardKeyboard::makePinyinDisplayContent()
{
    QStack<QString> _p;
    /* We should pop then push to reverse the order, which keep 
     * the original data, so make a stack copy here */ 
    QStack<QString> _b(this->getDisplayBufferStack());

    while (!_b.isEmpty()) {
        _p.push(_b.pop());
    }
  
    displayBuffer.clear();

    while (!_p.isEmpty()) {
        displayBuffer.append(_p.pop());
    }

    std::cout << "pinyinDisplayContent - " << displayBuffer.toStdString() << std::endl;

    return displayBuffer;
}

QString NonStandardKeyboard::getDisplayBuffer()
{
    return this->makePinyinDisplayContent();
}

QString NonStandardKeyboard::handleKeyPress(int keyCode)
{
	QHash<QString, SimpleKey *> _keys = this->keys[keyRole];    
    bool keyCodeNotSupported = false;
	QString keyName;
	SimpleKey *_k = nullptr;

    std::cout << "handleKeyPress, keyCode - " << QString::number(keyCode, 16).toStdString() << std::endl;

    /* First check if the pressed key is valid under current input method */
	if (simpleT9glb::a_key_code_to_key_name_map.find(keyCode) != simpleT9glb::a_key_code_to_key_name_map.end()) {
		keyName = simpleT9glb::a_key_code_to_key_name_map[keyCode];
        if (_keys.find(keyName) != _keys.end()) {
            _k = _keys[keyName];
        } else {
            std::cout << "key - " << QString::number(keyCode, 16).toStdString() << " not supported" << std::endl;
            keyCodeNotSupported = true;
        }
	} else {
		std::cout << "key - " << QString::number(keyCode, 16).toStdString() << " not supported" << std::endl;
		keyCodeNotSupported = true;
	}	

	/* Remove the dirty one later!! */
	if (keyCode == Qt::Key_F10) {
        
        /* Input Method Switch Order:
         *      (1) Chinese -> English
         *      (2) English -> English_Capital
         *      (3) English_Capital -> Digit
         *      (4) Digit -> Punctuation
         *      (5) Punctuation -> Chinese
         *
         * We only clear the display buffer stack when input mode is 
         * from "Chinese -> English", "Punctuation -> Chinese" */
        if (keyRole == NonStandardKeyboard::KR_Chinese || keyRole == NonStandardKeyboard::KR_Punctuation) {           
		    this->displayBufferStackClear();
        }
	}

    if (!keyCodeNotSupported) {
        _k->press();
    }
    
    return this->getDisplayBuffer();
}

void NonStandardKeyboard::initializeF1ToF10Keys(int keyRole)
{
	SimpleKey *a_key;

	QString a_kn_array[] = {
							function_kn(f1),
							function_kn(f2),
							function_kn(f3),
							function_kn(f4),
							function_kn(f5),
							function_kn(f6),
							function_kn(f7),
							function_kn(f8),
							function_kn(f8),
							function_kn(f10),
						};

	QString a_kv_array[] = {
							function_kv(f1),
							function_kv(f2),
							function_kv(f3),
							function_kv(f4),
							function_kv(f5),
							function_kv(f6),
							function_kv(f7),
							function_kv(f8),
							function_kv(f9),
							function_kv(f10)
						};

	for (unsigned int i = 0; i < sizeof(a_kn_array)/sizeof(a_kn_array[0]); i++) {
		insert_function_key(a_kn_array[i], a_kv_array[i], keyRole);
	}
}

void NonStandardKeyboard::initializeChineseKeys()
{
	SimpleKey *a_key;
	int a_key_role = SimpleKeyboard::KR_Chinese;
	
	QString a_multi_purpose_kv_array[] = {
			multi_purpose_kv(2),
			multi_purpose_kv(3),
			multi_purpose_kv(4),
			multi_purpose_kv(5),
			multi_purpose_kv(6),
			multi_purpose_kv(7),
			multi_purpose_kv(8),
			multi_purpose_kv(9)
		};

	QString a_multi_purpose_kn_array[] = {
			multi_purpose_kn(2),
			multi_purpose_kn(3),
			multi_purpose_kn(4),
			multi_purpose_kn(5),
			multi_purpose_kn(6),
			multi_purpose_kn(7),
			multi_purpose_kn(8),
			multi_purpose_kn(9)		
		};

	
	QString a_function_kv_array[] = {
			function_kv_ex(0),
			function_kv_ex(1),
			function_kv(backspace),
			function_kv(right),
			function_kv(left),
			function_kv(up),
			function_kv(down)	
		};

	QString a_function_kn_array[] = {
			function_kn(0),
			function_kn(1),
			function_kn(backspace),
			function_kn(right),
			function_kn(left),
			function_kn(up),
			function_kn(down)			
		};

	/* Multi-Purpose Keys */
	for (unsigned int i = 0; i < sizeof(a_multi_purpose_kv_array)/sizeof(a_multi_purpose_kv_array[0]); i++) {
		insert_multi_purpose_key(a_multi_purpose_kn_array[i], a_multi_purpose_kv_array[i], a_key_role);
	}

	/* Functional Keys */
	for (unsigned int i = 0; i < sizeof(a_function_kv_array)/sizeof(a_function_kv_array[0]); i++) {
		insert_function_key(a_function_kn_array[i], a_function_kv_array[i], a_key_role);
	}

	initializeF1ToF10Keys(a_key_role);
}

void NonStandardKeyboard::initializeEnglishKey_(int a_key_role)
{
	SimpleKey *a_key;

	QString a_multi_purpose_kv_array[] = {
			multi_purpose_kv(2),
			multi_purpose_kv(3),
			multi_purpose_kv(4),
			multi_purpose_kv(5),
			multi_purpose_kv(6),
			multi_purpose_kv(7),
			multi_purpose_kv(8),
			multi_purpose_kv(9)
		};

	QString a_multi_purpose_kn_array[] = {
			multi_purpose_kn(2),
			multi_purpose_kn(3),
			multi_purpose_kn(4),
			multi_purpose_kn(5),
			multi_purpose_kn(6),
			multi_purpose_kn(7),
			multi_purpose_kn(8),
			multi_purpose_kn(9)		
		};
	
	/* Multi-Purpose Keys */
	for (unsigned int i = 0; i < sizeof(a_multi_purpose_kv_array)/sizeof(a_multi_purpose_kv_array[0]); i++) {
		insert_multi_purpose_key(a_multi_purpose_kn_array[i], a_multi_purpose_kv_array[i], a_key_role);
	}

    insert_function_key(function_kn(backspace), function_kv(backspace), a_key_role);
    
	initializeF1ToF10Keys(a_key_role);
}

void NonStandardKeyboard::initializeEnglishKeys()
{
	this->initializeEnglishKey_(SimpleKeyboard::KR_English);
}

void NonStandardKeyboard::initializeEnglishCapitalKeys()
{
	this->initializeEnglishKey_(SimpleKeyboard::KR_English_Capital);
}

void NonStandardKeyboard::initializeDigitKeys()
{
	SimpleKey *a_key;
	int a_key_role = SimpleKeyboard::KR_Digit;

	QString a_multi_purpose_kv_array[] = {
			digit_kv_ex(0),
			digit_kv_ex(1),
			digit_kv_ex(2),
			digit_kv_ex(3),
			digit_kv_ex(4),
			digit_kv_ex(5),
			digit_kv_ex(6),
			digit_kv_ex(7),
			digit_kv_ex(8),
			digit_kv_ex(9)
		};

	QString a_multi_purpose_kn_array[] = {
			digit_kn(0),
			digit_kn(1),
			digit_kn(2),
			digit_kn(3),
			digit_kn(4),
			digit_kn(5),
			digit_kn(6),
			digit_kn(7),
			digit_kn(8),
			digit_kn(9)		
		};

	for (unsigned int i = 0; i < sizeof(a_multi_purpose_kv_array)/sizeof(a_multi_purpose_kv_array[0]); i++) {
		insert_digit_key(a_multi_purpose_kn_array[i], a_multi_purpose_kv_array[i], a_key_role);
	}

    insert_function_key(function_kn(backspace), function_kv(backspace), a_key_role);
    
	initializeF1ToF10Keys(a_key_role);
}

void NonStandardKeyboard::initializePunctuationKeys() 
{
    SimpleKey *a_key;
	int a_key_role = SimpleKeyboard::KR_Punctuation;
    
    QString a_function_kv_array[] = {
			function_kv(backspace),
			function_kv(right),
			function_kv(left),
			function_kv(up),
			function_kv(down),
			function_kv(space)
		};

	QString a_function_kn_array[] = {
			function_kn(backspace),
			function_kn(right),
			function_kn(left),
			function_kn(up),
			function_kn(down),
			function_kn(space)
		};

    /* Functional Keys */
	for (unsigned int i = 0; i < sizeof(a_function_kv_array)/sizeof(a_function_kv_array[0]); i++) {
		insert_function_key(a_function_kn_array[i], a_function_kv_array[i], a_key_role);
	}

	initializeF1ToF10Keys(a_key_role);
}

void NonStandardKeyboard::initializeKeys()
{
    initializeChineseKeys();
	initializeEnglishKeys();
	initializeEnglishCapitalKeys();
	initializeDigitKeys();
    initializePunctuationKeys();
}
