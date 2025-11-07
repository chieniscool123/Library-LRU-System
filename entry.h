/*
 * DO NOT MAKE ANY CHANGES
 */

#pragma once

template<class KeyType, class ValueType>
class ArrayMap;

template<class KeyType, class ValueType>
class Entry {
    friend class ArrayMap<KeyType, ValueType>;

private:
    KeyType key;
    ValueType value;
    Entry<KeyType, ValueType> *next;


public:
    Entry() = delete;

    Entry(const KeyType &key, const ValueType &value) : key(key), value(value), next(nullptr) {}

    ValueType get_value() {
        return value;
    }

    KeyType get_key() {
        return key;
    }

    void set_value(const ValueType &newValue) {
        value = newValue;
    }

    bool operator==(const KeyType &other_entry) {
        return key == other_entry;
    }

    bool operator==(const Entry<KeyType, ValueType> &other_entry) {
        return key == other_entry.key && value == other_entry.value;
    }
};