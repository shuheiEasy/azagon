#ifndef FILESYS_H
#define FILESYS_H

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include <string>

#include <dataObject/dataObject.hpp>

/// @brief ファイル操作ライブラリの空間
namespace fileSystem
{
    /// @brief ファイル種類を表す列挙体
    /// @details
    /// | 種類 | 凡例 |
    /// |--:|:--:|
    /// | FT_Unknown | 不明なファイル |
    /// | FT_NoExist | 存在していないファイル |
    /// | FT_File | ファイル |
    /// | FT_Dir | ディレクトリ |
    enum FileType
    {
        FT_Unknown = -100,
        FT_NoExist = 0,
        FT_File = 1,
        FT_Dir,
    };

    /// @brief ファイル状況を表す列挙体
    /// @details
    /// | モード | 状態 |
    /// |--:|:--:|
    /// | UNKNOWNMODE | 状態不明 |
    /// | CLOSEMODE | ファイルを閉じた状態 |
    /// | READMODE | ファイルを読み込みモードで開いた状態 |
    /// | WRITEMODE | ファイルを上書きモードで開いた状態 |
    /// | APPENDMODE | ファイルを追記モードで開いた状態 |
    enum FileMode
    {
        UNKNOWNMODE = -100,
        CLOSEMODE = -1,
        READMODE = 0,
        WRITEMODE,
        APPENDMODE
    };

    /// @brief ファイルクラス
    class File : public dataObject::DataObject
    {
    protected:
        FileType _filetype;
        FileMode _filemode;
        dataObject::String _path;
        dataObject::String _name;
        dataObject::String _extension;
        FILE *_file_ptr;

        // メンバ関数
        void _init(dataObject::String path);
        void _setDirPath();
        void _setExtension();
        void _setName();

    public:
        /// @brief コンストラクタ
        File();
        /// @brief コンストラクタ
        /// @param path パス
        File(const char *path);
        /// @brief コンストラクタ
        /// @param path パス
        File(const dataObject::String &path);
        /// @brief コピーコンストラクタ
        /// @param file ファイル
        File(const File &file);
        /// @brief デコンストラクタ
        ~File();
        const char *getType() const { return "File"; }
        int getSize() const;
        const char *getLog() const { return _path.getChar(); }

        // 独自メンバ関数

        /// @brief ファイル閉じる
        void close();
        /// @brief ファイル存在判定
        /// @return [Bool] ファイルが存在したときTrueを出力
        dataObject::Bool exists() const;
        /// @brief 拡張子取得
        /// @return [String] 拡張子
        dataObject::String getExtension() const;
        /// @brief ファイルポインタ
        /// @return [FILE] ファイルポインタ
        FILE *getFilePtr();
        /// @brief ファイル形式取得
        /// @return [FileType] ファイル種類
        FileType getFileType() const;
        /// @brief 名前取得
        /// @return [String] ファイル名
        dataObject::String getName() const;
        /// @brief Path取得
        /// @return [String] ファイルのパス
        dataObject::String getPath() const;
        /// @brief ディレクトリ判定
        /// @return [Bool] ディレクトリである場合Trueを出力
        dataObject::Bool isdir() const;
        /// @brief ファイル判定
        /// @return [Bool] ファイルである場合Trueを出力
        dataObject::Bool isfile() const;
        /// @brief ディレクトリ作成
        /// @return [Bool] ディレクトリ作成が成功した場合Trueを出力
        dataObject::Bool mkdir();
        /// @brief ファイル作成
        /// @return [Bool] ファイル作成が成功した場合Trueを出力
        dataObject::Bool mkfile();
        /// @brief ファイル開く
        /// @param mode ファイルを開くモード
        /// @return [Bool] ファイルが正しく開けた場合Trueを出力
        dataObject::Bool open(const char *mode);
        /// @brief ファイル開く
        /// @param mode ファイルを開くモード
        /// @return [Bool] ファイルが正しく開けた場合Trueを出力
        dataObject::Bool open(FileMode mode);
        /// @brief ファイル削除
        /// @param force_mode フォルダの中身があるときも削除する場合はtrueを指定
        /// @return 正しく削除できた場合にtrueを返す
        dataObject::Bool remove(const bool force_mode = false);
        /// @brief ファイル作成
        /// @return [Bool] ファイル作成が成功した場合Trueを出力
        dataObject::Bool touch();
    };

