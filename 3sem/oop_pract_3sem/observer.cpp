#include "..//headers/observer.h"

Observer::Observer(OWrapper& ostr){
    this->ostr_list.push_back(ostr);
    ostr.link();
}

Observer::Observer(const std::vector<std::reference_wrapper<OWrapper>>& stream){
    for(auto i = stream.begin(); i != stream.end(); i++){
        OWrapper& owrapper = (*i);
        owrapper.link();
        ostr_list.push_back(*i);
    }
}

Observer::~Observer(){
    for(auto i = ostr_list.begin(); i != ostr_list.end(); i++){
        OWrapper& owrapper = (*i);
        owrapper.unlink();
    }
}