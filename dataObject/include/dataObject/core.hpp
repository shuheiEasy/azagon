/**
 * @file core.hpp
 * @author iijima-robot
 * @brief dataObjectライブラリの基礎となるヘッダファイル
 * @date 2022-09-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef COMMON_DATAOBJECT_CORE_H
#define COMMON_DATAOBJECT_CORE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include <string>
#include <type_traits>

/**
 * @brief 文字コードを指定
 * @note 将来、動的に変更できるようにする予定
 *
 */
#define LANGUAGECODE "ja_JP.UTF-8"

/**
 * @brief ビルドしたOSを判定
 * @details "Linux"、"Windows"を判定。エラー時に"OTHER"となる。
 *
 */
#ifdef __linux__
#define OSTYPE "LINUX"
#elif _WIN32
#define OSTYPE "WINDOWS"
#elif _WIN64
#define OSTYPE "WINDOWS"
#else
#define OSTYPE "OTHER"
#endif

/**
 * @brief dataObjectライブラリの空間。
 * @details 型クラスや型クラスに関連する関数を含んでいる空間。
 *
 */
namespace dataObject
{
    /**
     * @brief 基本型クラス
     * @details dataObjectライブラリの型クラスはすべて本クラスを継承し作成される。
     *
     */
    class DataObject
    {
    public:
        /**
         * @brief 型名を取得する仮想関数
         *
         * @return [const char* 型] 型名
         */
        virtual const char *getType() const { return "DataObject"; }
        /**
         * @brief 型クラス内の要素数を取得する仮想関数
         *
         * @return [int] 要素数
         */
        virtual int getSize() const { return 0; }
        /**
         * @brief ログ出力仮想関数
         *
         * @return [const char*]　型クラスが保持するログ情報
         */
        virtual const char *getLog() const { return "None"; }
        /**
         * @brief デストラクタ
         */
        virtual ~DataObject() {}
    };

    /// @brief データ情報がない場合を定義するクラス
    class NoneType : public DataObject
    {
    public:
        const char *getType() const { return "None"; }
        int getSize() const { return 0; }
        const char *getLog() const { return "None"; }
    };

    /// @brief None
    /// @details この変数はデータが無い状態を表す変数。データの代入などは出来ない。
    const static NoneType None;

    /**
     * @brief 型クラスの種類を分類する列挙型
     * @attention 廃止予定
     *
     */
    enum ClassType
    {
        ANYTYPE_CLASS = -1,
        NONETYPE_CLASS = 0,
        DATATYPE_CLASS = 100,
        LISTTYPE_CLASS
    };

    /**
     * @brief 型クラスの種類を判定するクラス
     * @attention 廃止予定
     *
     */
    template <class TYPE>
    class Type
    {
    private:
        template <class T, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr>
        void check(T *arg) { class_id = DATATYPE_CLASS; }
        template <class T, typename std::enable_if<!std::is_base_of<DataObject, T>::value>::type * = nullptr>
        void check(T *arg) { class_id = ANYTYPE_CLASS; }

        TYPE *_inner_class;

    public:
        /**
         * @brief 型クラスの判定結果
         *
         */
        ClassType class_id;
        /**
         * @brief コンストラクトすることで型判定を実行
         *
         */
        Type() { check(_inner_class); }
    };

}

#endif