    /// @brief テキストファイルクラス
    class TextFile : public File
    {
    public:
        // メンバ関数

        /// @brief コンストラクタ
        TextFile();
        /// @brief コンストラクタ
        /// @param path パス
        TextFile(const char *path);
        /// @brief コンストラクタ
        /// @param path パス
        TextFile(dataObject::String &path);
        /// @brief コピーコンストラクタ
        /// @param file ファイル
        TextFile(const File &file);
        /// @brief デコンストラクタ
        ~TextFile();
        const char *getType() const { return "TextFile"; }

        // 独自メンバ関数

        /// @brief ファイル全体を読み込み
        /// @param output 読み込んだテキスト
        /// @return [Int] 読み込み結果
        /// @details
        /// | 読み込み結果の値 | 読み込み状態 |
        /// |--:|:--:|
        /// | 0 | 読み込み成功 |
        /// | -1 | ファイル以外のため読み込みを中止 |
        /// | -2 | ファイルの読み込みが失敗 |
        dataObject::Int read(dataObject::String &output);
        /// @brief ファイル全体を読み込み
        /// @return [String] 読み込んだテキスト
        dataObject::String read();
        /// @brief 行ごとに読み取り
        /// @param output 読み込んだテキストの各行ごとのリスト
        /// @return [Int] 読み込み結果
        /// @details
        /// | 読み込み結果の値 | 読み込み状態 |
        /// |--:|:--:|
        /// | 0 | 読み込み成功 |
        /// | -1 | ファイル以外のため読み込みを中止 |
        /// | -2 | ファイルの読み込みが失敗 |
        dataObject::Int readlines(dataObject::List<dataObject::String> &text_lines);
        /// @brief 行ごとに読み取り
        /// @return [String] 読み込んだテキストの各行ごとのリスト
        dataObject::List<dataObject::String> readlines();
        /// @brief 書き込み
        /// @param text 書き込む文章
        /// @param mode 書き込みモード
        /// @param close_flag ファイル閉じるフラグ（既定値:true）
        /// @return [Int] 書き込み結果
        dataObject::Int write(const char *text, FileMode mode = APPENDMODE, dataObject::Bool close_flag = true);
        /// @brief 書き込み
        /// @param text 書き込む文章
        /// @param mode 書き込みモード
        /// @param close_flag ファイル閉じるフラグ（既定値:true）
        /// @return [Int] 書き込み結果
        dataObject::Int write(dataObject::String text, FileMode mode = APPENDMODE, dataObject::Bool close_flag = true);
        /// @brief 改行したものを書き込み
        /// @param text 書き込む文章
        /// @param mode 書き込みモード
        /// @param close_flag ファイル閉じるフラグ（既定値:true）
        /// @return [Int] 書き込み結果
        dataObject::Int writeline(const char *text, FileMode mode = APPENDMODE, dataObject::Bool close_flag = true);
        /// @brief 改行したものを書き込み
        /// @param text 書き込む文章
        /// @param mode 書き込みモード
        /// @param close_flag ファイル閉じるフラグ（既定値:true）
        /// @return [Int] 書き込み結果
        dataObject::Int writeline(dataObject::String text, FileMode mode = APPENDMODE, dataObject::Bool close_flag = true);
        /// @brief 行のリストを書き込み
        /// @param text 書き込む文章の行のリスト
        /// @param mode 書き込みモード
        /// @param close_flag ファイル閉じるフラグ（既定値:true）
        /// @return [Int] 書き込み結果
        dataObject::Int writelines(dataObject::List<dataObject::Bool> &text_lines, FileMode mode = APPENDMODE, dataObject::Bool close_flag = true);
        /// @brief 行のリストを書き込み
        /// @param text 書き込む文章の行のリスト
        /// @param mode 書き込みモード
        /// @param close_flag ファイル閉じるフラグ（既定値:true）
        /// @return [Int] 書き込み結果
        dataObject::Int writelines(dataObject::List<dataObject::Int> &text_lines, FileMode mode = APPENDMODE, dataObject::Bool close_flag = true);
        /// @brief 行のリストを書き込み
        /// @param text 書き込む文章の行のリスト
        /// @param mode 書き込みモード
        /// @param close_flag ファイル閉じるフラグ（既定値:true）
        /// @return [Int] 書き込み結果
        dataObject::Int writelines(dataObject::List<dataObject::Float> &text_lines, FileMode mode = APPENDMODE, dataObject::Bool close_flag = true);
        /// @brief 行のリストを書き込み
        /// @param text 書き込む文章の行のリスト
        /// @param mode 書き込みモード
        /// @param close_flag ファイル閉じるフラグ（既定値:true）
        /// @return [Int] 書き込み結果
        dataObject::Int writelines(dataObject::List<dataObject::Double> &text_lines, FileMode mode = APPENDMODE, dataObject::Bool close_flag = true);
        /// @brief 行のリストを書き込み
        /// @param text 書き込む文章の行のリスト
        /// @param mode 書き込みモード
        /// @param close_flag ファイル閉じるフラグ（既定値:true）
        /// @return [Int] 書き込み結果
        dataObject::Int writelines(dataObject::List<dataObject::String> &text_lines, FileMode mode = APPENDMODE, dataObject::Bool close_flag = true);
    };

