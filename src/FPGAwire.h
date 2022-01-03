#ifndef FPGAWIRE_H
#define FPGAWIRE_H 	

#include <stdint.h>


#define MAX_WIRES   512


class iwire {
   public:
      virtual uint16_t id() const = 0 ;
} ;


class wire : public iwire {
  public:
    wire() ;
    uint16_t id() const { return _id ; } ;
  private:
    uint16_t _id ;
} ;


template <uint8_t n> class bus {
  private:
    wire wires[n] ;
} ;


namespace input {
  class wire : public ::iwire  {
    public:
      wire(const ::wire &w){ _id = w.id() ; } ;
      uint16_t id() const { return _id ; } ;
    private:
      uint16_t _id ;
  } ;
} ;


namespace output {
  class wire : public ::iwire {
    public:
      wire(const ::wire &w){ _id = w.id() ; } ;
      uint16_t id() const { return _id ; } ;
    private:
      uint16_t _id ;
  } ;
} ;


#endif
