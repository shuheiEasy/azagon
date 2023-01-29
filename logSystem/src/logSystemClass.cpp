#include <logSystem/logSystem.hpp>

using namespace logSystem;
using namespace dataObject;
using namespace fileSystem;

/////////////////////////////////////////////////
//
// public
//
/////////////////////////////////////////////////
LogSystem::LogSystem()
{
    _init();
}

LogSystem::LogSystem(const char *file_name)
{
    _init();
    setFile(file_name);
}

LogSystem::~LogSystem()
{
    if (_file != NULL)
    {
        delete _file;
    }
}

const char *LogSystem::getLog() const{return "LogSystem";}
int LogSystem::getSize() const{return 1;}
const char *LogSystem::getType() const{return "LogSystem";}

void LogSystem::setFile(const char *file_name)
{
    _file = new TextFile(file_name);
}

void LogSystem::setFormat(const char *format)
{
    _formatter.setFormat(format);
}

void LogSystem::setFormat(const dataObject::String &format)
{
    _formatter.setFormat(format);
}

void LogSystem::setLevel(LogLevel log_level)
{
    _log_level = log_level;
}

int LogSystem::fprint(LogLevel log_level, const dataObject::String &format, ...)
{
    if (log_level <= _log_level)
    {
        return -1;
    }

    _setLoglevelText(log_level);

    va_list args;
    va_start(args, format);
    String print_text = _generatePrintText(logSystem::_vprint(format, args));
    va_end(args);

    printf("%s", print_text.getChar());

    return 0;
}

/////////////////////////////////////////////////
//
// private
//
/////////////////////////////////////////////////
String LogSystem::_generatePrintText(dataObject::String &&msg)
{
    _formatter.setData("message", msg.getChar());
    _datetime.now();
    _formatter.setData("year", String(_datetime.year()));
    _formatter.setData("month", String(_datetime.month()));
    _formatter.setData("day", String(_datetime.day()));
    _formatter.setData("hour", String(_datetime.hour()));
    _formatter.setData("min", String(_datetime.minute()));
    _formatter.setData("sec", String(_datetime.second()));
    _formatter.setData("msec", String(_datetime.millisec()));
    return _formatter.generateText();
}

void LogSystem::_init()
{
    _file = NULL;
    _log_level = WARNING;
    setFormat("${year}-${month:02}-${day:02} ${hour:02}:${min:02}:${sec:02},${msec:03} [${levelname}] ${message}\n");
}

void LogSystem::_setLoglevelText(LogLevel log_level)
{
    _formatter.setData("levelname", logLevel_str(log_level));
}