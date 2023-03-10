/**
 * @file dict.hpp
 * @author iijima-robot
 * @brief Dictクラスを宣言するヘッダファイル
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef COMMON_DATAOBJECT_DICT_H
#define COMMON_DATAOBJECT_DICT_H

#include <dataObject/core.hpp>
#include <dataObject/list_impl.hpp>

namespace dataObject
{
    /// @brief 辞書型クラスの要素クラス
    /// @tparam K_T キーの型
    /// @tparam V_T 値の型
    template <class K_T, class V_T>
    class DictItem : public DataObject
    {
    public:
        K_T key;
        V_T value;

        DictItem(const K_T &key_, const V_T &value_)
        {
            key = key_;
            value = value_;
        }

        const char *getLog() const;
        int getSize() const
        {
            return 1;
        }

        const char *getType() const
        {
            return "DictItem";
        }
    };

    template <class K_T, class V_T>
    class Dict;

    /// @brief 辞書型クラスのイテレータクラス
    /// @tparam K_T キーの型
    /// @tparam V_T 値の型
    template <class K_T, class V_T>
    class DictIterator : public std::iterator<std::forward_iterator_tag, DictItem<K_T, V_T>>
    {
    private:
        // 辞書型クラスをfriend指定
        friend Dict<K_T, V_T>;

        // 辞書型クラス
        Dict<K_T, V_T> *dict;

        // 参照先のID
        int dict_list_id = 0;

        /// @brief コンストラクタ
        /// @param dict_ 辞書のポインター
        /// @param list_id 要素番号
        DictIterator(Dict<K_T, V_T> *dict_, int list_id);

    public:
        /// @brief コピーコンストラクタ
        /// @param other コピー元のイテレータ
        DictIterator(const DictIterator<K_T, V_T> &other);

        /// @brief 間接参照演算子
        /// @return [DictItem型] キーと値のペア
        DictItem<K_T, V_T> &operator*();

        /// @brief インクリメント演算子
        /// @return 参照先をずらす
        DictIterator<K_T, V_T> &operator++();
        DictIterator<K_T, V_T> operator++(int);

        /// @brief 比較演算子
        /// @param other 比較元のイテレータ
        /// @return [bool] 比較元のデータと同じならtrue
        bool operator==(const DictIterator<K_T, V_T> &other);
        bool operator!=(const DictIterator<K_T, V_T> &other);
    };

    /// @brief 辞書型クラス
    /// @tparam K_T Keyの型
    /// @tparam V_T Valueの型
    template <class K_T, class V_T>
    class Dict : public DataObject
    {
    private:
        // 辞書型のイテレータクラスをfriend指定
        friend DictIterator<K_T, V_T>;

        // 格納データ
        List<DictItem<K_T, V_T>> _key_and_value_list;

        // 同じ名前が登録されていないか検索
        int _search(const K_T &key);

    public:
        typedef DictIterator<K_T, V_T> iterator;

        Dict() {}
        Dict(const Dict<K_T, V_T> &dict);
        /// @brief 要素を取得する関数
        /// @param key キー
        /// @return 値
        /// @details 存在しないキーが存在しない場合はキーを登録する
        V_T &at(const K_T key);
        /// @brief 先頭のイテレータを取得
        /// @return [DictIterator<K_T, V_T>] 先頭のイテレータ
        Dict<K_T, V_T>::iterator begin();
        /// @brief 辞書を削除
        void clear();
        /// @brief 要素を削除
        /// @param key 削除する要素のキー
        /// @details 存在しないキーを指定した場合動作しない
        void del(const K_T &key);
        /// @brief キーが存在するか判定
        /// @param key 検索したいキー
        /// @return キーが存在する場合はTrue
        bool exist(const K_T &key);
        /// @brief 末尾のイテレータを取得
        /// @return [DictIterator<K_T, V_T>] 末尾のイテレータ
        Dict<K_T, V_T>::iterator end();
        /// @brief 辞書を拡張する
        /// @param dict 追加する辞書
        void extend(const Dict<K_T, V_T> &dict);
        /// @brief 要素を取得する関数
        /// @param key 検索するキー
        /// @param value 取得したい値
        /// @return キーが存在したら0を返す
        int getData(const K_T &key, V_T &value);
        List<K_T> getKeys() const;
        const char *getLog() const;
        int getSize() const;
        const char *getType() const;
        List<V_T> getValues() const;
        /// @brief オペレータ(添字演算子)
        /// @param key キー
        /// @return 値
        /// @details 存在しないキーが存在しない場合はキーを登録する
        V_T &operator[](const K_T key);
        /// @brief オペレータ(代入演算子)
        /// @param dict 代入する辞書
        /// @return [Dict] データが代入された辞書
        Dict<K_T, V_T> &operator=(const Dict<K_T, V_T> &dict);
        /// @brief オペレータ(複合代入演算子)
        /// @param dict 追加する辞書
        /// @return [Dict] データが代入された辞書
        Dict<K_T, V_T> &operator+=(const Dict<K_T, V_T> &dict);
        /// @brief 要素を設定する関数
        /// @param key 設定する要素のキー
        /// @param value 設定する要素の値
        /// @details 存在するキーの場合はその要素を上書き
        void update(const K_T &key, const V_T &value);
    };
}
#endif