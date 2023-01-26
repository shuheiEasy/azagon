/**
 * @file print.hpp
 * @author iijima-robot
 * @brief リストクラスおよび辞書クラスの出力を実装するヘッダファイル
 * @date 2022-09-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef COMMON_DATAOBJECT_PRINT_H
#define COMMON_DATAOBJECT_PRINT_H

#include <dataObject/any.hpp>
#include <dataObject/list.hpp>
#include <dataObject/string.hpp>
#include <dataObject/dict_impl.hpp>

namespace dataObject
{
    /// @cond
    // 型判定
    template <class T>
    class Type<List<T>>
    {
    public:
        ClassType class_id;
        Type() { class_id = LISTTYPE_CLASS; }
    };
    /// @endcond

    template <class T, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr>
    inline String toMemberString(T *&value)
    {
        String ret;
        if (String(value->getType()) == "String")
        {
            ret += "\"";
        }
        ret += value->getLog();
        if (String(value->getType()) == "String")
        {
            ret += "\"";
        }
        return ret;
    }

    template <class T, typename std::enable_if<std::is_base_of<DataObject, T>::value>::type * = nullptr>
    inline String toMemberString(T &value)
    {
        String ret;
        if (String(value.getType()) == "String")
        {
            ret += "\"";
        }
        ret += value.getLog();
        if (String(value.getType()) == "String")
        {
            ret += "\"";
        }
        return ret;
    }

    template <class T, typename std::enable_if<!std::is_base_of<DataObject, T>::value>::type * = nullptr>
    inline String toMemberString(T &value)
    {
        return toString(value);
    }

    template <class T>
    const char *List<T>::getLog() const
    {
        _Node<T> *ptr = _head->next;
        String ret = "[ ";

        while (ptr != _tail)
        {
            String tmp = toMemberString(ptr->data);

            if (ptr != _head->next)
            {
                ret += ", ";
            }
            ret += tmp;
            ptr = ptr->next;
        }

        ret += " ]";

        return ret.getChar();
    }

    template <class K_T, class V_T>
    const char *Dict<K_T, V_T>::getLog() const
    {
        String ret = "{ ";

        for (int i = 0; i < _key_list.getSize(); i++)
        {
            if (i != 0)
            {
                ret += ", ";
            }
            K_T key = _key_list.get(i);
            V_T value = _value_list.get(i);
            ret += toMemberString(key);
            ret += ": ";
            ret += toMemberString(value);
        }

        ret += " }";

        return ret.getChar();
    }
}
#endif