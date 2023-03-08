/**
 * @file dataObject.hpp
 * @author iijima-robot
 * @brief Anyクラスを宣言するヘッダファイル
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef COMMON_DATAOBJECT_ANY_H
#define COMMON_DATAOBJECT_ANY_H

#include <dataObject/dataObject.hpp>
#include <memory>

namespace dataObject
{
    /// @brief 任意の型を取れるクラス
    /// @details dataObject型を入力する。
    class Any : public DataObject
    {
    private:
        struct Storage
        {
            virtual ~Storage() {}
            virtual std::unique_ptr<Storage> copy() const { return nullptr; }
            virtual const char *getLog() const { return ""; }
            virtual int getSize() const { return 0; }
            virtual const char *getType() const { return "Null"; }
        };

        template <class T>
        struct Data : public Storage
        {
            T *_data;
            Data(const T &data)
            {
                _data = new T(data);
            }
            ~Data()
            {
                delete _data;
            }
            std::unique_ptr<Storage> copy() const
            {
                return std::unique_ptr<Storage>(new Data<T>(std::forward<T>(*_data)));
            }
            const char *getType() const { return _data->getType(); }
            int getSize() const { return _data->getSize(); }
            const char *getLog() const { return _data->getLog(); }
        };

        std::unique_ptr<Storage> _data_ptr;

    public:
        /// @brief コンストラクタ
        Any();
        /// @brief コンストラクタ
        /// @tparam T dataObject型の派生型
        /// @param data 代入するデータ
        template <class T, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr>
        Any(const T &data)
        {
            _data_ptr.reset(new Data<T>(data));
        }
        /// @brief コンストラクタ
        /// @param data 代入するboolデータ
        Any(const bool &data)
        {
            _data_ptr.reset(new Data<Bool>(data));
        }
        /// @brief コンストラクタ
        /// @param data 代入するintデータ
        Any(const int &data)
        {
            _data_ptr.reset(new Data<Int>(data));
        }
        /// @brief コンストラクタ
        /// @param data 代入するfloatデータ
        Any(const float &data)
        {
            _data_ptr.reset(new Data<Float>(data));
        }
        /// @brief コンストラクタ
        /// @param data 代入するdoubleデータ
        Any(const double &data)
        {
            _data_ptr.reset(new Data<Double>(data));
        }
        /// @brief コンストラクタ
        /// @param data 代入するcharデータ
        Any(const char data)
        {
            _data_ptr.reset(new Data<String>(data));
        }
        /// @brief コンストラクタ
        /// @param data 代入するchar*データ
        Any(const char *data)
        {
            _data_ptr.reset(new Data<String>(data));
        }
        /// @brief コピーコンストラクタ
        Any(const Any &data)
        {
            _data_ptr = data._data_ptr->copy();
        }
        /// @brief デコンストラクタ
        ~Any() {}

        /// @brief 値を取得する関数
        /// @tparam T 取得するデータの型
        /// @return 取得する値
        template <class T>
        T *getData()
        {
            Data<T> *ptr = dynamic_cast<Data<T> *>(_data_ptr.get());
            if (ptr == NULL)
            {
                printf("ERROR: Any型のgetData関数の型を間違えています\n");
                exit(1);
            }
            return ptr->_data;
        }

        const char *getLog() const { return _data_ptr->getLog(); }
        int getSize() const { return _data_ptr->getSize(); }
        const char *getType() const { return _data_ptr->getType(); }

        /// @brief 代入演算子
        /// @tparam T Any型に代入されている型
        /// @param data 代入するデータ
        /// @return 代入後のデータ
        template <class T, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr>
        Any operator=(const T &data)
        {
            _data_ptr.reset(new Data<T>(data));
            return *this;
        }

        /// @brief 代入演算子
        /// @param data 代入するデータ
        /// @return 代入後のデータ
        Any operator=(const Any &data)
        {
            _data_ptr = data._data_ptr->copy();
            return *this;
        }
    };
}

#endif