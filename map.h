/*
 * DO NOT MAKE ANY CHANGES
 */

#pragma once

template<class KeyType, class ValueType>
class Map {
public:
    virtual bool is_empty() = 0;

    virtual int size() = 0; // number of element in the dictionary

    virtual void put(KeyType const &key, ValueType const &value) = 0;

    virtual bool remove(KeyType const &key) = 0;

    virtual bool get(KeyType const &key, ValueType &value) const = 0;

    virtual ~Map() {};
};