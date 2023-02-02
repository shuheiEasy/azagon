#ifndef COMMON_LOG_SYSTEM_CORE_H
#define COMMON_LOG_SYSTEM_CORE_H

#include <stdarg.h>
#include <dataObject/dataObject.hpp>
#include <formatter/formatter.hpp>
#include <timeSystem/timeSystem.hpp>
#include <fileSystem/fileSystem.hpp>
/// @brief ログライブラリ
namespace logSystem
{
    /// @brief ログ出力レベルの列挙体
    enum LogLevel
    {
        NOTSET = 0,
        DEBUG = 10,
        INFO = 20,
        WARNING = 30,
        ERROR = 40,
        CRITICAL = 50
    };

    // 関数群

    /// @brief ログ出力
    /// @tparam 可変長型
    /// @param args, 入力する可変長データ 
    template <class... Args>
    void print(const Args &...args);
    /// @brief 書式設定可能ログ出力
    /// @param format 書式
    /// @param args 入力する可変長データ
    void fprint(const dataObject::String &format, ...);
    /// @brief 書式設定可能ログ出力
    /// @param format 書式
    /// @param args 入力する可変長データ
    void fprint(const char *format, ...);
    /// @cond
    // 書式を使って可変長データを文章へ変換
    dataObject::String _vprint(const dataObject::String &format, va_list args);
    /// @endcond

    /// @brief ログレベルをString型へ変換
    /// @param level ログレベル
    /// @return [String] ログレベルをString型へ変換したもの
    dataObject::String logLevel_str(LogLevel level);

    /// @brief 出力ログ生成クラス
    class PrintSystem
    {
    private:
        dataObject::List<dataObject::String> *_text_list;
        void _extractStr() {}
        template <class HeadClass, class... TailClass>
        void _extractStr(const HeadClass &head, TailClass &...tail);

    public:
        /// @brief コンストラクタ
        /// @param 可変長データ 出力したいデータ 
        template <class... Args>
        PrintSystem(const Args &...args);
        /// @brief デコンストラクタ
        ~PrintSystem() { delete _text_list; }
        /// @brief ログ生成
        /// @return [String] ログの文字列
        dataObject::String getPrintStr();
        /// @brief ログ出力
        void print(void);
    };

}

#endif