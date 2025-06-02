#include <iostream>
#include <utility>
#include <new>
#include <cstddef>

// ---------- Implémentation simplifiée de std::vector ----------
template <typename T>
class MyVector
{
private:
  T* data_;
  size_t size_;
  size_t capacity_;

public:
  MyVector() : data_(nullptr), size_(0), capacity_(0) {}

  ~MyVector()
  {
    clear();
    ::operator delete(data_);
  }

  /**
   * 
   * Ce que ça fait :
   *  - Si besoin, on réalloue d'abord → ce qui déplace les anciens objets.
   *  - Puis on construit value dans data_ + size_.
   * 
   * C’est plus simple à comprendre, mais 
   *  ça diffère du comportement réel de std::vector,
   *  qui préfère construire le nouvel élément d'abord 
   *  dans le nouveau bloc, avant de déplacer les anciens.
   * 
   */
  void push_back(const T& value)
  {
    if (size_ == capacity_)
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    new (data_ + size_) T(value); // placement new (copy)
    ++size_;
  }

  void push_back(T&& value)
  {
    // à chaque fois que size atteint capacity
    // on réalloue de la mémoire => 2* capacity actuel
    if (size_ == capacity_)
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    new (data_ + size_) T(std::move(value)); // placement new (move)
    ++size_;
  }

  void reserve(size_t new_cap)
  {
    if (new_cap <= capacity_) return;

    T* new_data = static_cast<T*>(::operator new(new_cap * sizeof(T)));

    // Move or copy old elements
    for (size_t i = 0; i < size_; ++i)
        new (new_data + i) T(std::move_if_noexcept(data_[i]));

    // Destroy old elements
    for (size_t i = 0; i < size_; ++i)
        data_[i].~T();

    ::operator delete(data_);
    data_ = new_data;
    capacity_ = new_cap;
  }

  T& operator[](size_t index) { return data_[index]; }
  const T& operator[](size_t index) const { return data_[index]; }

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }

  void clear()
  {
    for (size_t i = 0; i < size_; ++i)
        data_[i].~T();
    size_ = 0;
  }
};


int main()
{

  return 0;
}