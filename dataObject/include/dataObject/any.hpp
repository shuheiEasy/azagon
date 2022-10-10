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
            virtual Storage *copy() const { return nullptr; }
            virtual const char *getLog() const { return ""; }
            virtual int getSize() const { return 0; }
            virtual const char *getType() const {return "Null";}
        };

        template <class T, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr>
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
            Storage *copy() const
            {
                return new Data<T>(*_data);
            }
            const char *getType() const { return _data->getType(); }
            int getSize() const { return _data->getSize(); }
            const char *getLog() const { return _data->getLog(); }
        };

        Storage *_data_ptr;

    public:
        /// @brief コンストラクタ
        Any();
        /// @brief コンストラクタ
        /// @tparam T dataObject型の派生型
        /// @param data 代入するデータ
        /// @todo 将来的に算術型にも対応する予定
        template <class T>
        Any(const T &data, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr)
        {
            _data_ptr = new Data<T>(data);
        }
        /// @brief コピーコンストラクタ
        Any(const Any &data){
            _data_ptr = data._data_ptr->copy();
        }
        /// @brief デコンストラクタ
        ~Any()
        {
            delete _data_ptr;
        }
        /// @brief 値を取得する関数
        /// @tparam T 取得するデータの型
        /// @return 取得する値
        template <class T>
        T *getData()
        {
            Data<T> *ptr = dynamic_cast<Data<T> *>(_data_ptr);
            return ptr->_data;
        }
        const char *getLog() const { return _data_ptr->getLog(); }
        int getSize() const { return _data_ptr->getSize(); }
        const char *getType() const { return _data_ptr->getType(); }

        template <class T, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr>
        Any operator=(const T &data){
            delete _data_ptr;
            _data_ptr = new Data<T>(data);
            return *this;
        }
    };
}

#endif