#include <cstddef> // size_t
template <typename T>
class allocator{
public:
  typedef T value_type;
  typedef T* pointer;
  typedef  T const* const_pointer;
  typedef T& reference;
  typedef  T const & const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference;
  /* allocate/deallocate Raw memory */
  pointer allocate(size_type n);
  void deallocate(pointer p, size_type n);

  size_type max_size();
  pointer address(value_type v);

  /* construct or destroy object in already created memory */
  void construct(pointer p, const_reference t);
  void destroy(pointer p);

};
/* Returns raw memory without calling constructor , hint is ignored for now. Throws exception if can't allocate */

template <typename T> 
typename allocator<T>::pointer allocator<T>::allocate(allocator<T>::size_type n){
  return static_cast<allocator<T>::pointer>(operator new(n));	
}

template <typename T>
void allocator<T>::deallocate(allocator<T>::pointer p, allocator<T>::size_type n){
  ::operator delete(p);
}

template <typename T>
typename allocator<T>::pointer allocator<T>::address(allocator<T>::value_type v){
  return &v;
}

template <typename T>
void allocator<T>::construct(allocator<T>::pointer p, allocator<T>::const_reference t){
  new(p) T(t);
}
template <typename T>
void allocator<T>::destroy(allocator<T>::pointer p){
  p->~T();
}

main(){
  allocator<int> a;
  allocator<int>::pointer p =  a.allocate(10);
}
