#pragma once
#include "lowlevel.h"

class Mapping {
public:
    virtual ~Mapping();

    virtual Int size() const;
    virtual Index operator [] (Int i) const;
    virtual Index operator () (Int i) const;
    
    bool operator == (const Mapping &other) const;
    bool operator != (const Mapping &other) const;
};

