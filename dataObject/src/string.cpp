#include <dataObject/dataObject.hpp>

using namespace dataObject;

String::String()
{
    _init();
    _setData("", -1);
}

String::String(const NoneType &none)
{
    _init();
    _setData("", -1);
}

String::String(const bool &data)
{
    _init();
    if (data)
    {
        _setData("True", -1);
    }
    else
    {
        _setData("False", -1);
    }
}

String::String(const int &data)
{
    _init();
    _fromInt(data, -1);
}

String::String(const float &data)
{
    _init();
    _fromFloat(data, -1);
}

String::String(const double &data)
{
    _init();
    _fromDouble(data, -1);
}

String::String(const char letter)
{
    _init();
    _fromChar(letter, -1);
}

String::String(const char *text)
{
    _init();
    _setData(text, -1);
}

String::String(const String &text)
{
    _init();
    _setData(text.getChar(), -1);
}

String::String(const std::string &text)
{
    _init();
    _setData(text.c_str(), -1);
}

String::~String()
{
    _free_ptr();
}

void String::append(const int &data)
{
    _fromInt(data, -1);
}

void String::append(const float &data)
{
    _fromFloat(data, -1);
}

void String::append(const double &data)
{
    _fromDouble(data, -1);
}

void String::append(const char letter)
{
    _fromChar(letter, -1);
}

void String::append(const char *text)
{
    _setData(text, -1);
}

void String::append(const String text)
{
    _setData(text.getChar(), -1);
}

void String::clear()
{
    _free_ptr();
    _init();
}

int String::count(const char moji)
{
    return findall(moji).getSize();
}

int String::count(const char *text)
{
    return findall(text).getSize();
}

int String::count(const String &text)
{
    return findall(text).getSize();
}

char *String::c_str() const
{
    return this->getChar();
}

void String::del(int start)
{
    _del(start, 1);
}

void String::del(int start, int length)
{
    _del(start, length);
}

bool String::exist(const char moji)
{
    return this->exist(String(moji));
}

bool String::exist(const char *text)
{
    return this->exist(String(text));
}

