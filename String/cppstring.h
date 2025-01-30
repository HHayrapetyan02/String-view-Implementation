#ifndef STRING
#define STRING
#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
  size_t size_;
  size_t capacity_;
  char* arr_;

 public:
  String();
  String(const size_t&, const char&);
  String(const char*);  // NOLINT
  String(const char*, const size_t&);
  ~String();
  String(const String&);
  String& operator=(const String&);
  const char& operator[](const size_t&) const;
  char& operator[](const size_t&);
  const char& At(const size_t&) const;
  char& At(const size_t&);
  const char& Front() const;
  char& Front();
  const char& Back() const;
  char& Back();
  const char* CStr() const;
  char* CStr();
  const char* Data() const;
  char* Data();
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  void PushBack(const char&);
  String& operator+=(const String&);
  void Resize(const size_t&, const char&);
  void Reserve(const size_t&);
  void ShrinkToFit();
  friend String operator+(const String&, const String&);
  friend bool operator<(const String&, const String&);
  friend bool operator>(const String&, const String&);
  friend bool operator<=(const String&, const String&);
  friend bool operator>=(const String&, const String&);
  friend bool operator==(const String&, const String&);
  friend bool operator!=(const String&, const String&);
  friend std::ostream& operator<<(std::ostream&, const String&);
};

#endif
