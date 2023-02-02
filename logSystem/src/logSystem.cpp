#include <logSystem/logSystem.hpp>

using namespace logSystem;
using namespace dataObject;
using namespace fileSystem;

/////////////////////////////////////////////////
//
// 関数
//
/////////////////////////////////////////////////

void logSystem::fprint(const String &format, ...)
{
    // 変数
    va_list args;

    // 引数取得
    va_start(args, format);

    // 出力
    String print_text = _vprint(format, args);

    // 解析終了
    va_end(args);

    // 出力
    printf("%s", print_text.getChar());
}

void logSystem::fprint(const char *format_char, ...)
{
    // 変数
    va_list args;

    // 引数取得
    va_start(args, format_char);

    // 出力
    String print_text = _vprint(String(format_char), args);

    // 解析終了
    va_end(args);

    // 出力
    printf("%s", print_text.getChar());
}

dataObject::String logSystem::_vprint(const String &format, va_list args)
{
    // 変数
    String format_str = format;
    List<String> format_list;

    // // 構文分析
    format_list = format_str.split("%s");
    String print_text = "";

    // 出力文作成
    for (int i = 0; i < format_list.getSize() - 1; i++)
    {
        print_text += format_list[i];
        print_text += va_arg(args, DataObject).getLog();
    }
    print_text += format_list[-1];

    return print_text;
}

String logSystem::logLevel_str(LogLevel level)
{
    String ret = "";
    switch (level)
    {
    case NOTSET:
        ret += "NOTSET";
        break;
    case DEBUG:
        ret += "DEBUG";
        break;
    case INFO:
        ret += "INFO";
        break;
    case WARNING:
        ret += "WARNING";
        break;
    case ERROR:
        ret += "ERROR";
        break;
    case CRITICAL:
        ret += "CRITICAL";
        break;
    default:
        ret += "CUSTOM";
        break;
    }
    return ret;
}

/////////////////////////////////////////////////
//
// PrintSystem
//
/////////////////////////////////////////////////

dataObject::String PrintSystem::getPrintStr()
{
    String print_text = "";
    for (int i = 0; i < _text_list->getSize(); i++)
    {
        print_text += _text_list->get(i);
    }
    return print_text;
}

void PrintSystem::print()
{
    String print_text = getPrintStr();
    printf("%s\n", print_text.getLog());
}