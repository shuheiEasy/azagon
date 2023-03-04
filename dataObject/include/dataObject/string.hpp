#ifndef STRING_H
#define STRING_H

#include <dataObject/core.hpp>
#include <dataObject/list_impl.hpp>

namespace dataObject
{
    /// @brief 文字列クラス
    class String : public DataObject
    {
    private:
        struct Moji
        {
            char *data;
            int size;
        };

        int _MOJI_SIZE = 4;
        int _MEMORY_SIZE = 4;

        Moji *_data;
        int _length;
        int _memory_unit;

        void _converter(Moji *&ret, const char *text, int &size);
        int _convertNum(int pos) const;
        int _del(int start, int length);
        void _init();
        void _free_ptr();
        void _fromChar(const char letter, const int start);
        void _fromInt(const int data, const int start);
        void _fromFloat(const float data, const int start);
        void _fromDouble(const double data, const int start);
        void _getMemory(const int memory_size);
        int _getPos(int pos) const;
        int _judgeNum() const;
        void _malloc(Moji *&ret, int size);
        void _setData(const char *text, int start);

    public:
        /// @brief コンストラクタ
        String();
        String(const NoneType &none);
        /// @brief コンストラクタ
        /// @param data bool型のデータ
        String(const bool &data);
        /// @brief コンストラクタ
        /// @param data int型のデータ
        /// @details 数値を文字列に変換してデータを格納する
        String(const int &data);
        /// @brief コンストラクタ
        /// @param data float型のデータ
        /// @details 数値を文字列に変換してデータを格納する
        String(const float &data);
        /// @brief コンストラクタ
        /// @param data double型のデータ
        /// @details 数値を文字列に変換してデータを格納する
        String(const double &data);
        /// @brief コンストラクタ
        /// @param letter const char 型の文字列
        String(const char letter);
        /// @brief コンストラクタ
        /// @param text const char *型の文字列
        String(const char *text);
        /// @brief コンストラクタ
        /// @param text String型の文字列
        String(const String &text);
        /// @brief デコンストラクタ
        ~String();
        /// @brief 文字列を追加する関数
        /// @param data int型のデータ
        /// @details 数値を文字列に変換して追加する
        void append(const int &data);
        /// @brief 文字列を追加する関数
        /// @param data float型のデータ
        /// @details 数値を文字列に変換して追加する
        void append(const float &data);
        /// @brief 文字列を追加する関数
        /// @param data double型のデータ
        /// @details 数値を文字列に変換して追加する
        void append(const double &data);
        /// @brief 文字列を追加する関数
        /// @param text const char *型の文字列
        void append(const char letter);
        /// @brief 文字列を追加する関数
        /// @param text const char *型の文字列
        void append(const char *text);
        /// @brief 文字列を追加する関数
        /// @param text String型の文字列
        void append(const String text);
        /// @brief 文字列をすべて消す関数
        void clear();
        /// @brief 文字を消す関数
        /// @param start 消したい文字の位置
        void del(int start);
        /// @brief 文字列の一部を消す関数
        /// @param start 消したい文字列の先頭の文字の位置
        /// @param length 消したい文字列の長さ
        void del(int start, int length);
        /// @brief char *型へ変換する関数
        /// @return char *型
        char *getChar() const;
        const char *getType() const;
        const char *getLog() const;
        int getSize() const;
        /// @brief 文字列を挿入する関数
        /// @param text 挿入するchar *型の文字列
        /// @param start 挿入する位置
        void insert(const char *text, int start);
        /// @brief 文字列を挿入する関数
        /// @param text 挿入するString型の文字列
        /// @param start 挿入する位置
        void insert(const String text, int start);
        /// @brief 文字列が整数か判定する関数
        bool isdigit() const;
        /// @brief 文字列が数字か判定する関数
        bool isnumeric() const;
        /// @brief Stringクラスの比較演算子(==)
        /// @param data 比較するint型のデータ
        /// @return 数値が等しければtrueを出力。
        bool operator==(const int &data) const;
        /// @brief Stringクラスの比較演算子(==)
        /// @param data 比較するfloat型のデータ
        /// @return 数値が等しければtrueを出力。
        bool operator==(const float &data) const;
        /// @brief Stringクラスの比較演算子(==)
        /// @param data 比較するdouble型のデータ
        /// @return 数値が等しければtrueを出力。
        bool operator==(const double &data) const;
        /// @brief Stringクラスの比較演算子(==)
        /// @param letter 比較するconst char 型の文字列
        /// @return 文字列が等しければtrueを出力。
        bool operator==(const char letter) const;
        /// @brief Stringクラスの比較演算子(==)
        /// @param data 比較するconst char *型の文字列
        /// @return 文字列が等しければtrueを出力。
        bool operator==(const char *text) const;
        /// @brief Stringクラスの比較演算子(==)
        /// @param data 比較するString型の文字列
        /// @return 文字列が等しければtrueを出力。
        bool operator==(const String &text) const;
        /// @brief Stringクラスの比較演算子(!=)
        /// @param data 比較するint型のデータ
        /// @return 数値が異なればtrueを出力。
        bool operator!=(const int &data) const;
        /// @brief Stringクラスの比較演算子(!=)
        /// @param data 比較するfloat型のデータ
        /// @return 数値が異なればtrueを出力。
        bool operator!=(const float &data) const;
        /// @brief Stringクラスの比較演算子(!=)
        /// @param data 比較するdouble型のデータ
        /// @return 数値が異なればtrueを出力。
        bool operator!=(const double &data) const;
        /// @brief Stringクラスの比較演算子(!=)
        /// @param data 比較するconst char 型の文字列
        /// @return 文字列が異なればtrueを出力。
        bool operator!=(const char letter) const;
        /// @brief Stringクラスの比較演算子(!=)
        /// @param data 比較するconst char *型の文字列
        /// @return 文字列が異なればtrueを出力。
        bool operator!=(const char *text) const;
        /// @brief Stringクラスの比較演算子(!=)
        /// @param data 比較するString型の文字列
        /// @return 文字列が異なればtrueを出力。
        bool operator!=(const String &text) const;
        /// @brief Stringクラスの添字演算子
        /// @param id 取得したい文字の位置
        /// @return [String] 取得したい文字
        String operator[](const int id) const;
        /// @brief Stringクラスの代入演算子(=)
        /// @param data 代入するint型のデータ
        /// @return [String] 本クラスの文字列
        String operator=(const int &data);
        /// @brief Stringクラスの代入演算子(=)
        /// @param data 代入するfloat型のデータ
        /// @return [String] 本クラスの文字列
        String operator=(const float &data);
        /// @brief Stringクラスの代入演算子(=)
        /// @param data 代入するdouble型のデータ
        /// @return [String] 本クラスの文字列
        String operator=(const double &data);
        /// @brief Stringクラスの代入演算子(=)
        /// @param data 代入するconst char 型の文字列
        /// @return [String] 本クラスの文字列
        String operator=(const char letter);
        /// @brief Stringクラスの代入演算子(=)
        /// @param data 代入するconst char *型の文字列
        /// @return [String] 本クラスの文字列
        String operator=(const char *str);
        /// @brief Stringクラスの代入演算子(=)
        /// @param data 代入するString型の文字列
        /// @return [String] 本クラスの文字列
        String operator=(const String &str);
        /// @brief Stringクラスの代入演算子(+)
        /// @param data 追加するint型のデータ
        /// @return [String] 追加された文字列
        String operator+(const int &data) const;
        /// @brief Stringクラスの代入演算子(+)
        /// @param data 追加するfloat型のデータ
        /// @return [String] 追加された文字列
        String operator+(const float &data) const;
        /// @brief Stringクラスの代入演算子(+)
        /// @param data 追加するdouble型のデータ
        /// @return [String] 追加された文字列
        String operator+(const double &data) const;
        /// @brief Stringクラスの代入演算子(+)
        /// @param data 追加するconst char型の文字列
        /// @return [String] 追加された文字列
        String operator+(const char letter) const;
        /// @brief Stringクラスの代入演算子(+)
        /// @param data 追加するconst char *型の文字列
        /// @return [String] 追加された文字列
        String operator+(const char *str) const;
        /// @brief Stringクラスの代入演算子(+)
        /// @param data 追加するString型の文字列
        /// @return [String] 追加された文字列
        String operator+(const String &str) const;
        /// @brief Stringクラスの複合代入演算子(+=)
        /// @param data 追加するint型のデータ
        /// @return [String] 本クラスの文字列
        String &operator+=(const int &data);
        /// @brief Stringクラスの代入演算子(+=)
        /// @param data 追加するfloat型のデータ
        /// @return [String] 本クラスの文字列
        String &operator+=(const float &data);
        /// @brief Stringクラスの代入演算子(+=)
        /// @param data 追加するdouble型のデータ
        /// @return [String] 本クラスの文字列
        String &operator+=(const double &data);
        /// @brief Stringクラスの代入演算子(+=)
        /// @param data 追加するconst char型の文字列
        /// @return [String] 本クラスの文字列
        String &operator+=(const char letter);
        /// @brief Stringクラスの代入演算子(+=)
        /// @param data 追加するconst char *型の文字列
        /// @return [String] 本クラスの文字列
        String &operator+=(const char *str);
        /// @brief Stringクラスの代入演算子(+=)
        /// @param data 追加するString型の文字列
        /// @return [String] 本クラスの文字列
        String &operator+=(const String &str);
        /// @brief 文字列の一部を削除し、削除した文字列を取得する関数
        /// @param start 取得する文字列の先頭の文字の位置
        /// @param length 取得する文字列の長さ
        /// @return [String] 文字列
        String pop(int start, int length);
        /// @brief 文字列を置換する関数
        /// @param before 置換される文字列
        /// @param after 置換する文字列
        /// @return 置換済みの文字列
        String replace(const char *before,const char *after);
        /// @brief 文字列を置換する関数
        /// @param before 置換される文字列
        /// @param after 置換する文字列
        /// @return 置換済みの文字列
        String replace(const char * before,const String after);
        /// @brief 文字列を置換する関数
        /// @param before 置換される文字列
        /// @param after 置換する文字列
        /// @return 置換済みの文字列
        String replace(const String before,const char *after);
        /// @brief 文字列を置換する関数
        /// @param before 置換される文字列
        /// @param after 置換する文字列
        /// @return 置換済みの文字列
        String replace(const String before,const String after);
        /// @brief 文字列の一部を取得する関数
        /// @param start 取得する文字列の先頭の文字の位置
        /// @param length 取得する文字列の長さ
        /// @return [String] 文字列
        String slice(int start, int length) const;
        /// @brief 文字列を区切り文字列で分割する関数
        /// @param sep 区切り文字列
        /// @return [List<String>] 文字列のリスト
        List<String> split(const char sep);
        /// @brief 文字列を区切り文字列で分割する関数
        /// @param sep 区切り文字列
        /// @return [List<String>] 文字列のリスト
        List<String> split(const char *sep);
        /// @brief 文字列を区切り文字列で分割する関数
        /// @param sep 区切り文字列
        /// @return [List<String>] 文字列のリスト
        List<String> split(const String sep);
        /// @brief int型へ変換
        /// @return [int] 数値
        int toInt();
        /// @brief float型へ変換
        /// @return [float] 数値
        float toFloat();
        /// @brief double型へ変換
        /// @return [double] 数値
        double toDouble();
    };

