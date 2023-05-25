#include<iostream>
#include"module_input.h"

int main(){
    _moduleInput *SPobject = new _moduleInput();

    double flow_data = SPobject -> getFlowData();
    double p_data = SPobject -> getPressureData();
    std::cout << flow_data << std::endl;
    std::cout << p_data << std::endl;
    std::cout << SPobject -> testOUT() << std::endl;
    //Remove object 
    delete SPobject;
    return 0;
}

