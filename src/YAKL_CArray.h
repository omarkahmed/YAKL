
#pragma once
// Included by YAKL_Array.h
// Inside the yakl namespace

template <class T, int rank, int myMem>
class Array<T,rank,myMem,styleC> : public CArrayBase<T,rank,myMem> {
public:

  typedef typename std::remove_cv<T>::type type;
  typedef          T value_type;
  typedef typename std::add_const<type>::type const_value_type;
  typedef typename std::remove_const<type>::type non_const_value_type;


  // Start off all constructors making sure the pointers are null
  YAKL_INLINE void nullify() {
    this->myData   = nullptr;
    this->refCount = nullptr;
    for (int i=0; i < rank; i++) { this->dimension[i] = 0; }
    #ifdef YAKL_DEBUG
      this->myname="Uninitialized";
    #endif
  }

  /* CONSTRUCTORS
  Always nullify before beginning so that myData == nullptr upon init.
  */
  YAKL_INLINE Array() {
    nullify();
  }
  YAKL_INLINE Array(char const * label) {
    nullify();
    #ifdef YAKL_DEBUG
      this->myname = label;
    #endif
  }
  // Owned constructors
  YAKL_INLINE Array( char const* label , index_t d1 ) : Array(label,Dims(d1)) {}
  YAKL_INLINE Array( char const* label , index_t d1 ,
                                         index_t d2 ) : Array(label,Dims(d1,d2)) {}
  YAKL_INLINE Array( char const* label , index_t d1 ,
                                         index_t d2 ,
                                         index_t d3 ) : Array(label,Dims(d1,d2,d3)) {}
  YAKL_INLINE Array( char const* label , index_t d1 ,
                                         index_t d2 ,
                                         index_t d3 ,
                                         index_t d4 ) : Array(label,Dims(d1,d2,d3,d4)) {}
  YAKL_INLINE Array( char const* label , index_t d1 ,
                                         index_t d2 ,
                                         index_t d3 ,
                                         index_t d4 ,
                                         index_t d5 ) : Array(label,Dims(d1,d2,d3,d4,d5)) {}
  YAKL_INLINE Array( char const* label , index_t d1 ,
                                         index_t d2 ,
                                         index_t d3 ,
                                         index_t d4 ,
                                         index_t d5 ,
                                         index_t d6 ) : Array(label,Dims(d1,d2,d3,d4,d5,d6)) {}
  YAKL_INLINE Array( char const* label , index_t d1 ,
                                         index_t d2 ,
                                         index_t d3 ,
                                         index_t d4 ,
                                         index_t d5 ,
                                         index_t d6 ,
                                         index_t d7 ) : Array(label,Dims(d1,d2,d3,d4,d5,d6,d7)) {}
  YAKL_INLINE Array( char const* label , index_t d1 ,
                                         index_t d2 ,
                                         index_t d3 ,
                                         index_t d4 ,
                                         index_t d5 ,
                                         index_t d6 ,
                                         index_t d7 ,
                                         index_t d8 ) : Array(label,Dims(d1,d2,d3,d4,d5,d6,d7,d8)) {}
  YAKL_INLINE Array(char const * label, Dims const dims) {
    nullify();
    #ifdef YAKL_DEBUG
      if (dims.size() != rank) yakl_throw("ERROR: Number of constructor dimensions does not match the Array rank");
      if (rank < 1 || rank > 8) yakl_throw("ERROR: Invalid rank, must be between 1 and 8");
      this->myname = label;
    #endif
    #if YAKL_CURRENTLY_ON_HOST()
      this->deallocate();
    #endif
    for (int i=0; i < rank; i++) { this->dimension[i] = dims[i]; }
    #if YAKL_CURRENTLY_ON_HOST()
      this->allocate(label);
    #endif
  }
  // Non-owned constructors
  YAKL_INLINE Array(char const *label, T *data, index_t const d1) : Array(label,data,Dims(d1)) {}
  YAKL_INLINE Array(char const *label, T *data, index_t const d1,
                                                index_t const d2) : Array(label,data,Dims(d1,d2)) {}
  YAKL_INLINE Array(char const *label, T *data, index_t const d1,
                                                index_t const d2,
                                                index_t const d3) : Array(label,data,Dims(d1,d2,d3)) {}
  YAKL_INLINE Array(char const *label, T *data, index_t const d1,
                                                index_t const d2,
                                                index_t const d3,
                                                index_t const d4) : Array(label,data,Dims(d1,d2,d3,d4)) {}
  YAKL_INLINE Array(char const *label, T *data, index_t const d1,
                                                index_t const d2,
                                                index_t const d3,
                                                index_t const d4,
                                                index_t const d5) : Array(label,data,Dims(d1,d2,d3,d4,d5)) {}
  YAKL_INLINE Array(char const *label, T *data, index_t const d1,
                                                index_t const d2,
                                                index_t const d3,
                                                index_t const d4,
                                                index_t const d5,
                                                index_t const d6) : Array(label,data,Dims(d1,d2,d3,d4,d5,d6)) {}
  YAKL_INLINE Array(char const *label, T *data, index_t const d1,
                                                index_t const d2,
                                                index_t const d3,
                                                index_t const d4,
                                                index_t const d5,
                                                index_t const d6,
                                                index_t const d7) : Array(label,data,Dims(d1,d2,d3,d4,d5,d6,d7)) {}
  YAKL_INLINE Array(char const *label, T *data, index_t const d1,
                                                index_t const d2,
                                                index_t const d3,
                                                index_t const d4,
                                                index_t const d5,
                                                index_t const d6,
                                                index_t const d7,
                                                index_t const d8) : Array(label,data,Dims(d1,d2,d3,d4,d5,d6,d7,d8)) {}
  YAKL_INLINE Array(char const *label, T *data, Dims const dims) {
    nullify();
    #ifdef YAKL_DEBUG
      if ( dims.size() < rank ) yakl_throw("ERROR: dims < rank");
      if ( rank < 1 || rank > 8 ) yakl_throw("ERROR: Invalid rank, must be between 1 and 8");
      if (data == nullptr) yakl_throw("ERROR: wrapping nullptr with a YAKL Array object");
      this->myname = label;
    #endif
    for (int i=0; i < rank; i++) { this->dimension[i] = dims[i]; }
    this->myData = data;
    this->refCount = nullptr;
  }


