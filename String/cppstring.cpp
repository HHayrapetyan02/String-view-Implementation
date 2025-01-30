#include "cppstring.h"
#include <iostream>
#include <stdexcept>

String::String() : size_(0), capacity_(0), arr_(nullptr) {
}

String::String(const size_t& size, const char& symbol) : size_(size), capacity_(size) {
  if (size_ == 0) {
    arr_ = nullptr;
  } else {
    arr_ = new char[size_ + 1]{};
    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = symbol;
    }
    arr_[size_] = '\0';
  }
}

String::String(const char* string) {
  size_t temp = 0;
  while (string[temp] != '\0') {
    ++temp;
  }
  size_ = temp;
  capacity_ = temp;
  if (size_ == 0) {
    arr_ = nullptr;
  } else {
    arr_ = new char[size_ + 1]{};
    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = string[i];
    }
    arr_[size_] = '\0';
  }
}

String::String(const char* string, const size_t& size) : size_(size), capacity_(size) {
  if (size == 0) {
    arr_ = nullptr;
  } else {
    arr_ = new char[size_ + 1]{};
    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = string[i];
    }
    arr_[size_] = '\0';
  }
}

String::~String() {
  size_ = 0;
  capacity_ = 0;
  delete[] arr_;
}

String::String(const String& string) {
  size_ = string.size_;
  capacity_ = string.capacity_;
  if (size_ == 0) {
    arr_ = nullptr;
  } else {
    arr_ = new char[size_ + 1]{};
    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = string[i];
    }
    arr_[size_] = '\0';
  }
}

String& String::operator=(const String& string) {
  if (this == &string) {
    return *this;
  }
  delete[] arr_;
  size_ = string.size_;
  capacity_ = string.capacity_;
  if (size_ == 0) {
    arr_ = nullptr;
  } else {
    arr_ = new char[size_ + 1]{};
    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = string[i];
    }
    arr_[size_] = '\0';
  }
  return *this;
}

const char& String::operator[](const size_t& ind) const {
  return arr_[ind];
}

char& String::operator[](const size_t& ind) {
  return arr_[ind];
}

const char& String::At(const size_t& ind) const {
  if (ind < size_) {
    return arr_[ind];
  }
  throw StringOutOfRange{};
}

char& String::At(const size_t& ind) {
  if (ind < size_) {
    return arr_[ind];
  }
  throw StringOutOfRange{};
}

const char& String::Front() const {
  return arr_[0];
}

char& String::Front() {
  return arr_[0];
}

const char& String::Back() const {
  return arr_[size_ - 1];
}

char& String::Back() {
  return arr_[size_ - 1];
}

const char* String::CStr() const {
  return arr_;
}

char* String::CStr() {
  return arr_;
}

const char* String::Data() const {
  return arr_;
}

char* String::Data() {
  return arr_;
}

bool String::Empty() const {
  return size_ == 0;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  size_ = 0;
  if (arr_ != nullptr) {
    arr_[0] = '\0';
  }
}

void String::Swap(String& string) {
  std::swap(size_, string.size_);
  std::swap(capacity_, string.capacity_);
  std::swap(arr_, string.arr_);
}

void String::PopBack() {
  arr_[size_ - 1] = '\0';
  --size_;
}

void String::PushBack(const char& symbol) {
  if (size_ == capacity_) {
    capacity_ == 0 ? capacity_ += 1 : capacity_ *= 2;
    auto temp = arr_;
    arr_ = new char[capacity_ + 1]{};
    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = temp[i];
    }
    delete[] temp;
  }
  arr_[size_] = symbol;
  ++size_;
  arr_[size_] = '\0';
}

String& String::operator+=(const String& string) {
  for (size_t i = 0; i < string.size_; ++i) {
    PushBack(string.arr_[i]);
  }
  return *this;
}

void String::Resize(const size_t& size, const char& symbol) {
  if (size > capacity_) {
    capacity_ = size;
    auto temp = arr_;
    arr_ = new char[capacity_ + 1]{};
    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = temp[i];
    }
    delete[] temp;
  }
  for (size_t i = size_; i < size; ++i) {
    arr_[i] = symbol;
  }
  size_ = size;
  arr_[size_] = '\0';
}

void String::Reserve(const size_t& capacity) {
  if (capacity > capacity_) {
    capacity_ = capacity;
    auto temp = arr_;
    arr_ = new char[capacity_ + 1]{};
    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = temp[i];
    }
    arr_[size_] = '\0';
    delete[] temp;
  }
}

void String::ShrinkToFit() {
  capacity_ = size_;
  auto temp = arr_;
  arr_ = new char[capacity_ + 1]{};
  for (size_t i = 0; i < size_; ++i) {
    arr_[i] = temp[i];
  }
  arr_[size_] = '\0';
  delete[] temp;
}

String operator+(const String& first, const String& second) {
  String str = first;
  str += second;
  return str;
}

bool operator<(const String& first, const String& second) {
  size_t min = std::min(first.size_, second.size_);
  for (size_t i = 0; i < min; ++i) {
    if (first.arr_[i] != second.arr_[i]) {
      return first.arr_[i] < second.arr_[i];
    }
  }
  return first.size_ < second.size_;
}

bool operator>(const String& first, const String& second) {
  size_t min = std::min(first.size_, second.size_);
  for (size_t i = 0; i < min; ++i) {
    if (first.arr_[i] != second.arr_[i]) {
      return first.arr_[i] > second.arr_[i];
    }
  }
  return first.size_ > second.size_;
}

bool operator==(const String& first, const String& second) {
  if (first.size_ == second.size_) {
    for (size_t i = 0; i < first.size_; ++i) {
      if (first.arr_[i] != second.arr_[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool operator<=(const String& first, const String& second) {
  return first == second || first < second;
}

bool operator>=(const String& first, const String& second) {
  return first == second || first > second;
}

bool operator!=(const String& first, const String& second) {
  return !(first == second);
}

std::ostream& operator<<(std::ostream& os, const String& string) {
  for (size_t i = 0; i < string.size_; ++i) {
    os << string.arr_[i];
  }
  return os;
}
