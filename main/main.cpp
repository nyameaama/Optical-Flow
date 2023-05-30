#include <iostream>
#include <string>
#include "_init.h"
#include "analysis.h"

int main() {
    _initialise *obj = new _initialise();
    _Analysis *obj2 = new _Analysis();

    //Check if dependencies available
    bool Dcheck = obj -> dependencyCheck();
    if(!Dcheck){
        return;
    }

    //Get content path from config file
    std::string path = obj -> readfilePathfromConfig();

    //Perform content check
    bool Ccheck = obj -> contentCheck(path);
    if(!Ccheck){
        std::cout << "There is problem loading the experimental data" << std::endl;
        return;
    }else{
        //Push some video metadata to output csv

    }

    //Get Region of Interest from config file
    uint16_t ROI;

    //Start Performing analysis

    //Initial Step1
    obj2 -> analysisStep1(path);


    delete obj;
    delete obj2;
}