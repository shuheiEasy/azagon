/**
 * @file dict.hpp
 * @author iijima-robot
 * @brief Dictクラスを宣言するヘッダファイル
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef COMMON_DATAOBJECT_DICT_IMPL_H
#define COMMON_DATAOBJECT_DICT_IMPL_H

#include <dataObject/dict.hpp>
#include <stdexcept>

namespace dataObject
{
    template <class K_T, class V_T>
    Dict<K_T, V_T>::Dict(const Dict<K_T, V_T> &dict)
    {
        this->clear();
        this->extend(dict);
    }

    template <class K_T, class V_T>
    V_T &Dict<K_T, V_T>::at(const K_T key)
    {
        int find_id = _search(key);

        if (find_id < 0)
        {
            _key_list.append(key);
            _value_list.append(V_T());
        }

        return _value_list[find_id];
    }

    template <class K_T, class V_T>
    void Dict<K_T, V_T>::clear()
    {
        _key_list.clear();
        _value_list.clear();
    }

    template <class K_T, class V_T>
    void Dict<K_T, V_T>::del(const K_T &key)
    {
        int del_id = _search(key);

        if (del_id > -1)
        {
            _key_list.del(del_id);
            _value_list.del(del_id);
        }
    }

    template <class K_T, class V_T>
    bool Dict<K_T, V_T>::exist(const K_T &key)
    {
        int find_id = _search(key);

        if (find_id < 0)
        {
            return false;
        }
        return true;
    }

    template <class K_T, class V_T>
    void Dict<K_T, V_T>::extend(const Dict<K_T, V_T> &dict)
    {
        auto key_list = dict.getKeys();
        auto value_list = dict.getValues();
        for (int i = 0; i < key_list.getSize(); i++)
        {
            this->update(key_list.get(i), value_list.get(i));
        }
    }

    template <class K_T, class V_T>
    int Dict<K_T, V_T>::getData(const K_T &key, V_T &value)
    {
        int find_id = _search(key);
        if (find_id < 0)
        {
            return -1;
        }

        value = _value_list[find_id];
        return 0;
    }

    template <class K_T, class V_T>
    List<K_T> Dict<K_T, V_T>::getKeys() const
    {
        return _key_list;
    }

    template <class K_T, class V_T>
    int Dict<K_T, V_T>::getSize() const
    {
        return _key_list.getSize();
    }

    template <class K_T, class V_T>
    const char *Dict<K_T, V_T>::getType() const
    {
        return "Dict";
    }

    template <class K_T, class V_T>
    List<V_T> Dict<K_T, V_T>::getValues() const
    {
        return _value_list;
    }

    template <class K_T, class V_T>
    V_T &Dict<K_T, V_T>::operator[](const K_T key)
    {
        return this->at(key);
    }

    template <class K_T, class V_T>
    Dict<K_T, V_T> &Dict<K_T, V_T>::operator=(const Dict<K_T, V_T> &dict)
    {
        this->clear();
        this->extend(dict);
        return *this;
    }

    template <class K_T, class V_T>
    Dict<K_T, V_T> &Dict<K_T, V_T>::operator+=(const Dict<K_T, V_T> &dict)
    {
        this->extend(dict);
        return *this;
    }

    template <class K_T, class V_T>
    void Dict<K_T, V_T>::update(const K_T &key, const V_T &value)
    {
        // 同じ名前が登録されていないか判定
        int add_id = _search(key);

        if (add_id < 0)
        {
            _key_list.append(key);
            _value_list.append(value);
        }
        else
        {
            _value_list[add_id] = value;
        }
    }

    ///////////////////////////////////////////////////////
    //
    //  private
    //
    ///////////////////////////////////////////////////////
    template <class K_T, class V_T>
    int Dict<K_T, V_T>::_search(const K_T &key)
    {
        int find_id = -1;
        for (int i = 0; i < _key_list.getSize(); i++)
        {
            if (_key_list[i] == key)
            {
                find_id = i;
                break;
            }
        }
        return find_id;
    }
}

#endif