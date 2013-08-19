#include <cstddef> // size_t
#include <new>
#include <iostream>
#include <list>      // For std::list
//#include <string>
//using namespace std;
/* 
	Implement customer allocator (STL type)
	To have a basic idea of Allocator design read :: http://www.sgi.com/tech/stl/alloc.html

	Whole idea of allocator is to "Make the library containers independent of the underlying memory model"

	* Allocator type 
		pool based allocator (Boost C++)
		shared memory allocator
		garbage collect memory allocator
		
	
	custom allocator have follwoing advantage:
	* can  be more efficient for specific requirement 
    * can be easily extended to add in build support of memory related checks (similar to purify or valgrind)


	STL allocator need to comply with the requirement stated in the standard
    Allocator here meets the requement laid by the c++ standard.

	None the less this allocator  will be used for my own library (which is very similar to STL)

	At the very basic An allocator class should have following basic methods:

	allocate() // Raw allocation
	deallocate() // Raw dealloacation
	construct()  // construct an element at a given location( already allocated) 
	destroy() 
	address() // return address of &x
	max_size() 
	
	Further you can make a decision that allocator is type aware or not? non type aware allocator will be simple
	and return void* just like malloc() do !

	C++ standard depict that the alloctor should be type aware.
	
	Also Till C++03 the allocator should be stateless. This restriction is relaxed in C++11.
	
	http://stackoverflow.com/questions/4110292/worst-that-can-happen-if-i-dont-obey-the-stateless-custom-allocators-dogma

	**** Check the requirement in C++ standard or wikipedia to know more about it. **** 

*/
template <typename T>
class myallocator{
public:
  typedef T value_type;
  typedef T* pointer;
  typedef  T const* const_pointer;
  typedef T& reference;
  typedef  T const  &  const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference;
  /* allocate/deallocate Raw memory */
  pointer allocate(size_type n);
  void deallocate(pointer p, size_type n);

  size_type max_size(){ return size_type(-1)/sizeof(T);	} // 
  pointer address(T& v) const { return &v;} //  we pass it as referece. save copying!!
  const T * address(const T& v) const { return &v;}


  /* construct or destroy object in already created memory */
  void construct(pointer p, const_reference t);
  void destroy(pointer p);
  template <typename U> struct rebind { /* list and other container use this to get different myallocator type from given myallocator type*/
        typedef myallocator<U> other;
   };

  myallocator() { } /* default constructor */
 
  myallocator(const myallocator&) { }  /* copy consturctor */
 
  template <typename U> myallocator(const myallocator<U>&) { std::cout <<"constructor conversion"; } /* constructor from conversion of other type to exiting type */
 
  ~myallocator() { } /* destructor */

};

/* See how elaborative is c++ constructs below if you define the member function definition outside the class */


/* Returns raw memory without calling constructor , hint is ignored for now. Throws exception if can't allocate */
template <typename T> 
typename /*needed because myallocator<T> is dependent scope  */ 
myallocator<T>::pointer myallocator<T>::allocate(myallocator<T>::size_type n){
  return static_cast<myallocator<T>::pointer>(operator new(n * sizeof(T)));	// operator new gives raw memory back 
}

template <typename T>
void myallocator<T>::deallocate(myallocator<T>::pointer p, myallocator<T>::size_type n){
  ::operator delete(p);
}

template <typename T>
void myallocator<T>::construct(myallocator<T>::pointer p, myallocator<T>::const_reference t){
 void * const pv = static_cast<void *>(p);
 new(pv) T(t); // T(t) will call the copy constructor
}
template <typename T>
 void myallocator<T>::destroy(myallocator<T>::pointer p){
  p->~T();
}
class myclass{
public:
  myclass(char *p){
	std::cout<< "ctor" << std::endl;
  }
  myclass(){
  }
  ~myclass(){
	std::cout<< "destructor" << std::endl;
  }
  myclass(const myclass &k){
	std::cout<< "copy ctor" << std::endl;
  }
};
/* non member == and =! operator */
/* http://stackoverflow.com/questions/4622330/operator-overloading-member-function-vs-non-member-function */

template< class T1, class T2 >
bool operator==( const myallocator<T1>& lhs, const myallocator<T2>& rhs ){ return true; }
template< class T1, class T2 >
bool operator!=( const myallocator<T1>& lhs, const myallocator<T2>& rhs ){ return false; }

main(){
  myallocator<int> a;
  myallocator<int>::pointer p =  a.allocate(10);
  a.construct(p,10);
  std::cout<< *p <<std::endl;
  
  myallocator<myclass> sa;
  myallocator<myclass>::pointer strp = sa.allocate(1);
  sa.construct(strp,static_cast<char *>("mystring"));

  using namespace std;
  cout << "Constructing l:" << endl;
  list<int, myallocator<int> > l;
  cout << endl << "l.push_back(1729):" << endl;
 
  l.push_back(1729);
  cout << endl << "l.push_back(2161):" << endl;
  l.push_back(2161);
  cout << endl;
  for (list<int, myallocator<int> >::const_iterator i = l.begin(); i != l.end(); ++i) {
	cout << "Element: " << *i << endl;
  }
	
}
