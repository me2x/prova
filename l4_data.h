#ifndef L4_DATA_H
#define L4_DATA_H

#include "port.h"
class L4_Data
{
public:
    std::string name;
    std::list<Port*> ports;
};

#endif // L4_DATA_H