  /*
  COPY CONSTRUCTORS / FUNCTIONS
  This shares the pointers with another Array and increments the refCounter
  */
  YAKL_INLINE Array(Array<non_const_value_type,rank,myMem,styleC> const &rhs) {
    // constructor, so no need to deallocate
    nullify();
    copy_constructor_common(rhs);
  }
  YAKL_INLINE Array(Array<const_value_type,rank,myMem,styleC> const &rhs) {
    static_assert( std::is_const<T>::value , 
                   "ERROR: Cannot create non-const Array using const Array" );
    // constructor, so no need to deallocate
    nullify();
    copy_constructor_common(rhs);
  }


  YAKL_INLINE Array & operator=(Array<non_const_value_type,rank,myMem,styleC> const &rhs) {
    if (this == &rhs) { return *this; }
    #if YAKL_CURRENTLY_ON_HOST()
      this->deallocate();
    #endif
    copy_constructor_common(rhs);
    return *this;
  }
  YAKL_INLINE Array & operator=(Array<const_value_type,rank,myMem,styleC> const &rhs) {
    static_assert( std::is_const<T>::value , 
                   "ERROR: Cannot create non-const Array using const Array" );
    if (this == &rhs) { return *this; }
    #if YAKL_CURRENTLY_ON_HOST()
      this->deallocate();
    #endif
    copy_constructor_common(rhs);
    return *this;
  }

