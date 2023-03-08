#include <fileSystem/fileSystem.hpp>

using namespace dataObject;
using namespace fileSystem;

JsonFile::JsonFile()
{
    textFile = nullptr;
}

JsonFile::JsonFile(const char *file_path)
{
    textFile = nullptr;
    setPath(file_path);
}

JsonFile::JsonFile(const String &file_path)
{
    textFile = nullptr;
    setPath(file_path);
}

JsonFile::~JsonFile()
{
    delete textFile;
}

const char *JsonFile::getType() const { return "JsonFile"; }
int JsonFile::getSize() const { return json_dict_data.getSize(); }
const char *JsonFile::getLog() const { return json_dict_data.getLog(); }

dataObject::Dict<dataObject::String, dataObject::Any> &JsonFile::getDict()
{
    return this->json_dict_data;
}

int JsonFile::read()
{
    if (textFile == nullptr)
    {
        return -2;
    }

    // Read the json file
    String textData = textFile->read();

    // Analyze the data
    auto ret = _getObject(textData, json_dict_data);
    if (ret < 0)
    {
        json_dict_data.clear();
    }

    return ret;
}

void JsonFile::setPath(const String &file_path)
{
    if (textFile != nullptr)
    {
        delete textFile;
    }
    textFile = new TextFile(file_path);
    if (textFile->isfile())
    {
        read();
    }
}

void JsonFile::setPath(const char *file_path)
{
    if (textFile != nullptr)
    {
        delete textFile;
    }

    textFile = new TextFile(file_path);
    if (textFile->isfile())
    {
        read();
    }
}

void JsonFile::write()
{
    String textData = _writeObject(json_dict_data, 0);

    if (!textFile->isfile())
    {
        textFile->touch();
    }

    textFile->write(textData, WRITEMODE);
}

Any JsonFile::_converter(String text)
{
    Any ret = None;

    if (text != "")
    {
        if (text.isdigit())
        {
            ret = text.toInt();
        }
        else if (text.isnumeric())
        {
            ret = text.toDouble();
        }
        else if (text == "null")
        {
            ret = None;
        }
        else
        {
            Bool tmp_flag(text);
            ret = tmp_flag;
        }
    }

    return ret;
}

int JsonFile::_getList(String text, List<Any> &data)
{
    // データ位置
    int pos = 1;

    // データバッファ
    String buffer;
    bool append_flag = true;

    // 確認用
    bool end_flag = false;

    // データ解析
    while (pos < len(text))
    {
        if (text[pos] == "]")
        {
            if (append_flag && buffer != "")
            {
                data.append(this->_converter(buffer));
            }
            append_flag = true;
            end_flag = true;
            buffer.clear();
            break;
        }
        else if (text[pos] == "{")
        {
            buffer.clear();
            Dict<String, Any> tmp;
            auto ret = _getObject(text.slice(pos, len(text)), tmp);
            // エラー処理の後始末
            if (ret < 0)
            {
                return -1;
            }
            pos += ret;

            if (append_flag)
            {
                data.append(tmp);
            }
            append_flag = false;
        }
        else if (text[pos] == "[")
        {
            buffer.clear();
            List<Any> tmp;
            auto ret = _getList(text.slice(pos, len(text)), tmp);
            // エラー処理の後始末
            if (ret < 0)
            {
                return -1;
            }
            pos += ret;

            if (append_flag)
            {
                data.append(tmp);
            }
            append_flag = false;
        }
        else if (text[pos] == "\"")
        {
            buffer.clear();
            auto ret = _getString(text.slice(pos, len(text)), buffer);
            // エラー処理の後始末
            if (ret < 0)
            {
                return -1;
            }
            pos += ret;

            if (append_flag)
            {
                data.append(buffer);
            }
            append_flag = false;
            buffer.clear();
        }
        else
        {
            if (text[pos] == ",")
            {
                if (append_flag && buffer != "")
                {
                    data.append(this->_converter(buffer));
                }
                append_flag = true;
                buffer.clear();
            }
            else
            {
                if (text[pos] != " " && text[pos] != "\t" && text[pos] != "\n" && text[pos] != "　")
                {
                    buffer += text[pos];
                }
            }
            pos++;
        }
    }

    if (!end_flag)
    {
        printf("[ERROR] ]が閉じていません\n");
        return -1;
    }

    return pos + 1;
}

