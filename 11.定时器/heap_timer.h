// 代码清单11-6 时间堆
#pragma once

#include <iostream>
#include <time.h>
#include <netinet/in.h>
#include <stdio.h>
using std::exception;

#define BUFFER_SIZE 64

class heap_timer;

struct client_data
{
    sockaddr_in address;    // 客户端sock地址
    int sockfd;
    char buf[BUFFER_SIZE];  // 读缓存
    heap_timer* timer;      // 定时器
};

class heap_timer
{
public:
    heap_timer(int delay)
    {
        expire = time(NULL) + delay;
    }
public:
    time_t expire;     // 定时器生效的绝对时间
    void (*cb_func)(client_data*);  // 定时器的回调函数
    client_data* user_data; // 用户数据
};

// 时间堆
class time_heap
{
public:
    time_heap(int cap) : capacity(cap), cur_size(0)
    {
        array = new heap_timer*[capacity];
        if (!array)
        {
            throw std::bad_alloc();
        }
        for (int i = 0; i < capacity; i++)
        {
            array[i] = NULL;
        }
    }

    time_heap(heap_timer** init_array, int size, int capacity)
        : cur_size(size), capacity(capacity)
    {
        if (capacity < size)
        {
            throw std::invalid_argument("heap capacity is less than init size");
        }

        array = new heap_timer*[capacity];
        if (!array)
        {
            throw std::bad_alloc();
        }

        for (int i = 0; i < capacity; i++)
        {
            array[i] = NULL;
        }

        if (size != 0)
        {
            for (int i = 0; i < size; ++i)
            {
                array[i] = init_array[i];
            }
            for (int i = (cur_size-1)/2; i >= 0; --i)
            {
                // 对数组中的第[(cur_size-1)/2]~0个元素执行下滤操作
                percolate_down(i);
            }
        }
    }
private:
    // 最小堆的下滤操作，它确保堆数组中以第hole个节点作为根的子树拥有最小堆性质
    void percolate_down(int hole)
    {
        heap_timer* temp = array[hole];
        int child = 0;
        for(; hole*2+1 <= cur_size-1; hole=child)
        {
            child = hole*2+1;
            if ((child < cur_size -1) && (array[child+1]->expire < array[child]->expire))
            {
                ++child;
            }

            if (array[child]->expire < temp->expire)
            {
                
            }
        }
    }

private:
    heap_timer** array;     // 堆数组
    int capacity;           // 堆数组的容量
    int cur_size;           // 堆数组当前包含元素的个数
};