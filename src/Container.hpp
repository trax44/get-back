#ifndef TX_CONTAINER_HPP_
#define TX_CONTAINER_HPP_


namespace TX {

template <typename T>
class Container {
private:
  typedef typename std::set<T>::iterator        iterator;
  typedef typename std::set<T>::const_iterator  const_iterator;
  

  typedef typename std::set<T>::value_type      value_type;
  typedef typename std::set<T>::size_type       size_type;

public:
  
  
  virtual iterator begin  () = 0;
  virtual iterator end    () = 0;
  virtual void     insert (const value_type &val) = 0;
  

  virtual ~Container();
};

} //TX


#endif /* _CONTAINER_HPP_ */
