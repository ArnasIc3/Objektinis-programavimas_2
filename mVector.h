#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <utility>

template <class T>
class mVector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

public:
    // Member types
    using value_type = T;
    using allocator_type = std::allocator<T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Default constructor
    mVector() : data_(nullptr), size_(0), capacity_(0) {}

    // Destructor
    ~mVector() {
        delete[] data_;
    }

    // Copy constructor
    mVector(const mVector& other) : data_(nullptr), size_(0), capacity_(0) {
        reserve(other.size_);
        size_ = other.size_;
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    // Copy assignment operator
    mVector& operator=(const mVector& other) {
        if (this != &other) {
            T* new_data = new T[other.capacity_];
            std::copy(other.data_, other.data_ + other.size_, new_data);
            delete[] data_;
            data_ = new_data;
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    // Move constructor
    mVector(mVector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Move assignment operator
    mVector& operator=(mVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Constructor that takes an initializer list
    mVector(std::initializer_list<T> init) : size_(init.size()), capacity_(init.size()), data_(new T[init.size()]) {
        std::copy(init.begin(), init.end(), data_);
    }

    // Constructor that takes a size and an initial value
    mVector(size_t size, const T& value) : size_(size), capacity_(size), data_(new T[size]) {
        std::fill(data_, data_ + size, value);
    }

    // Return allocator
    allocator_type get_allocator() const noexcept {
        return allocator_type();
    }

    // Iterators
    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    const_iterator cbegin() const { return data_; }
    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }
    const_iterator cend() const { return data_ + size_; }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    // Capacity
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    size_t max_size() const { return std::allocator_traits<allocator_type>::max_size(get_allocator()); }

    // Resize the vector
    void resize(size_t new_size) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        if (new_size > size_) {
            std::fill(data_ + size_, data_ + new_size, T());
        }
        size_ = new_size;
    }

    // Reserve capacity
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* new_data = new T[new_capacity];
            std::move(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }

    void shrink_to_fit() {
        if (capacity_ > size_) {
            T* new_data = new T[size_];
            std::move(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = size_;
        }
    }

    // Element access
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("mVector::at - index out of range");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("mVector::at - index out of range");
        }
        return data_[index];
    }

    T& front() {
        if (size_ == 0) {
            throw std::out_of_range("mVector::front - vector is empty");
        }
        return data_[0];
    }

    const T& front() const {
        if (size_ == 0) {
            throw std::out_of_range("mVector::front - vector is empty");
        }
        return data_[0];
    }

    T& back() {
        if (size_ == 0) {
            throw std::out_of_range("mVector::back - vector is empty");
        }
        return data_[size_ - 1];
    }

    const T& back() const {
        if (size_ == 0) {
            throw std::out_of_range("mVector::back - vector is empty");
        }
        return data_[size_ - 1];
    }

    T* data() noexcept { return data_; }
    const T* data() const noexcept { return data_; }

    // Modifiers
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("mVector is empty");
        }
        --size_;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = std::move(value);
    }

    template <typename T1, typename T2>
    void emplace_back(T1&& arg1, T2&& arg2) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = T(std::forward<T1>(arg1), std::forward<T2>(arg2));
    }

    void insert(size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("mVector::insert - index out of range");
        }
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        std::move_backward(data_ + index, data_ + size_, data_ + size_ + 1);
        data_[index] = value;
        ++size_;
    }

    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("mVector::erase - index out of range");
        }
        std::move(data_ + index + 1, data_ + size_, data_ + index);
        --size_;
    }

    void swap(mVector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void clear() {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    void assign(size_t count, const T& value) {
        clear();
        reserve(count);
        for (size_t i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    // Comparison operators
    bool operator==(const mVector& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const mVector& other) const {
        return !(*this == other);
    }
};