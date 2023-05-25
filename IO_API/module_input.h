#ifndef MODULEINPUT
#define MODULEINPUT

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define FILE "testdata.csv"
#define FLOW 1
#define PRESSURE 2

class _moduleInput {
    public:
        std::string Values_raw;

    public:
        //Constructor 
        _moduleInput();

        void readFile();

        double getFlowData();

        double getPressureData();

        std::string testOUT();

    private:
        double convert_to_double(std::string data);

        std::string sortData(std::string data,uint8_t unit);

};

#endif