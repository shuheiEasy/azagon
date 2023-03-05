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
    ///////////////////////////////////////////////////////
    //
    //  Dictクラス
    //
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    //  public
    ///////////////////////////////////////////////////////
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
            _key_and_value_list.append(DictItem<K_T, V_T>(key, V_T()));
        }

        return _key_and_value_list[find_id].value;
    }

    template <class K_T, class V_T>
    typename Dict<K_T, V_T>::iterator Dict<K_T, V_T>::begin()
    {
        return DictIterator<K_T, V_T>(this, 0);
    }

    template <class K_T, class V_T>
    void Dict<K_T, V_T>::clear()
    {
        _key_and_value_list.clear();
    }

    template <class K_T, class V_T>
    void Dict<K_T, V_T>::del(const K_T &key)
    {
        int del_id = _search(key);

        if (del_id > -1)
        {
            _key_and_value_list.del(del_id);
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
    typename Dict<K_T, V_T>::iterator Dict<K_T, V_T>::end()
    {
        return DictIterator<K_T, V_T>(this, this->getSize());
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

        value = _key_and_value_list[find_id].value;
        return 0;
    }

    template <class K_T, class V_T>
    List<K_T> Dict<K_T, V_T>::getKeys() const
    {
        List<K_T> ret;
        for (int i = 0; i < _key_and_value_list.getSize(); i++)
        {
            ret.append(_key_and_value_list.get(i).key);
        }
        return ret;
    }

    template <class K_T, class V_T>
    int Dict<K_T, V_T>::getSize() const
    {
        return _key_and_value_list.getSize();
    }

    template <class K_T, class V_T>
    const char *Dict<K_T, V_T>::getType() const
    {
        return "Dict";
    }

    template <class K_T, class V_T>
    List<V_T> Dict<K_T, V_T>::getValues() const
    {
        List<V_T> ret;
        for (int i = 0; i < _key_and_value_list.getSize(); i++)
        {
            ret.append(_key_and_value_list.get(i).value);
        }
        return ret;
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
            _key_and_value_list.append(DictItem<K_T, V_T>(key, value));
        }
        else
        {
            _key_and_value_list[add_id].value = value;
        }
    }

    ///////////////////////////////////////////////////////
    //  private
    ///////////////////////////////////////////////////////
    template <class K_T, class V_T>
    int Dict<K_T, V_T>::_search(const K_T &key)
    {
        int find_id = -1;
        for (int i = 0; i < _key_and_value_list.getSize(); i++)
        {
            if (_key_and_value_list[i].key == key)
            {
                find_id = i;
                break;
            }
        }
        return find_id;
    }

    ///////////////////////////////////////////////////////
    //
    //  DictIteratorクラス
    //
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    //  public
    ///////////////////////////////////////////////////////
    template <class K_T, class V_T>
    DictIterator<K_T, V_T>::DictIterator(const DictIterator<K_T, V_T> &other)
    {
        this->dict = other.dict;
        this->dict_list_id = other.dict_list_id;
    }

    template <class K_T, class V_T>
    DictItem<K_T, V_T> &DictIterator<K_T, V_T>::operator*()
    {
        if (dict_list_id < dict->getSize())
        {
            return *(dict->_key_and_value_list.at(dict_list_id));
        }
        return *(dict->_key_and_value_list.at(0));
    }

    template <class K_T, class V_T>
    DictIterator<K_T, V_T> &DictIterator<K_T, V_T>::operator++()
    {
        dict_list_id++;

        if (dict_list_id > dict->getSize())
        {
            dict_list_id = dict->getSize();
        }

        return *this;
    }

    template <class K_T, class V_T>
    DictIterator<K_T, V_T> DictIterator<K_T, V_T>::operator++(int)
    {
        DictIterator<K_T, V_T> iter = *this;

        dict_list_id++;

        if (dict_list_id > dict->getSize())
        {
            dict_list_id = dict->getSize();
        }

        return iter;
    }

    template <class K_T, class V_T>
    bool DictIterator<K_T, V_T>::operator==(const DictIterator<K_T, V_T> &other)
    {
        if (dict_list_id == other.dict_list_id)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <class K_T, class V_T>
    bool DictIterator<K_T, V_T>::operator!=(const DictIterator<K_T, V_T> &other)
    {
        return !(*this == other);
    }

    ///////////////////////////////////////////////////////
    //  private
    ///////////////////////////////////////////////////////
    template <class K_T, class V_T>
    DictIterator<K_T, V_T>::DictIterator(Dict<K_T, V_T> *dict_, int list_id)
    {
        dict = dict_;
        dict_list_id = list_id;
    }
}

#endif