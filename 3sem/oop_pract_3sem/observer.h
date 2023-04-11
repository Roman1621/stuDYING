#ifndef OBSERVER_H
#define OBSERVER_H

#include <functional>
#include <iostream>
#include <vector>
#include "ostream_wrapper.h"

class Observer{
    protected:
        std::vector<std::reference_wrapper<OWrapper>> ostr_list;

    public:
        Observer(OWrapper& ostr);
        Observer(const std::vector<std::reference_wrapper<OWrapper>>& stream);
        virtual ~Observer();
        virtual void notify() = 0;    
};

#endif