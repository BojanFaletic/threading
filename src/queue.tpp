#pragma once
#include <thread>
#include <iostream>
#include <cstdint>
#include <mutex>
#include "queue.hpp"

template <typename T>
Queue<T>::Queue(size_t capacity)
{
    this->capacity = capacity;
    this->data = new T[capacity];
    this->head = 0;
    this->tail = 0;
    this->count = 0;
}

template <typename T>
Queue<T>::~Queue()
{
    delete[] this->data;
}

template <typename T>
void Queue<T>::push(T data)
{
    std::unique_lock<std::mutex> lock(this->mutex);
    
    while (this->is_full())
    {
        std::this_thread::yield();
    }

    this->data[this->tail] = data;
    this->tail = (this->tail + 1) % this->capacity;
    this->count++;
}

template <typename T>
QueueError Queue<T>::try_push(T const &data)
{
    std::unique_lock<std::mutex> lock(this->mutex);

    if (this->is_full())
    {
        return QUEUE_FULL;
    }

    this->data[this->tail] = data;
    this->tail = (this->tail + 1) % this->capacity;
    this->count++;

    return QUEUE_OK;
}

template <typename T>
T Queue<T>::pop()
{
    std::unique_lock<std::mutex> lock(this->mutex);

    while (this->is_empty())
    {
        std::this_thread::yield();
    }

    T data = this->data[this->head];
    this->head = (this->head + 1) % this->capacity;
    this->count--;

    return data;
}

template <typename T>
QueueError Queue<T>::try_pop(T &data)
{
    std::unique_lock<std::mutex> lock(this->mutex);

    if (this->is_empty())
    {
        return QUEUE_EMPTY;
    }

    data = this->data[this->head];
    this->head = (this->head + 1) % this->capacity;
    this->count--;

    return QUEUE_OK;
}

template <typename T>
bool Queue<T>::is_empty()
{
    return this->count == 0;
}

template <typename T>
bool Queue<T>::is_full()
{
    return this->count == this->capacity;
}

template <typename T>
size_t Queue<T>::get_count()
{
    return this->count;
}

template <typename T>
size_t Queue<T>::get_capacity()
{
    return this->capacity;
}

template <typename T>
void Queue<T>::clear()
{
    this->head = 0;
    this->tail = 0;
    this->count = 0;
}

template <typename T>
void Queue<T>::print()
{
    for (size_t i = 0; i < this->count; i++)
    {
        std::cout << this->data[(this->head + i) % this->capacity] << " ";
    }
    std::cout << std::endl;
}