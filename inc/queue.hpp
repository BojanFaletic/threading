#pragma once
#include <cstdint>
#include <mutex>

// error codes
enum QueueError
{
    QUEUE_OK = 0,
    QUEUE_FULL,
    QUEUE_EMPTY
};

template <typename T>
class Queue
{
private:
    T *data;
    size_t capacity;
    uint32_t head;
    uint32_t tail;
    size_t count;  
    std::mutex mutex;
public:
    Queue(size_t capacity = 1);
    ~Queue();

    QueueError try_push(T const &data);
    void push(T data);

    QueueError try_pop(T &data);
    T pop();

    bool is_empty();
    bool is_full();

    size_t get_count();
    size_t get_capacity();

    void clear();
    void print();
};

#include "queue.tpp"
