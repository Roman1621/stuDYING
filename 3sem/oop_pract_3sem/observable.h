#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "observer.h"

class Observable{
    private:
        Observer* observer = nullptr;

    public:
        void set_observer(Observer& observer);
        void notify_observer(); 
};

#endif