  template <class TLOC>
  YAKL_INLINE void copy_constructor_common(Array<TLOC,rank,myMem,styleC> const &rhs) {
    for (int i=0; i<rank; i++) {
      this->dimension[i] = rhs.dimension[i];
    }
    #ifdef YAKL_DEBUG
      this->myname = rhs.myname;
    #endif
    this->myData   = rhs.myData;
    #if YAKL_CURRENTLY_ON_HOST()
      yakl_mtx_lock();
    #endif
    this->refCount = rhs.refCount;
    if (this->refCount != nullptr) {
      #if YAKL_CURRENTLY_ON_HOST()
        (*(this->refCount))++;
      #endif
    }
    #if YAKL_CURRENTLY_ON_HOST()
      yakl_mtx_unlock();
    #endif
  }


  /*
  MOVE CONSTRUCTORS
  This steals the pointers form the rhs rather than sharing and sets rhs pointers to nullptr.
  Therefore, no need to increment refCout
  */
  YAKL_INLINE Array(Array &&rhs) {
    // constructor, so no need to deallocate
    nullify();
    for (int i=0; i<rank; i++) {
      this->dimension[i] = rhs.dimension[i];
    }
    #ifdef YAKL_DEBUG
      this->myname = rhs.myname;
    #endif
    this->myData   = rhs.myData;
    rhs.myData   = nullptr;

    this->refCount = rhs.refCount;
    rhs.refCount = nullptr;
  }


  YAKL_INLINE Array& operator=(Array &&rhs) {
    if (this == &rhs) { return *this; }
    #if YAKL_CURRENTLY_ON_HOST()
      this->deallocate();
    #endif
    for (int i=0; i<rank; i++) {
      this->dimension[i] = rhs.dimension[i];
    }
    #ifdef YAKL_DEBUG
      this->myname = rhs.myname;
    #endif
    this->myData   = rhs.myData;
    rhs.myData   = nullptr;

    this->refCount = rhs.refCount;
    rhs.refCount = nullptr;

    return *this;
  }


  /*
  DESTRUCTOR
  Decrement the refCounter, and if it's zero, deallocate and nullify.  
  */
  YAKL_INLINE ~Array() {
    #if YAKL_CURRENTLY_ON_HOST()
      this->deallocate();
    #endif
  }


  template <class TLOC, typename std::enable_if<std::is_arithmetic<TLOC>::value,bool>::type = false>
  YAKL_INLINE Array & operator=(TLOC const &rhs) {
    memset( *this , rhs );
    return *this;
  }


  template <int N> inline Array<T,N,myMem,styleC> reshape(Dims const &dims) const {
    #ifdef YAKL_DEBUG
      if (! this->initialized()) { yakl_throw("ERROR: Trying to reshape an Array that hasn't been initialized"); }
      if (dims.size() != N) { yakl_throw("ERROR: new number of reshaped array dimensions does not match the templated rank"); }
      index_t totelems = 1;
      for (int i=0; i < N; i++) {
        totelems *= dims.data[i];
      }
      if (totelems != this->totElems()) { yakl_throw("ERROR: Total reshaped array elements is not consistent with this array"); }
    #endif
    Array<T,N,myMem,styleC> ret;
    for (int i=0; i < N; i++) {
      ret.dimension[i] = dims.data[i];
    }
    #ifdef YAKL_DEBUG
      ret.myname = this->myname;
    #endif
    ret.myData = this->myData;
    yakl_mtx_lock();
    ret.refCount = this->refCount;
    if (this->refCount != nullptr) {
      (*(this->refCount))++;
    }
    yakl_mtx_unlock();
    return ret;
  }


  inline Array<T,1,myMem,styleC> collapse() const {
    #ifdef YAKL_DEBUG
      if (! this->initialized()) { yakl_throw("ERROR: Trying to collapse an Array that hasn't been initialized"); }
    #endif
    Array<T,1,myMem,styleC> ret;
    ret.dimension[0] = this->totElems();
    #ifdef YAKL_DEBUG
      ret.myname = this->myname;
    #endif
    ret.myData = this->myData;
    yakl_mtx_lock();
    ret.refCount = this->refCount;
    if (this->refCount != nullptr) {
      (*(this->refCount))++;
    }
    yakl_mtx_unlock();
    return ret;
  }

};