    // String型変換

    /// @brief Stringクラスへ変換する関数
    /// @tparam T DataObjectクラス、もしくはその派生クラスを示すポインタ型
    /// @param text データを表すポインタの参照渡し
    /// @return Stringクラス
    template <class T, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr>
    inline String toString(T *&text)
    {
        return String(text->getLog());
    }

    /// @brief Stringクラスへ変換する関数
    /// @tparam T DataObjectクラスの派生クラス
    /// @param text DataObjectクラスの派生クラスの参照渡し
    /// @return Stringクラス
    template <class T>
    inline String toString(T &text, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr)
    {
        return String(text.getLog());
    }

    /// @brief Stringクラスへ変換する関数
    /// @tparam T DataObjectクラス
    /// @param text DataObjectクラスの参照渡し
    /// @return Stringクラス
    template <class T>
    inline String toString(T &text, typename std::enable_if<std::is_same<DataObject, T>::value>::type * = nullptr)
    {
        return String(text.getLog());
    }

    /// @brief Stringクラスへ変換する関数
    /// @tparam T 算術型
    /// @param text 算術型の参照渡し
    /// @return Stringクラス
    template <class T>
    inline String toString(const T &num, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr)
    {
        return String(num);
    }

    /// @brief Stringクラスへ変換する関数
    /// @tparam T 本関数に未対応の型
    /// @param text 未対応型の参照渡し
    /// @return Stringクラス
    template <class T>
    inline String toString(const T &text, typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_base_of<DataObject, T>::value>::type * = nullptr)
    {
        return "";
    }