    /// @brief ディレクトリクラス
    /// @attention 廃止予定
    class FileExplorer : public dataObject::DataObject
    {
    private:
        File *_dir;
        dataObject::List<File> *_file_list;
        void _init();
        int _searchDir(void);

    public:
        FileExplorer();
        /// @brief コンストラクタ
        /// @param path パス
        FileExplorer(const dataObject::String &path);
        FileExplorer(const char *path);
        /// @brief デコンストラクタ
        ~FileExplorer();
        /// @brief ディレクトリのリスト
        /// @return List<File> ディレクトリリスト
        dataObject::List<File> getDirList();
        dataObject::List<File> getFileList();
        dataObject::List<File> getFileList(const char *extension);
        /// @brief 指定した拡張子のファイルリストの取得
        /// @param extension 拡張子
        /// @return List<File> ファイルリスト
        dataObject::List<File> getFileList(const dataObject::String extension);
        const char *getLog() const;
        int getSize() const;
        const char *getType() const { return "FileExplorer"; }
        /// @brief 代入演算子
        /// @param path パス
        FileExplorer &operator=(const dataObject::String &path);
        FileExplorer &operator=(const char *path);
        /// @brief ディレクトリへのパス
        /// @param path パス
        void setPath(const dataObject::String &path);
        void setPath(const char *path);
    };

    /// @brief Jsonファイルクラス
    class JsonFile : public dataObject::DataObject
    {
    private:
        TextFile *textFile;

        dataObject::Any _converter(dataObject::String text);
        int _getList(dataObject::String text, dataObject::List<dataObject::Any> &data_);
        int _getObject(dataObject::String text, dataObject::Dict<dataObject::String, dataObject::Any> &data_);
        int _getString(dataObject::String text, dataObject::String &data_);

        dataObject::String _writeAny(dataObject::Any value, int tab);
        dataObject::String _writeList(dataObject::List<dataObject::Any> data_, int tab);
        dataObject::String _writeObject(dataObject::Dict<dataObject::String, dataObject::Any> data_, int tab);

    public:
        /// @brief JSONデータ
        dataObject::Any data;

        /// @brief コンストラクタ
        JsonFile();
        /// @brief コンストラクタ
        /// @param file_path ファイルのパス
        JsonFile(const dataObject::String &file_path);
        JsonFile(const char *file_path);
        /// @brief デコンストラクタ
        ~JsonFile();

        const char *getType() const;
        int getSize() const;
        const char *getLog() const;

        /// @brief Jsonデータの辞書型を取得する関数
        /// @return Jsonデータの辞書型
        dataObject::Dict<dataObject::String, dataObject::Any> &getDict();
        /// @brief Jsonデータの辞書型を取得する関数
        /// @param Jsonデータの辞書型
        /// @return 成功した場合0を返す
        int getDict(dataObject::Dict<dataObject::String, dataObject::Any> *&dict);

        /// @brief Jsonデータのリスト型を取得する関数
        /// @return Jsonデータのリスト型
        dataObject::List<dataObject::Any> &getList();
        /// @brief Jsonデータのリスト型を取得する関数
        /// @param Jsonデータのリスト型
        /// @return 成功した場合0を返す
        int getList(dataObject::List<dataObject::Any> *&list);

        /// @brief オペレータ(添字演算子)
        /// @param key キー
        /// @return 値
        /// @details 存在しないキーが存在しない場合はキーを登録する
        dataObject::Any &operator[](const int key);
        dataObject::Any &operator[](const dataObject::String key);