int JsonFile::_getObject(String text, Dict<String, Any> &data)
{
    // データ位置
    int pos = 1;
    String key = "";
    String buffer;
    bool key_flag = true;
    bool end_flag = false;

    // データ解析
    while (pos < len(text))
    {
        if (text[pos] == "}")
        {
            if (buffer != "")
            {
                data[key] = this->_converter(buffer);
                key.clear();
                buffer.clear();
            }
            end_flag = true;
            break;
        }
        else if (text[pos] == "{")
        {
            buffer.clear();
            Dict<String, Any> tmp;
            auto ret = _getObject(text.slice(pos, len(text)), tmp);
            // エラー処理の後始末
            if (ret < 0)
            {
                return -1;
            }
            pos += ret;

            // ERROR
            if (key_flag)
            {
                printf("[ERROR] キーに不正な値が入っています！\n");
                return -1;
            }

            data[key] = tmp;
            key.clear();
            buffer.clear();
            key_flag = true;
        }
        else if (text[pos] == "[")
        {
            buffer.clear();
            List<Any> tmp;
            auto ret = _getList(text.slice(pos, len(text)), tmp);
            // エラー処理の後始末
            if (ret < 0)
            {
                return -1;
            }
            pos += ret;

            // ERROR
            if (key_flag)
            {
                printf("[ERROR] キーに不正な値が入っています！ \n");
                return -1;
            }

            data[key] = tmp;
            key.clear();
            buffer.clear();
            key_flag = true;
        }
        else if (text[pos] == "\"")
        {
            buffer.clear();
            auto ret = _getString(text.slice(pos, len(text)), buffer);
            // エラー処理の後始末
            if (ret < 0)
            {
                return -1;
            }
            pos += ret;

            if (key_flag)
            {
                key = buffer;
            }
            else
            {
                data[key] = buffer;
                key.clear();
                buffer.clear();
            }
        }
        else
        {
            if (text[pos] == ":")
            {
                key_flag = false;
                buffer.clear();
            }
            else if (text[pos] == ",")
            {
                key_flag = true;
                if (buffer != "")
                {
                    data[key] = this->_converter(buffer);
                    key.clear();
                    buffer.clear();
                }
            }
            else
            {
                if (text[pos] != " " && text[pos] != "\t" && text[pos] != "\n" && text[pos] != "　")
                {
                    buffer += text[pos];
                }
            }
            pos++;
        }
    }

    if (!end_flag)
    {
        printf("[ERROR] }が閉じていません\n");
        return -1;
    }

    return pos + 1;
}

int JsonFile::_getString(String text, String &data)
{
    // データ位置
    int pos = 1;

    // 確認用
    bool end_flag = false;

    // データ解析
    while (pos < len(text))
    {
        if (text[pos] == "\"")
        {
            end_flag = true;
            break;
        }
        pos++;
    }

    if (!end_flag)
    {
        printf("[ERROR] \"が閉じていません\n");
        return -1;
    }

    data = text.slice(1, pos - 1);

    return pos + 1;
}

String JsonFile::_writeAny(Any value, int tab)
{
    String ret = "";
    // 型ごとに仕分け
    if (type(value) == "Dict")
    {
        Dict<String, Any> *tmp = value.getData<Dict<String, Any>>();
        ret += _writeObject(*tmp, tab + 1);
    }
    else if (type(value) == "List")
    {
        List<Any> *tmp = value.getData<List<Any>>();
        ret += _writeList(*tmp, tab + 1);
    }
    else if (type(value) == "String")
    {
        ret += "\"";
        ret += value.getLog();
        ret += "\"";
    }
    else if (type(value) == "Int" || type(value) == "Double")
    {
        ret += value.getLog();
    }
    else if (type(value) == "Bool")
    {
        Bool *tmp = value.getData<Bool>();
        if (*tmp)
        {
            ret += "true";
        }
        else
        {
            ret += "false";
        }
    }
    else if (type(value) == "None")
    {
        ret += "null";
    }
    else
    {
        ret += value.getLog();
    }

    return ret;
}

String JsonFile::_writeList(List<Any> data, int tab)
{
    String ret = "[\n";

    for (int i = 0; i < len(data); i++)
    {
        // コロンつける
        if (i > 0)
        {
            ret += ",\n";
        }

        // インデント
        for (int j = 0; j < tab + 1; j++)
        {
            ret += "\t";
        }

        // 値書き込み
        Any value = data[i];
        ret += _writeAny(data[i], tab);
    }

    // 後始末
    ret += "\n";
    for (int i = 0; i < tab; i++)
    {
        ret += "\t";
    }
    ret += "]";

    return ret;
}

String JsonFile::_writeObject(Dict<String, Any> data, int tab)
{
    String ret = "{\n";
    auto keys = data.getKeys();

    for (int i = 0; i < len(keys); i++)
    {
        // コロンつける
        if (i > 0)
        {
            ret += ",\n";
        }

        // インデント
        for (int j = 0; j < tab + 1; j++)
        {
            ret += "\t";
        }

        // キー書き込み
        ret += "\"";
        ret += keys[i] + "\": ";

        // 値書き込み
        ret += _writeAny(data[keys[i]], tab);
    }

    // 後始末
    ret += "\n";
    for (int i = 0; i < tab; i++)
    {
        ret += "\t";
    }
    ret += "}";

    return ret;
}
