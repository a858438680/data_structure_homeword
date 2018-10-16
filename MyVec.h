#include <initializer_list>
#include <limits>
#include <utility>
#include <cstddef>

namespace alan{
template <class T>
class vector {
    template <typename U> friend void swap(vector<U>&, vector<U>&) noexcept;
public:
    // 类型：
    typedef T                                                   value_type;
    typedef value_type&                                         reference;
    typedef const value_type&                                   const_reference;
    typedef value_type*                                         iterator;
    typedef const value_type*                                   const_iterator; 
    typedef size_t                                              size_type;
    typedef size_t                                              difference_type;
 
    // 构造/复制/销毁：
    vector() noexcept;
    explicit vector(size_type n);
    vector(size_type n, const_reference value);
    template <class InputIterator>
        vector(InputIterator first, InputIterator last);
    vector(const vector<T>& x);
    vector(vector<T>&&);
    vector(std::initializer_list<T>);
 
    ~vector();
    vector<T>& operator=(vector<T> rhs);
    vector<T>& operator=(std::initializer_list<T>);
 
    // 迭代器：
    iterator                begin() noexcept;
    const_iterator          begin() const noexcept;
    iterator                end() noexcept;
    const_iterator          end() const noexcept;
 
    const_iterator          cbegin() noexcept;
    const_iterator          cend() noexcept;
 
    // 容量：
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    size_type capacity() const noexcept;
    bool      empty() const noexcept;
    void      reserve(size_type n);
 
    // 元素访问：
    reference       operator[](size_type n);
    const_reference operator[](size_type n) const;
 
    // 修改器：
    template <class... Args> void emplace_back(Args&&... args);
    void push_back(const T& x);
    void push_back(T&& x);
    void pop_back();
 
