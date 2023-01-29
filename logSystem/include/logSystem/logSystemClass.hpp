#include <logSystem/core.hpp>

#ifndef COMMON_LOG_SYSTEM_CLASS_H
#define COMMON_LOG_SYSTEM_CLASS_H

namespace logSystem
{
    /// @brief ログ出力クラス
    class LogSystem: public dataObject::DataObject
    {
    private:
        fileSystem::TextFile *_file;
        LogLevel _log_level;
        formatter::Formatter _formatter;
        timeSystem::Datetime _datetime;

        // メゾット
        dataObject::String _generatePrintText(dataObject::String &&msg);
        void _init();
        void _setLoglevelText(LogLevel log_level);

    public:
        /// @brief コンストラクタ
        LogSystem();
        /// @brief コンストラクタ
        /// @param file_name ログを出力するファイル
        LogSystem(const char *file_name);
        /// @brief デコンストラクタ
        ~LogSystem();
        /// @brief 書式付きログ出力
        /// @param log_level ログレベル
        /// @param format 書式
        /// @param  可変長データ 出力するデータ
        /// @return 出力する結果
        int fprint(LogLevel log_level, const dataObject::String &format, ...);
        const char *getLog() const;
        int getSize() const;
        const char *getType() const;
        /// @brief ログを出力するファイルを設定する
        /// @param file_name ログを出力するファイル
        void setFile(const char *file_name);
        /// @brief ログの書式を設定する
        /// @param format 書式
        /// @details
        /// 書式の種類
        /// | 書式名 | 入力されるデータ |
        /// |--:|:--:|
        /// | levelname | ログレベル |
        /// | message | 出力するメッセージ |
        /// | year | ログを出力した年 |
        /// | month | ログを出力した月 |
        /// | day | ログを出力した日 |
        /// | hour | ログを出力した時間の時 |
        /// | min | ログを出力した時間の分 |
        /// | sec | ログを出力した時間の秒 |
        /// | msec | ログを出力した時間のミリ秒 |
        void setFormat(const char *format);
        /// @brief ログの書式を設定する
        /// @param format 書式
        /// @details
        /// 書式の種類
        /// | 書式名 | 入力されるデータ |
        /// |--:|:--:|
        /// | levelname | ログレベル |
        /// | message | 出力するメッセージ |
        /// | year | ログを出力した年 |
        /// | month | ログを出力した月 |
        /// | day | ログを出力した日 |
        /// | hour | ログを出力した時間の時 |
        /// | min | ログを出力した時間の分 |
        /// | sec | ログを出力した時間の秒 |
        /// | msec | ログを出力した時間のミリ秒 |
        void setFormat(const dataObject::String &format);
        /// @brief 出力するログレベルを設定する
        /// @param log_level ログレベル
        void setLevel(LogLevel log_level);
        /// @brief ログ出力
        /// @tparam ...Args 可変長型
        /// @param log_level ログレベル
        /// @param ...args 出力するデータ
        /// @return 出力する結果
        template <class... Args>
        int print(LogLevel log_level, Args &&...args);
    };

    /////////////////////////////////////////////////
    //
    // 実装部
    //
    /////////////////////////////////////////////////
    template <class... Args>
    int LogSystem::print(LogLevel log_level, Args &&...args)
    {
        if (log_level <= _log_level)
        {
            return -1;
        }
        _setLoglevelText(log_level);
        PrintSystem p(args...);
        dataObject::String print_text = _generatePrintText(p.getPrintStr());

        printf("%s", print_text.getLog());
        if(_file!=NULL){
            _file->writeline(print_text);
        }
        
        return 0;
    }
}
#endif