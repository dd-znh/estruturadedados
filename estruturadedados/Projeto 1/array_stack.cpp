
namespace structures {

template<typename T>
ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[DEFAULT_SIZE];
    top_ = -1;
}

template<typename T>
ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

template<typename T>
void ArrayStack<T>::push(const T& data) {
    if (full())
        throw std::out_of_range("pilha cheia");
    top_++;
    contents[top_] = data;
}

template<typename T>
T ArrayStack<T>::pop() {
    if (empty())
        throw std::out_of_range("pilha vazia");
    T aux;
    aux = contents[top_];
    top_--;
    return aux;
}

template<typename T>
T& ArrayStack<T>::top() {
    if (empty())
        throw std::out_of_range("pilha vazia");
    return contents[top_];
}

template<typename T>
void ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
std::size_t ArrayStack<T>::size() {
    return top_ + 1;
}

template<typename T>
std::size_t ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool ArrayStack<T>::empty() {
    return (top_ == -1);
}

template<typename T>
bool ArrayStack<T>::full() {
    return size() == max_size();
}

}  // namespace structures
