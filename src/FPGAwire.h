#ifndef FPGAWIRE_H
#define FPGAWIRE_H 	

#include <stdint.h>


#define MAX_WIRES   512


class wire {
  public:
    wire() ;
    wire(uint16_t id) ;
    static void set(uint16_t id, bool v) ;
    void set(bool v) ;
    static bool get(uint16_t id) ;
    bool get() ;
    uint16_t id() ;
  private:
    uint16_t _id ;
} ;


namespace input {
  class wire : public ::wire {
    public:
      wire(wire &w) : ::wire(w.id()){} ;
  } ;
} ;


namespace output {
  class wire : public ::wire {
    public:
      wire(wire &w) : ::wire(w.id()){} ;
  } ;
} ;


#endif
