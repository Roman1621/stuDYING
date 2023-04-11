#include "..//headers/observable.h"

void Observable::set_observer(Observer& observer){
    this->observer = &observer;
}

void Observable::notify_observer(){
    if(observer)
        observer->notify();
}