    /// @brief Stringクラスへ変換する関数
    /// @param b bool型の参照渡し
    /// @return Stringクラス
    inline String toString(bool &b)
    {
        return String(b);
    }
    
    /// @brief Stringクラスへ変換する関数
    /// @param b boolのポインタ型の参照渡し
    /// @return Stringクラス
    inline String toString(bool *&b)
    {
        return String(*b);
    }

    /// @brief Stringクラスへ変換する関数
    /// @param num intのポインタ型の参照渡し
    /// @return Stringクラス
    inline String toString(int *&num)
    {
        return String(*num);
    }

    /// @brief Stringクラスへ変換する関数
    /// @param num floatのポインタ型の参照渡し
    /// @return Stringクラス
    inline String toString(float *&num)
    {
        return String(*num);
    }

    /// @brief Stringクラスへ変換する関数
    /// @param num doubleのポインタ型の参照渡し
    /// @return Stringクラス
    inline String toString(double *&num)
    {
        return String(*num);
    }

    /// @brief Stringクラスへ変換する関数
    /// @param text charのポインタ型の参照渡し
    /// @return Stringクラス
    inline String toString(char *text)
    {
        return String(text);
    }

    /// @brief Stringクラスへ変換する関数
    /// @param text const charのポインタ型の参照渡し
    /// @return Stringクラス
    inline String toString(const char *text)
    {
        return String(text);
    }

}

#endif