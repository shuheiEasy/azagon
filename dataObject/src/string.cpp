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

void String::del(int start)
{
    _del(start, 1);
}

void String::del(int start, int length)
{
    _del(start, length);
}

char *String::getChar() const
{
    // 初期化
    int char_size = 0;
    int ptr = 0;
    char *ret;

    // 容量計算
    for (int i = 0; i < _length; i++)
    {
        char_size += _data[i].size;
    }
    char_size++;

    // 容量確保
    ret = (char *)malloc(sizeof(char) * char_size);

    // 初期化
    for (int i = 0; i < char_size; i++)
    {
        ret[i] = '\0';
    }

    // コピー
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

String String::slice(int start, int length) const
{
    // 位置取得
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

    // 不正検知
    if (start_pos > end_pos)
    {
        return String("");
    }

    // データ取得
    String ret = "";
    for (int i = start_pos; i < end_pos; i++)
    {
        // 領域外判定
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

///////////////////////////////////////////////////////////
//
// private
//
///////////////////////////////////////////////////////////

void String::_converter(Moji *&ret, const char *text, int &size)
{
    // 初期化
    int pos = 0;
    size = 0;
    _malloc(ret, strlen(text));

    // 計測
    while (text[pos] != '\0')
    {
        // サイズ計測
        int len = mblen(&text[pos], MB_CUR_MAX);

        // 文字情報取得
        for (int i = 0; i < len; i++)
        {
            ret[size].data[i] = text[pos + i];
        }
        // 　容量
        ret[size].size = len;

        // 後始末
        pos += len;
        size++;
    }
}

int String::_convertNum(int pos) const
{
    if (_data[pos].size > 2)
    {
        if (strcmp(_data[pos].data, "０") == 0)
        {
            return 0;
        }
        else if (strcmp(_data[pos].data, "１") == 0)
        {
            return 1;
        }
        else if (strcmp(_data[pos].data, "２") == 0)
        {
            return 2;
        }
        else if (strcmp(_data[pos].data, "３") == 0)
        {
            return 3;
        }
        else if (strcmp(_data[pos].data, "４") == 0)
        {
            return 4;
        }
        else if (strcmp(_data[pos].data, "５") == 0)
        {
            return 5;
        }
        else if (strcmp(_data[pos].data, "６") == 0)
        {
            return 6;
        }
        else if (strcmp(_data[pos].data, "７") == 0)
        {
            return 7;
        }
        else if (strcmp(_data[pos].data, "８") == 0)
        {
            return 8;
        }
        else if (strcmp(_data[pos].data, "９") == 0)
        {
            return 9;
        }
        else if (strcmp(_data[pos].data, "＋") == 0)
        {
            return 100;
        }
        else if (strcmp(_data[pos].data, "ー") == 0)
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
    // 位置取得
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

    // 不正検知
    if (start_pos > end_pos)
    {
        return -1;
    }

    // データ移動
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

    // 文字数削除
    _length -= end_pos - start_pos;

    return 0;
}

void String::_init()
{
    // 定数
    _MOJI_SIZE = 4;
    _MEMORY_SIZE = 4;

    // 長さ
    _length = 0;

    // 記憶容量
    _memory_unit = 1;

    // 記憶領域確保
    _malloc(_data, _memory_unit * _MEMORY_SIZE);

    // 文字コード設定
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
    // 記憶容量不足時
    if (memory_size >= _memory_unit * _MEMORY_SIZE)
    {
        // 記憶容量拡張
        _memory_unit++;

        // 記憶領域確保
        Moji *tmp = (Moji *)realloc(_data, sizeof(Moji) * _memory_unit * _MEMORY_SIZE);

        if (tmp == NULL)
        {
            printf("メモリーの再確保に失敗しました!(size=%d)\n", memory_size);
            // _free_ptr();
            exit(1);
        }
        else
        {
            // 追加確保分初期化
            for (int i = (_memory_unit - 1) * _MEMORY_SIZE; i < _memory_unit * _MEMORY_SIZE; i++)
            {
                tmp[i].data = (char *)malloc(sizeof(char) * _MOJI_SIZE);
                for (int j = 0; j < _MOJI_SIZE; j++)
                {
                    tmp[i].data[j] = '\0';
                }
                tmp[i].size = 0;
            }

            // 代入
            _data = tmp;

            // もっと足りないこともありそうなので再帰的にする
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
    // 戻り値
    // 文字列が整数の場合　　　：0
    // 文字列が数値の場合　　　：1
    // 文字列が数値型以外の場合：-1
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
    // 変数
    int moji_counter = 0;
    int start_pos;
    Moji *tmp = NULL;

    // 入力情報分析
    _converter(tmp, text, moji_counter);

    // 入力位置分析
    if (start < 0)
    {
        start_pos = _length;
    }
    else
    {
        start_pos = start;
    }

    // 記憶領域確保
    _getMemory(_length + moji_counter);

    // データの移動
    for (int i = _length; i > start_pos; i--)
    {
        int ptr = i + moji_counter - 1;
        _data[ptr].size = _data[i - 1].size;

        for (int j = 0; j < _MOJI_SIZE; j++)
        {
            _data[ptr].data[j] = _data[i - 1].data[j];
        }
    }

    // データのコピー
    for (int i = 0; i < moji_counter; i++)
    {
        _data[i + start_pos].size = tmp[i].size;
        for (int j = 0; j < _MOJI_SIZE; j++)
        {
            _data[i + start_pos].data[j] = tmp[i].data[j];
        }
    }

    // バッファの解放
    if (tmp != NULL)
    {
        free(tmp);
        tmp = NULL;
    }

    // 文字の長さ更新
    _length += moji_counter;
}