bool String::exist(const String &text)
{
    if (this->find(text) >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int String::find(const char moji, bool reverse_flag)
{
    return this->find(String(moji), reverse_flag);
}

int String::find(const char *text, bool reverse_flag)
{
    return this->find(String(text), reverse_flag);
}

int String::find(const String &text, bool reverse_flag)
{
    int search_id;
    int ret = -1;

    if (reverse_flag)
    {
        search_id = text.getSize() - 1;
    }
    else
    {
        search_id = 0;
    }

    for (int i = 0; i < this->getSize(); i++)
    {
        // ??????????????????????????????
        int text_pos;

        if (reverse_flag)
        {
            text_pos = this->getSize() - i - 1;
        }
        else
        {
            text_pos = i;
        }

        // ????????????
        String moji = slice(text_pos, 1);

        // ????????????
        if (moji == text[search_id])
        {
            if (reverse_flag)
            {
                if (search_id == text.getSize() - 1)
                {
                    ret = text_pos;
                }
            }
            else
            {
                if (search_id == 0)
                {
                    ret = text_pos;
                }
            }

            if (reverse_flag)
            {
                search_id--;
            }
            else
            {
                search_id++;
            }
        }
        else
        {
            if (reverse_flag)
            {
                search_id = text.getSize() - 1;
            }
            else
            {
                search_id = 0;
            }
            ret = -1;
        }

        // ???????????????????????????????????????
        if (reverse_flag)
        {
            if (search_id < 0)
            {
                break;
            }
        }
        else
        {
            if (search_id >= text.getSize())
            {
                break;
            }
        }
    }

    // ??????????????????
    if (reverse_flag)
    {
        ret -= text.getSize() - 1;
    }

    return ret;
}

List<int> String::findall(const char moji)
{
    return findall(String(moji));
}

List<int> String::findall(const char *text)
{
    return findall(String(text));
}

List<int> String::findall(const String &text)
{
    // return
    List<int> ret;

    // ??????
    int start = 0;
    int length = this->getSize();
    while (true)
    {
        // ????????????????????????
        String buffer = this->slice(start, length);

        // ??????
        int search_pos = buffer.find(text);

        // ????????????????????????????????????
        if (search_pos < 0)
        {
            break;
        }

        // ??????????????????
        ret.append(start + search_pos);

        // ??????????????????????????????
        start += search_pos + text.getSize();
    }

    return ret;
}

char *String::getChar() const
{
    // ?????????
    int char_size = 0;
    int ptr = 0;
    char *ret;

    // ????????????
    for (int i = 0; i < _length; i++)
    {
        char_size += _data[i].size;
    }
    char_size++;

    // ????????????
    ret = (char *)malloc(sizeof(char) * char_size);

    // ?????????
    for (int i = 0; i < char_size; i++)
    {
        ret[i] = '\0';
    }

    // ?????????
    for (int i = 0; i < _length; i++)
    {
        for (int j = 0; j < _data[i].size; j++)
        {
            ret[ptr + j] = _data[i].data[j];
        }
        ptr += _data[i].size;
    }

    return ret;
}

const char *String::getType() const
{
    return "String";
}

const char *String::getLog() const
{
    return getChar();
}

int String::getSize() const
{
    return _length;
}

void String::insert(const char *text, int start)
{
    int start_pos = _getPos(start);

    _setData(text, start_pos);
}

void String::insert(const String text, int start)
{
    int start_pos = _getPos(start);

    _setData(text.getChar(), start_pos);
}

bool String::isdigit() const
{
    if (this->_judgeNum() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool String::isnumeric() const
{
    if (this->_judgeNum() >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

String String::lower()
{
    String ret;
    for (int pos = 0; pos < _length; pos++)
    {
        if (_data[pos].size == 1)
        {
            if ('A' <= _data[pos].data[0] && _data[pos].data[0] <= 'Z')
            {
                ret += String(char(_data[pos].data[0] + 32));
            }
            else
            {
                ret += String(_data[pos].data);
            }
        }
        else
        {
            ret += String(_data[pos].data);
        }
    }

    return ret;
}

bool String::operator==(const int &data) const
{
    String tmp(data);
    if (tmp == *this)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool String::operator==(const float &data) const
{
    String tmp(data);
    if (tmp == *this)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool String::operator==(const double &data) const
{
    String tmp(data);
    if (tmp == *this)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool String::operator==(const char letter) const
{
    String tmp(letter);
    if (tmp == *this)
    {
        return true;
    }
    return false;
}

bool String::operator==(const char *text) const
{
    if (strcmp(getChar(), text) == 0)
    {
        return true;
    }
    return false;
}

bool String::operator==(const String &text) const
{
    if (text.getSize() == _length)
    {
        if (strcmp(this->getChar(), text.getChar()) == 0)
        {
            return true;
        }
    }
    return false;
}

bool String::operator!=(const int &data) const
{
    return !operator==(data);
}

bool String::operator!=(const float &data) const
{
    return !operator==(data);
}

bool String::operator!=(const double &data) const
{
    return !operator==(data);
}

bool String::operator!=(const char letter) const
{
    return !operator==(letter);
}

bool String::operator!=(const char *text) const
{
    return !operator==(text);
}

bool String::operator!=(const String &text) const
{
    return !operator==(text);
}

String String::operator[](const int id) const
{
    return slice(id, 1);
}

String String::operator=(const int &data)
{
    clear();
    _fromInt(data, -1);
    return *this;
}

String String::operator=(const float &data)
{
    clear();
    _fromFloat(data, -1);
    return *this;
}

String String::operator=(const double &data)
{
    clear();
    _fromDouble(data, -1);
    return *this;
}

String String::operator=(const char letter)
{
    clear();
    _fromChar(letter, -1);

    return *this;
}

String String::operator=(const char *str)
{
    clear();
    _setData(str, -1);

    return *this;
}

String String::operator=(const String &str)
{
    clear();
    _setData(str.getChar(), -1);

    return *this;
}

String String::operator+(const int &data) const
{
    String ret = *this;
    ret.append(data);
    return ret;
}

String String::operator+(const float &data) const
{
    String ret = *this;
    ret.append(data);
    return ret;
}

String String::operator+(const double &data) const
{
    String ret = *this;
    ret.append(data);
    return ret;
}

String String::operator+(const char letter) const
{
    String ret = *this;
    ret.append(letter);
    return ret;
}

String String::operator+(const char *str) const
{
    String ret = *this;
    ret.append(str);
    return ret;
}

String String::operator+(const String &str) const
{
    String ret = *this;
    ret.append(str);
    return ret;
}

String &String::operator+=(const int &data)
{
    _fromInt(data, -1);
    return *this;
}

String &String::operator+=(const float &data)
{
    _fromFloat(data, -1);
    return *this;
}

String &String::operator+=(const double &data)
{
    _fromDouble(data, -1);
    return *this;
}

String &String::operator+=(const char letter)
{
    _fromChar(letter, -1);
    return *this;
}

String &String::operator+=(const char *str)
{
    _setData(str, -1);
    return *this;
}

String &String::operator+=(const String &str)
{
    _setData(str.getChar(), -1);
    return *this;
}

String String::pop(int start, int length)
{
    String ret = slice(start, length);
    _del(start, length);
    return ret;
}

String String::replace(const char *before, const char *after)
{
    String before_tmp = before;
    String after_tmp = after;

    return this->replace(before_tmp, after_tmp);
}
String String::replace(const char *before, const String after)
{
    String before_tmp = before;

    return this->replace(before_tmp, after);
}
String String::replace(const String before, const char *after)
{
    String after_tmp = after;

    return this->replace(before, after_tmp);
}
String String::replace(const String before, const String after)
{
    List<String> buffer = this->split(before);
    String ret = "";

    for (int i = 0; i < buffer.getSize() - 1; i++)
    {
        ret += buffer[i];
        ret += after;
    }

    ret += buffer[buffer.getSize() - 1];

    return ret;
}

String String::slice(int start, int length) const
{
    // ????????????
    int start_pos;
    int end_pos;

    if (length < 0)
    {
        end_pos = _getPos(start);
        start_pos = _getPos(end_pos + length);
    }
    else
    {
        start_pos = _getPos(start);
        end_pos = _getPos(start_pos + length);
    }

    // ????????????
    if (start_pos > end_pos)
    {
        return String("");
    }

    // ???????????????
    String ret = "";
    for (int i = start_pos; i < end_pos; i++)
    {
        // ???????????????
        if (i >= _memory_unit * _MEMORY_SIZE)
        {
            break;
        }
        ret += _data[i].data;
    }

    return ret;
}

List<String> String::split(const char sep)
{
    return split(String(sep));
}

List<String> String::split(const char *sep)
{
    return split(String(sep));
}

List<String> String::split(const String sep)
{
    List<String> ret;
    int sep_length = sep.getSize();

    String buffer = "";
    String check_text = "";
    for (int i = 0; i < _length; i++)
    {
        check_text += _data[i].data;
        if (check_text.getSize() == sep_length)
        {
            if (check_text == sep)
            {
                check_text = "";
                ret.append(buffer);
                buffer = "";
            }
            else
            {
                buffer += check_text.pop(0, 1);
            }
        }
    }
    if (check_text.getSize() > 0)
    {
        buffer.append(check_text);
    }

    ret.append(buffer);

    return ret;
}

int String::toInt()
{
    int ret = 0;
    int digit_counter = 0;
    for (int i = _length - 1; i >= 0; i--)
    {
        auto num = _convertNum(i);
        if (num < 0)
        {
            return 0;
        }
        if (num > 10)
        {
            switch (num)
            {
            case 100:
                return ret;
                break;
            case 101:
                return -ret;
                break;
            case 102:
                ret = 0;
                digit_counter = -1;
                break;
            default:
                return 0;
                break;
            }
        }
        else
        {
            int digit = 1;
            for (int j = 0; j < digit_counter; j++)
            {
                digit *= 10;
            }
            ret += num * digit;
        }
        digit_counter++;
    }

    return ret;
}

float String::toFloat()
{
    float ret = 0;
    bool integer_flag = true;
    int point_counter = 0;
    bool minus_flag = false;
    for (int i = 0; i < _length; i++)
    {
        auto num = _convertNum(i);
        if (num < 0)
        {
            return 0;
        }
        if (num > 10)
        {
            if (i == 0)
            {
                switch (num)
                {
                case 101:
                    minus_flag = true;
                    break;
                case 102:
                    if (!integer_flag)
                    {
                        return ret;
                    }
                    integer_flag = false;
                    break;
                default:
                    return 0;
                    break;
                }
            }
            else
            {
                switch (num)
                {
                case 100:
                case 101:
                    return ret;
                    break;
                case 102:
                    if (!integer_flag)
                    {
                        return ret;
                    }
                    integer_flag = false;
                    break;
                default:
                    return 0;
                    break;
                }
            }
        }
        else
        {
            if (integer_flag)
            {
                ret = ret * 10 + num;
            }
            else
            {
                float decimal = 1;
                for (int j = 0; j < point_counter; j++)
                {
                    decimal *= 0.1;
                }
                ret += num * decimal;
            }
        }

        if (!integer_flag)
        {
            point_counter++;
        }
    }

    if (minus_flag)
    {
        return -ret;
    }
    else
    {
        return ret;
    }
}

double String::toDouble()
{
    double ret = 0;
    bool integer_flag = true;
    int point_counter = 0;
    bool minus_flag = false;
    for (int i = 0; i < _length; i++)
    {
        auto num = _convertNum(i);
        if (num < 0)
        {
            return 0;
        }
        if (num > 10)
        {
            if (i == 0)
            {
                switch (num)
                {
                case 101:
                    minus_flag = true;
                    break;
                case 102:
                    if (!integer_flag)
                    {
                        return ret;
                    }
                    integer_flag = false;
                    break;
                default:
                    return 0;
                    break;
                }
            }
            else
            {
                switch (num)
                {
                case 100:
                case 101:
                    return ret;
                    break;
                case 102:
                    if (!integer_flag)
                    {
                        return ret;
                    }
                    integer_flag = false;
                    break;
                default:
                    return 0;
                    break;
                }
            }
        }
        else
        {
            if (integer_flag)
            {
                ret = ret * 10 + num;
            }
            else
            {
                double decimal = 1;
                for (int j = 0; j < point_counter; j++)
                {
                    decimal *= 0.1;
                }
                ret += num * decimal;
            }
        }

        if (!integer_flag)
        {
            point_counter++;
        }
    }

    if (minus_flag)
    {
        return -ret;
    }
    else
    {
        return ret;
    }
}

String String::upper()
{
    String ret;
    for (int pos = 0; pos < _length; pos++)
    {
        if (_data[pos].size == 1)
        {
            if ('a' <= _data[pos].data[0] && _data[pos].data[0] <= 'z')
            {
                ret += String(char(_data[pos].data[0] - 32));
            }
            else
            {
                ret += String(_data[pos].data);
            }
        }
        else
        {
            ret += String(_data[pos].data);
        }
    }

    return ret;
}

///////////////////////////////////////////////////////////
//
// private
//
///////////////////////////////////////////////////////////

void String::_converter(Moji *&ret, const char *text, int &size)
{
    // ?????????
    int pos = 0;
    size = 0;
    _malloc(ret, strlen(text));

    // ??????
    while (text[pos] != '\0')
    {
        // ???????????????
        int len = mblen(&text[pos], MB_CUR_MAX);

        // ??????????????????
        for (int i = 0; i < len; i++)
        {
            ret[size].data[i] = text[pos + i];
        }
        // ?????????
        ret[size].size = len;

        // ?????????
        pos += len;
        size++;
    }
}

int String::_convertNum(int pos) const
{
    if (_data[pos].size > 2)
    {
        if (strcmp(_data[pos].data, "???") == 0)
        {
            return 0;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 1;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 2;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 3;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 4;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 5;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 6;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 7;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 8;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 9;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 100;
        }
        else if (strcmp(_data[pos].data, "???") == 0)
        {
            return 101;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (strcmp(_data[pos].data, "0") == 0)
        {
            return 0;
        }
        else if (strcmp(_data[pos].data, "1") == 0)
        {
            return 1;
        }
        else if (strcmp(_data[pos].data, "2") == 0)
        {
            return 2;
        }
        else if (strcmp(_data[pos].data, "3") == 0)
        {
            return 3;
        }
        else if (strcmp(_data[pos].data, "4") == 0)
        {
            return 4;
        }
        else if (strcmp(_data[pos].data, "5") == 0)
        {
            return 5;
        }
        else if (strcmp(_data[pos].data, "6") == 0)
        {
            return 6;
        }
        else if (strcmp(_data[pos].data, "7") == 0)
        {
            return 7;
        }
        else if (strcmp(_data[pos].data, "8") == 0)
        {
            return 8;
        }
        else if (strcmp(_data[pos].data, "9") == 0)
        {
            return 9;
        }
        else if (strcmp(_data[pos].data, "+") == 0)
        {
            return 100;
        }
        else if (strcmp(_data[pos].data, "-") == 0)
        {
            return 101;
        }
        else if (strcmp(_data[pos].data, ".") == 0)
        {
            return 102;
        }
        else
        {
            return -1;
        }
    }
}
int String::_del(int start, int length)
{
    // ????????????
    int start_pos;
    int end_pos;

    if (length < 0)
    {
        end_pos = _getPos(start);
        start_pos = _getPos(end_pos + length);
    }
    else
    {
        start_pos = _getPos(start);
        end_pos = _getPos(start_pos + length);
    }

    // ????????????
    if (start_pos > end_pos)
    {
        return -1;
    }

    // ???????????????
    int pos = 0;
    for (int i = end_pos; i < _memory_unit * _MEMORY_SIZE; i++)
    {
        _data[start_pos + pos].size = _data[i].size;
        _data[i].size = 0;
        for (int j = 0; j < _MOJI_SIZE; j++)
        {
            _data[start_pos + pos].data[j] = _data[i].data[j];
            _data[i].data[j] = '\0';
        }
        pos++;
    }

    // ???????????????
    _length -= end_pos - start_pos;

    return 0;
}

void String::_init()
{
    // ??????
    _MOJI_SIZE = 4;
    _MEMORY_SIZE = 4;

    // ??????
    _length = 0;

    // ????????????
    _memory_unit = 1;

    // ??????????????????
    _malloc(_data, _memory_unit * _MEMORY_SIZE);

    // ?????????????????????
    setlocale(LC_CTYPE, LANGUAGECODE);
}

void String::_free_ptr()
{
    if (_memory_unit > 0)
    {
        for (int i = 0; i < _memory_unit * _MEMORY_SIZE; i++)
        {
            if (_data[i].data != NULL)
            {
                free(_data[i].data);
                _data[i].data = NULL;
            }
        }

        if (_data != NULL)
        {
            free(_data);
            _data = NULL;
        }
        _memory_unit = 0;
    }
}

void String::_fromChar(const char letter, const int start)
{
    char text[] = {letter, '\0'};
    _setData(text, start);
}

void String::_fromInt(const int data, const int start)
{
    const int TMP_SIZE = 12;
    char tmp[TMP_SIZE];
    for (int i = 0; i < TMP_SIZE; i++)
    {
        tmp[i] = '\0';
    }
    snprintf(tmp, TMP_SIZE, "%d", data);
    _setData(tmp, start);
}

void String::_fromFloat(const float data, const int start)
{
    const int TMP_SIZE = 10;
    char tmp[TMP_SIZE];
    for (int i = 0; i < TMP_SIZE; i++)
    {
        tmp[i] = '\0';
    }
    snprintf(tmp, TMP_SIZE, "%f", data);
    int non_zero_digit = TMP_SIZE - 1;
    for (int i = TMP_SIZE - 1; i >= 0; i--)
    {
        if (non_zero_digit == i)
        {
            if ((tmp[i] == '0') || (tmp[i] == '\0'))
            {
                non_zero_digit--;
            }
        }
    }

    for (int i = non_zero_digit + 1; i < TMP_SIZE; i++)
    {
        tmp[i] = '\0';
    }

    _setData(tmp, start);
}

void String::_fromDouble(const double data, const int start)
{
    const int TMP_SIZE = 16;
    char tmp[TMP_SIZE];
    for (int i = 0; i < TMP_SIZE; i++)
    {
        tmp[i] = '\0';
    }
    snprintf(tmp, TMP_SIZE, "%lf", data);
    int non_zero_digit = TMP_SIZE - 1;
    for (int i = TMP_SIZE - 1; i >= 0; i--)
    {
        if (non_zero_digit == i)
        {
            if ((tmp[i] == '0') || (tmp[i] == '\0'))
            {
                non_zero_digit--;
            }
        }
    }

    for (int i = non_zero_digit + 1; i < TMP_SIZE; i++)
    {
        tmp[i] = '\0';
    }

    _setData(tmp, start);
}

void String::_getMemory(const int memory_size)
{
    // ?????????????????????
    if (memory_size >= _memory_unit * _MEMORY_SIZE)
    {
        // ??????????????????
        _memory_unit++;

        // ??????????????????
        Moji *tmp = (Moji *)realloc(_data, sizeof(Moji) * _memory_unit * _MEMORY_SIZE);

        if (tmp == NULL)
        {
            printf("?????????????????????????????????????????????!(size=%d)\n", memory_size);
            // _free_ptr();
            exit(1);
        }
        else
        {
            // ????????????????????????
            for (int i = (_memory_unit - 1) * _MEMORY_SIZE; i < _memory_unit * _MEMORY_SIZE; i++)
            {
                tmp[i].data = (char *)malloc(sizeof(char) * _MOJI_SIZE);
                for (int j = 0; j < _MOJI_SIZE; j++)
                {
                    tmp[i].data[j] = '\0';
                }
                tmp[i].size = 0;
            }

            // ??????
            _data = tmp;

            // ?????????????????????????????????????????????????????????????????????
            _getMemory(memory_size);
        }
    }
}

int String::_getPos(int pos) const
{
    int ret;

    if (pos < 0)
    {
        ret = _length + pos;
        if (ret < 0)
        {
            ret = 0;
        }
    }
    else
    {
        ret = pos;
        if (ret > _length)
        {
            ret = _length;
        }
    }

    return ret;
}

int String::_judgeNum() const
{
    // ?????????
    // ???????????????????????????????????????0
    // ???????????????????????????????????????1
    // ???????????????????????????????????????-1
    int ret = 0;
    for (int i = 0; i < _length; i++)
    {
        auto num = _convertNum(i);
        if (num < 0)
        {
            return -1;
        }
        if (num > 10)
        {
            ret = 1;
        }
    }
    return ret;
}
void String::_malloc(Moji *&ret, int size)
{
    ret = (Moji *)malloc(sizeof(Moji) * size);
    for (int i = 0; i < size; i++)
    {
        ret[i].size = 0;
        ret[i].data = (char *)malloc(sizeof(char) * _MOJI_SIZE);
        for (int j = 0; j < _MOJI_SIZE; j++)
        {
            ret[i].data[j] = '\0';
        }
    }
}

void String::_setData(const char *text, int start)
{
    // ??????
    int moji_counter = 0;
    int start_pos;
    Moji *tmp = NULL;

    // ??????????????????
    _converter(tmp, text, moji_counter);

    // ??????????????????
    if (start < 0)
    {
        start_pos = _length;
    }
    else
    {
        start_pos = start;
    }

    // ??????????????????
    _getMemory(_length + moji_counter);

    // ??????????????????
    for (int i = _length; i > start_pos; i--)
    {
        int ptr = i + moji_counter - 1;
        _data[ptr].size = _data[i - 1].size;

        for (int j = 0; j < _MOJI_SIZE; j++)
        {
            _data[ptr].data[j] = _data[i - 1].data[j];
        }
    }

    // ?????????????????????
    for (int i = 0; i < moji_counter; i++)
    {
        _data[i + start_pos].size = tmp[i].size;
        for (int j = 0; j < _MOJI_SIZE; j++)
        {
            _data[i + start_pos].data[j] = tmp[i].data[j];
        }
    }

    // ?????????????????????
    if (tmp != NULL)
    {
        free(tmp);
        tmp = NULL;
    }

    // ?????????????????????
    _length += moji_counter;
}
