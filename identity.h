#ifndef IDENTITY_H
#define IDENTITY_H

/**
 * Template for classes with ids
 */

template <typename T> class Identity {
private:
  int id;

protected:
  static int s_nextId;
  static int grabId() { return s_nextId++; }

public:
  Identity();
  virtual ~Identity() = default;
  int getId() const;
  void setId(int value);
};

template <typename T> int Identity<T>::s_nextId = 0;

template <typename T> Identity<T>::Identity() : id{grabId()} {}

template <typename T> int Identity<T>::getId() const { return id; }

template <typename T> void Identity<T>::setId(int value) { id = value; }

#endif // IDENTITY_H