    template <class... Args> iterator emplace(iterator position, Args&&... args);
    iterator insert(iterator position, const T& x);
    iterator insert(iterator position, T&& x);
    iterator insert(iterator position, size_type n, const T& x);
 
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    void     clear() noexcept;
private:
    iterator elements;
    iterator first_free;
    iterator cap;
    void free();
    void reallocate();
    void chk_n_alloc();
    iterator move_forward(iterator pos, size_type n);
    iterator move_back(iterator first, iterator last);
};

template <class T>
inline void swap(vector<T>& lhs, vector<T>& rhs) noexcept
{
    using std::swap;
    swap(lhs.elements, rhs.elements);
    swap(lhs.first_free, rhs.first_free);
    swap(lhs.cap, rhs.cap);
}

template <class T>
vector<T>::vector() noexcept : elements(nullptr), first_free(nullptr), cap(nullptr) {}

template <class T>
vector<T>::vector(size_type n) : elements(new T[n]), first_free(elements+n), cap(elements+n) {}

template <class T>
vector<T>::vector(size_type n, const_reference value) :
elements(static_cast<iterator>(operator new[](sizeof(value_type)*n))), 
first_free(elements+n),
cap(elements+n)
{
    for (auto first = elements; first != first_free; ++first)
    {
        new (first) value_type (value);
    }
}

template <class T>
template <class InputIterator> vector<T>::vector(InputIterator first, InputIterator last)
{
    size_type n = 0;
    for (auto temp = first; temp != last; ++first, ++n);
    elements = static_cast<iterator>(operator new[](sizeof(value_type)*n));
    first_free = elements + n;
    cap = elements + n;
    for (auto itr = elements; first != last; ++first, ++itr)
    {
        *itr = *first;
    }
}

template <class T>
vector<T>::vector(const vector<T>& x) :
elements(static_cast<iterator>(operator new[](sizeof(value_type)*x.size()))),
first_free(elements+x.size()),
cap(elements + x.size())
{
    auto itr = elements;
    for (auto first = x.begin(); first = x.end(); ++first, ++itr)
    {
        *itr = *first;
    }
}

template <class T>
vector<T>::vector(vector<T>&& x) :
elements(static_cast<iterator>(operator new[](sizeof(value_type)*x.size()))),
first_free(elements+x.size()),
cap(elements + x.size())
{
    auto itr = elements;
    for (auto first = x.begin(); first = x.end(); ++first, ++itr)
    {
        *itr = std::move(*first);
    }
    x.elements = nullptr;
}

template <class T>
vector<T>::vector(std::initializer_list<T> il) :
elements(static_cast<iterator>(operator new[](sizeof(value_type)*il.size()))),
first_free(elements+il.size()),
cap(elements + il.size())
{
    auto itr = elements;
    for (auto first = il.begin(); first != il.end(); ++first, ++itr)
    {
        *itr = *first;
    }
}

template <class T>
vector<T>::~vector() {
    free();
    operator delete[](elements);
}

template <class T>
vector<T>& vector<T>::operator=(vector<T> rhs)
{
    using std::swap;
    swap(*this, rhs);
    return *this;
}

template <class T>
vector<T>& vector<T>::operator=(std::initializer_list<T> il)
{
    vector<T> temp(il);
    using std::swap;
    swap(*this, temp);
    return *this;
}

template <class T>
T* vector<T>::begin() noexcept
{
    return elements;
}

template <class T>
const T* vector<T>::begin() const noexcept
{
    return elements;
}

template <class T>
T* vector<T>::end() noexcept
{
    return first_free;
}

template <class T>
const T* vector<T>::end() const noexcept
{
    return first_free;
}

template <class T>
const T* vector<T>::cbegin() noexcept
{
    return elements;
}

template <class T>
const T* vector<T>::cend() noexcept
{
    return first_free;
}

template <class T>
size_t vector<T>::size() const noexcept
{
    return first_free - elements;
}

template <class T>
size_t vector<T>::max_size() const noexcept
{
    return std::numeric_limits<size_t>::max();
}

template <class T>
size_t vector<T>::capacity() const noexcept
{
    return cap - elements;
}

template <class T>
bool vector<T>::empty() const noexcept
{
    return elements == first_free;
}

template <class T>
void vector<T>::reserve(size_type newcapacity)
{
    if (newcapacity > cap - elements)
    {
        auto newdata =  static_cast<iterator>(operator new[](sizeof(value_type)*newcapacity));
        auto dest = newdata;
        auto elem = elements;
        for (size_type i = 0; i != size(); ++i)
        {
            new (dest++) value_type(std::move(*elem++));
        }
        free();
        elements = newdata;
        first_free = dest;
        cap = elements + newcapacity;
    }
}

template <class T>
T& vector<T>::operator[](size_type pos)
{
    return *(elements + pos);
}

template <class T>
const T& vector<T>::operator[](size_type pos) const
{
    return *(elements + pos);
}

template <class T>
template <class... Args> void vector<T>::emplace_back(Args&&... args)
{
    chk_n_alloc();
    new (first_free++) value_type(std::forward<Args>(args)...);
}

template <class T>
void vector<T>::push_back(const T& x)
{
    chk_n_alloc();
    new (first_free++) value_type(x);
}

template <class T>
void vector<T>::push_back(T&& x)
{
    chk_n_alloc();
    new (first_free++) value_type(std::move(x));
}

template <class T>
void vector<T>::pop_back()
{
    (--first_free)->~T();
}

template <class T>
template <class... Args> T* vector<T>::emplace(iterator position, Args&&... args)
{
    auto new_pos = move_forward(position, 1);
    new (new_pos) value_type(std::forward<Args>(args)...);
    ++first_free;
    return new_pos;
}

template <class T>
T* vector<T>::insert(iterator position, const T& x)
{
    auto new_pos = move_forward(position, 1);
    new (new_pos) value_type(x);
    ++first_free;
    return new_pos;
}

template <class T>
T* vector<T>::insert(iterator position, T&& x)
{
    auto new_pos = move_forward(position, 1);
    new (new_pos) value_type(std::move(x));
    ++first_free;
    return new_pos;
}

template <class T>
T* vector<T>::erase(iterator position)
{
    move_back(position, position + 1);
    --first_free;
    return position;
}

template <class T>
T* vector<T>::erase(iterator first, iterator last)
{
    move_back(first, last);
    first_free -= last - first;
    return first;
}

template <class T>
void vector<T>::clear() noexcept
{
    free();
    operator delete[](elements);
    elements = first_free = cap = nullptr;
}

template <class T>
void vector<T>::free()
{
    for (auto itr = elements; itr != first_free; ++itr)
    {
        itr->~T();
    }
}

template <class T>
void vector<T>::reallocate()
{
    auto newcapacity = size() ? 2*size() : 1;
    reserve(newcapacity);
}

template <class T>
void vector<T>::chk_n_alloc()
{
    if (size() == capacity())
    {
        reallocate();
    }
}

template <class T>
T* vector<T>::move_forward(iterator pos, size_type n)
{
    auto index = pos - elements;
    reserve(size() + n);
    for (auto itr = first_free-1; itr != elements+index-1; --itr)
    {
        *(itr+n) = *itr;
    }
    for (auto itr = elements + index; itr != elements + index + n; ++itr)
    {
        itr->~T();
    }
    return elements + index;
}

template <class T>
T* vector<T>::move_back(iterator first, iterator last)
{
    auto n = last - first;
    for (; last != first_free; ++last)
    {
        *(last-n) = *last;
    }
    for (auto itr = first_free - n; itr != first_free; ++itr)
    {
        itr->~T();
    }
    return first;
}
}