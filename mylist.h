#pragma once



#include <iostream>
#include <algorithm>
#include <exception>
#include <errno.h>
#include <cstdio>
#include <cstring>

const int Maxsize = 200;

// algorithm used
// pointer  m_begin m_end
// Double linked list implementation

template <class _Ty>
struct snode
{
    _Ty Data;
    int next;
    int prior;
};

template <class T>
class myNodelist
{
public:
    ~myNodelist();
    explicit myNodelist(int n = Maxsize);
    myNodelist(const myNodelist &other);
    myNodelist<T> &operator=(const myNodelist &other);
    int size() const;
    bool empty() const;
    void push_back(const T &x);
    void push_front(const T &x);
    void print_list() const;
    void pop_back();
    void pop_front();
    T &back() const;
    T &front() const;
    void clear();

private:
    snode<T> *m_snode;
    int m_begin;
    int m_end;
    int m_index;

    int m_cnt;
    int m_total;
};

template <class T>
myNodelist<T>::myNodelist(int n)
{
    if (n <= 0)
    {
        n = Maxsize;
        m_total = Maxsize;
    }
    else
    {
        m_total = n;
    }
    m_begin = 0;
    m_end = 0;
    m_index = 0;
    m_cnt = 0;
    try
    {
        m_snode = new snode<T>[n + 1] {};
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << e.what() << std::endl;
    }
    for (int i = 0; i < n; i++)
    {
        m_snode[i].next = -1;
        m_snode[i].prior = -1;
    }
}

template <class T>
myNodelist<T>::~myNodelist()
{
    delete[] m_snode;
}

template <class T>
int myNodelist<T>::size() const
{
    return m_cnt;
}

template <class T>
bool myNodelist<T>::empty() const
{
    return !m_cnt;
}

template <class T>
myNodelist<T>::myNodelist(const myNodelist<T> &other)
{
    m_end = other.m_end;
    m_begin = other.m_begin;
    m_total = other.m_total;
    m_index = other.m_index;
    m_cnt = other.m_cnt;
    try
    {
        m_snode = new snode<T>[m_total + 1] {};
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << e.what() << std::endl;
    }
    for (int i = 0; i < m_total; ++i)
    {
        m_snode[i].Data = other.m_snode[i].Data;
        m_snode[i].next = other.m_snode[i].next;
        m_snode[i].prior = other.m_snode[i].prior;
    }
}

template <class T>
myNodelist<T> &myNodelist<T>::operator=(const myNodelist<T> &other)
{
    if (this == other)
        ;
    else
    {
        m_end = other.m_end;
        m_begin = other.m_begin;
        m_total = other.m_total;
        m_index = other.m_index;
        m_cnt = other.m_cnt;
        try
        {
            m_snode = new snode<T>[m_total + 1] {};
        }
        catch (std::bad_alloc &e)
        {
            std::cerr << e.what() << std::endl;
        }

        for (int i = 0; i < m_total; ++i)
        {
            m_snode[i].Data = other.m_snode[i].Data;
            m_snode[i].next = other.m_snode[i].next;
            m_snode[i].prior = other.m_snode[i].prior;
        }
    }
}

template <class T>
void myNodelist<T>::print_list() const
{
    if (!m_cnt)
        return;
    int st = m_begin;
    while (st != -1)
    {
        // if(m_snode[st].next != -1)
        std::cout << m_snode[st].Data << std::endl;
        st = m_snode[st].next;
    }
}

template <class T>
void myNodelist<T>::clear()
{
    if (!m_cnt)
        return;
    for (int i = 0; i < m_index; ++i)
    {
        m_snode[i].next = -1;
        m_snode[i].prior = -1;
    }
    m_begin = -1;
    m_end = -1;
    m_index = 0;
    m_cnt = 0;
}

template <class T>
T &myNodelist<T>::back() const
{
    if (!m_cnt)
    {
        return m_snode[m_total].Data;
    }
    return m_snode[m_end].Data;
}

template <class T>
T &myNodelist<T>::front() const
{
    if (!m_cnt)
    {
        return m_snode[m_total].Data;
    }
    return m_snode[m_begin].Data;
}

template <class T>
void myNodelist<T>::push_front(const T &x)
{
    if (m_cnt == m_total || (m_index < 0) || m_index > m_total)
        return;
    if (!m_cnt)
    { // =0
        m_snode[m_index].next = -1;
        m_snode[m_index].prior = -1;
        m_snode[m_index].Data = x;
        m_end = m_index;
        m_begin = m_index;
    }
    else
    { // >0
        m_snode[m_index].Data = x;
        m_snode[m_index].next = m_begin;
        m_snode[m_index].prior = -1;
        m_snode[m_begin].prior = m_index;
        m_begin = m_index;
    }
    ++m_index;
    ++m_cnt;
}

template <class T>
void myNodelist<T>::push_back(const T &x)
{
    if (m_cnt == m_total || (m_index < 0) || m_index > m_total)
        return;
    if (!m_cnt)
    {
        m_snode[m_index].next = -1;
        m_snode[m_index].prior = -1;
        m_snode[m_index].Data = x;
        m_end = m_index;
        m_begin = m_index;
    }
    else
    {
        m_snode[m_index].next = -1;
        m_snode[m_index].prior = m_end;
        m_snode[m_index].Data = x;
        m_snode[m_end].next = m_index;
        m_end = m_index;
    }
    ++m_cnt;
    ++m_index;
}

template <class T>
void myNodelist<T>::pop_back()
{
    if (!m_cnt)
        return;
    if (m_cnt == 1)
    {
        m_snode[m_end].next = -1;
        m_begin = 0;
        m_end = 0;
        m_cnt = 0;
        return;
    }
    m_snode[m_end].next = -1;
    int pre = m_snode[m_end].prior;
    m_snode[m_end].prior = -1;
    m_end = pre;
    m_snode[m_end].next = -1;

    --m_cnt;
}

template <class T>
void myNodelist<T>::pop_front()
{
    if (!m_cnt)
        return;
    if (m_cnt == 1)
    {
        m_snode[m_begin].next = -1;
        m_snode[m_begin].prior = -1;
        m_begin = 0;
        m_begin = 0;
        m_cnt = 0;
        return;
    }
    int t = m_begin;
    t = m_snode[t].next;
    m_snode[m_begin].next = -1;
    m_snode[t].prior = -1;
    m_begin = t;
    --m_cnt;
}
