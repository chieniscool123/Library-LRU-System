/* Alogrithm to live by
 * They make the system faster by keeping relevant piece of information around instead of puttting them back. This is known as caching
 * Cache eviction : LRU is the most optimal way to finding out what information to keep
 * You can also use the LRU in the office setting by moving the LRU piece of paper to the right of the box
 * Rethinking rationaily : Upon a intractable problem, the best strategy is to trade off the labor of computation vs the result
 * Trade of the cost of labors against the cost of delays
 * relax the constraints
 *
 *
 *
 *
 */


#pragma once

#include "array_map.h"
#include "util.h"

template<typename T>
class LRUCache;

template<typename T>
class ListNode {
private:
    std::string key;
    T value;
    ListNode<T> *next;

public:
    ListNode() : next(nullptr) {
    }

    ListNode(const std::string &key, const T &value) : key(key), value(value), next(nullptr) {
    }

    friend class LRUCache<T>;
};

template<typename T>
class LRUCache {
private:
    int capacity;

    int num_of_entry;

    ArrayMap<std::string, ListNode<T> *> *map;

    ListNode<T> head; // dummy head node

public:
    explicit LRUCache(int capacity) : capacity(capacity), num_of_entry(0) {
        // store pointers to nodes in the linked list. It maps each key to a corresponding node in the doubly linked list.
        // This allows for O(1) average-time complexity for both insertion and lookup operations, which is crucial for efficient caching.
        map = new ArrayMap<std::string, ListNode<T> *>(capacity);
    }

    int get_capacity() {
        return capacity;
    }

    bool get(const std::string &key, T &value);

    bool remove(const std::string &key);

    bool put(const std::string &key, const T &value, T &evicted_value);

    virtual ~LRUCache() {
        ListNode<T> *current = head.next;
        while (current != nullptr) {
            ListNode<T> *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        num_of_entry = 0;
        delete map;
    }
};

/*
 * removes the item with the given name as the key
 */
template<typename T>
bool LRUCache<T>::remove(const std::string &key) {
    ListNode<T> *node = nullptr;
    if (!map->get(key, node)) {
        return false; // Key not found
    }

    ListNode<T> *prev = &head;
    ListNode<T> *current = head.next;

    while (current != node && current != nullptr) {
        prev = current;

        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }

    prev->next = current->next;
    delete current;

    map->remove(key);
    num_of_entry--;


    return true;
}

template<typename T>
bool LRUCache<T>::put(const std::string &key, const T &value, T &evicted_value) {
    // Case 1 : key alreayd exist
    ListNode<T> *node = nullptr;

    if (map->get(key, node)) {
        // check to see if key exist and set point node to the corresponding node
        ListNode<T> *current = head.next;
        ListNode<T> *prev = &head;


        // First node
        if (node == head.next) {
            node->value = value;
        }

        node->value = value; // set the node value


        while (current != nullptr && current != node) {
            // move through the linkedlist
            prev = current;
            current = current->next;
        }

        prev->next = current->next; // setting pre to 'nullptr'
        current->next = head.next; // move current node to the left of the linkedlist
        head.next = current;

        return false;
    }
    //Case 2: Key don't exist and the cache is at max_capacity


    node = new ListNode<T>(key, value);

    if (num_of_entry == capacity) {
        ListNode<T> *prev = &head;
        ListNode<T> *current = head.next;

        while (current->next != nullptr) {
            // move down the linkedlist
            prev = current;
            current = current->next;
        }

        prev->next = nullptr; // setting second to last node to the nullptr
        evicted_value = current->value;

        map->remove(current->key);
        delete current;

        num_of_entry--;

        node->next = head.next;
        head.next = node;
        map->put(key, node);
        num_of_entry++;

        return true;
    }

    // Insert the new node at the front  of the linked list
    node->next = head.next;
    head.next = node;
    map->put(key, node);
    num_of_entry++;

    return false;
}

/*
 * get finds and return the item based on name
 */
template<typename T>


bool LRUCache<T>::get(const std::string &key, T &result) {
    ListNode<T> *current = head.next;

    while (current != nullptr) {
        if (current->key == key) {
            result = current->value;
            return true;
        } else {
            current = current->next;
        }
    }
    return false;
}