        /// @brief ファイルの再読み込み
        /// @return 読込結果
        /// @details 読込成功時に0を返す
        int read();

        /// @brief JSONデータを文字列形式で設定する
        /// @param data JSONデータを表す文字列
        int setData(const dataObject::String &data);
        int setData(const char *data);

        /// @brief Jsonファイルのパスを設定する
        /// @param file_path ファイルのパス
        void setPath(const dataObject::String &file_path);
        void setPath(const char *file_path);

        /// @brief ファイルへ書き込み
        void write();
    };

    /////////////////////////////////////////////
    // 関数群
    /////////////////////////////////////////////

    /// @brief 絶対パスを取得する関数
    /// @param path 相対パス・絶対パスを表す文字列
    /// @return [String] 絶対パスを表す文字列
    dataObject::String getAbsolutePath(dataObject::String &path);
    /// @brief カレントディレクトリ取得
    /// @param size バッファのサイズ
    /// @return カレントディレクトリのパス
    dataObject::String getCurrentDir(const int size = 1024);
    /// @brief ディレクトリ内のディレクトリリスト
    /// @param path ディレクトリのパス
    /// @return List<File> ディレクトリリスト
    dataObject::List<File> getDirList(const char *path);
    /// @brief ディレクトリ内のディレクトリリスト
    /// @param path ディレクトリのパス
    /// @return List<File> ディレクトリリスト
    dataObject::List<File> getDirList(const dataObject::String &path);
    /// @brief ディレクトリ内のディレクトリリスト
    /// @param dir ディレクトリ
    /// @return List<File> ディレクトリリスト
    dataObject::List<File> getDirList(const File &dir);
    /// @brief ディレクトリ内のファイルリスト
    /// @param path ディレクトリのパス
    /// @return List<File> ファイルリスト
    dataObject::List<File> getFileList(const char *path);
    /// @brief ディレクトリ内のファイルリスト
    /// @param path ディレクトリのパス
    /// @param extension 拡張子
    /// @return List<File> ファイルリスト
    dataObject::List<File> getFileList(const char *path, const char *extension);
    /// @brief ディレクトリ内のファイルリスト
    /// @param path ディレクトリのパス
    /// @param extension 拡張子
    /// @return List<File> ファイルリスト
    dataObject::List<File> getFileList(const char *path, const dataObject::String &extension);
    /// @brief ディレクトリ内のファイルリスト
    /// @param path ディレクトリのパス
    /// @return List<File> ファイルリスト
    dataObject::List<File> getFileList(const dataObject::String &path);
    /// @brief ディレクトリ内のファイルリスト
    /// @param path ディレクトリのパス
    /// @param extension 拡張子
    /// @return List<File> ファイルリスト
    dataObject::List<File> getFileList(const dataObject::String &path, const char *extension);
    /// @brief ディレクトリ内のファイルリスト
    /// @param path ディレクトリのパス
    /// @param extension 拡張子
    /// @return List<File> ファイルリスト
    dataObject::List<File> getFileList(const dataObject::String &path, const dataObject::String &extension);
    /// @brief ディレクトリ内のファイルリスト
    /// @param dir ディレクトリ
    /// @return List<File> ファイルリスト
    dataObject::List<File> getFileList(const File &dir);
    /// @brief ディレクトリ内のファイルリスト
    /// @param dir ディレクトリ
    /// @param extension 拡張子
    /// @return List<File> ファイルリスト
    dataObject::List<File> getFileList(const File &dir, const char *extension);
    /// @brief ディレクトリ内のファイルリスト
    /// @param dir ディレクトリ
    /// @param extension 拡張子
    /// @return List<File> ファイルリスト
    dataObject::List<File> getFileList(const File &dir, const dataObject::String &extension);
    /// @brief パスを区切り文字で分割したリスト
    /// @param path パスを表す文字列
    /// @return [List<String>] パスのリスト
    dataObject::List<dataObject::String> getPathList(dataObject::String &path);
    /*!
    @brief カレントディレクトリ移動
    @param path バッファのサイズ
    @return 移動結果
        @li 0 成功
        @li -1 ディレクトリが存在しません
        @li -2 失敗
    */
    dataObject::Int moveCurrentDir(const dataObject::String &path);
}
#endif