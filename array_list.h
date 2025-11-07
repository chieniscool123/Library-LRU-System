/*
 * DO NOT MAKE ANY CHANGES
 */

#pragma once

#include "util.h"

template<class T>
class List {
public:
    // return the capacity of the list
    virtual size_t capacity() const = 0;

    // return the number of elements in the list
    virtual size_t size() const = 0;

    // inserts an element to the beginning
    virtual void push_front(const T &value) = 0;

    // adds an element to the end
    virtual void push_back(const T &value) = 0;

    // removes the last element
    virtual void pop_back() = 0;

    // removes the first element
    virtual void pop_front() = 0;

    // add an element to the end of the list
    virtual void remove(T &val) = 0;

    // merges two sorted lists
    virtual void merge(const List<T> &other) = 0;

    virtual ~List() {}
};

template<class T>
class ArrayList : public List<T> {
private:
    T *data;
    size_t max_capacity;
    size_t num_of_element;

public:
    ArrayList() = delete;   // disable default constructor

    // constructor
    ArrayList(size_t capacity) : max_capacity(capacity), num_of_element(0) {
        data = new T[capacity];
    }

    // copy constructor
    ArrayList(const ArrayList<T> &other_list) : max_capacity(other_list.max_capacity),
                                                num_of_element(other_list.num_of_element) {
        data = new T[max_capacity];
        for (size_t i = 0; i < other_list.num_of_element; i++) {
            data[i] = other_list.data[i];
        }
    }

    // destructor
    virtual ~ArrayList() {
        delete[]data;
    }

    size_t capacity() const override {
        return max_capacity;
    }

    size_t size() const override {
        return num_of_element;
    }

    T &operator[](int index) {
        return data[index];
    }

    bool operator==(const ArrayList<T> &other_list) {
        // not comparing capacity as eventually array list can be made capacity irrelevant using dynamic allocation
        if (num_of_element != other_list.num_of_element) {
            return false;
        }
        for (int i = 0; i < num_of_element; i++) {
            if (data[i] != other_list.data[i]) {
                return false;
            }
        }
        return true;
    }

    void push_front(const T &value) override;

    void push_back(const T &value) override;

    void pop_back() override;

    void pop_front() override;

    void remove(T &val) override;

    void merge(const List<T> &other) override;

private:
    void shift_left_to(size_t start) {
        for (size_t i = start; i < num_of_element - 1; i++) {
            data[i] = data[i + 1];
        }
    }
};

template<class T>
void ArrayList<T>::push_front(const T &value) {
    if (num_of_element == max_capacity) {
        return;
    }

    // memcpy(data, data + 1, num_of_element * sizeof(T));  // why won't this work?
    for (size_t i = 0; i < num_of_element; i++) {
        data[num_of_element - i] = data[num_of_element - i - 1];
    }
    data[0] = value;
    num_of_element++;
}

template<class T>
void ArrayList<T>::push_back(const T &value) {
    if (num_of_element == max_capacity) {
        return;
    }
    data[num_of_element++] = value;
}

template<class T>
void ArrayList<T>::pop_back() {
    if (num_of_element == 0) {
        return;
    }
    num_of_element--;
}

template<class T>
void ArrayList<T>::pop_front() {
    if (num_of_element == 0) {
        return;
    }

    /*
     * solution 1
     */
    shift_left_to(0);
    num_of_element--;

    /*
     * solution 2: will this work?
     */
    //memcpy(data, data + 1, (-num_of_element) * sizeof(T));
}

template<class T>
void ArrayList<T>::remove(T &val) {
    for (size_t i = 0; i < num_of_element;) {
        if (data[i] == val) {
            shift_left_to(i);
            num_of_element--;
        } else {
            i++;
        }
    }
}

/*
 * merge in ascending order
 */
template<class T>
void ArrayList<T>::merge(const List<T> &ot) {
    auto &other_list = (ArrayList<T> &) ot;

    if (other_list.num_of_element == 0) {
        return;
    }

    size_t new_size = num_of_element + other_list.num_of_element;
    size_t new_capacity = max_capacity + other_list.max_capacity; // capacity doesn't affect tests

    T *new_buffer = new T[new_capacity];

    if (num_of_element == 0) {
        for (size_t i = 0; i < other_list.num_of_element; i++) {
            new_buffer[i] = other_list.data[i];
        }

        delete[] data;
        data = new_buffer;
        num_of_element = new_size;
        max_capacity = new_capacity;
        return;
    }

    size_t p1 = 0, p2 = 0;
    for (size_t i = 0; i < new_size; i++) {
        if (p1 == num_of_element) {
            new_buffer[i] = other_list[p2];
            p2++;
        } else if (p2 == other_list.num_of_element) {
            new_buffer[i] = data[p1];
            p1++;
        } else {
            if (data[p1] < other_list.data[p2]) {
                new_buffer[i] = data[p1];
                p1++;
            } else {
                new_buffer[i] = other_list.data[p2];
                p2++;
            }
        }
    }

    delete[] data;
    data = new_buffer;
    num_of_element = new_size;
    max_capacity = new_capacity;
}
