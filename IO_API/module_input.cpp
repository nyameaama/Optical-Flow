#include"module_input.h"

 //Constructor 
_moduleInput::_moduleInput(){
    readFile();
}

double _moduleInput::convert_to_double(std::string data){
    return std::stod(data);
}

std::string _moduleInput::sortData(std::string data,uint8_t unit){
    //TABULAR FORMAT
    //  COLUMN 1 | COLUMN 2
    //  Pressure | Flow
    uint8_t index = 0;
    std::string flow;
    std::string pressure;
    for(uint8_t i = 0; i < data.length();i++){
        if(data[i] == ','){
            index = i;
        }
    }
    for(uint8_t j = 0; j <= data.length();j++){
        if(j < index){
            flow += data[j];
        }
        if(j > index){
            pressure += data[j];
        }
    }
    std::string returned = (unit == 1) ? flow : pressure;
    return returned;
}

void _moduleInput::readFile(){
    std::fstream file (FILE, std::ios::in);
    if(file.is_open()){
        file.seekg(-1,std::ios_base::end);                // go to one spot before the EOF

        bool keepLooping = true;
        while(keepLooping) {
            char ch;
            file.get(ch);                            // Get current byte's data

            if((int)file.tellg() <= 1) {             // If the data was at or before the 0th byte
                file.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if(ch == '\n') {                   // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            }
            else {                                  // If the data was neither a newline nor at the 0 byte
                file.seekg(-2,std::ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }

        std::string lastLine;            
        getline(file,lastLine);                      // Read the current line
        Values_raw = lastLine;
        file.close();
    }
}

double _moduleInput::getFlowData(){
    //Read 
    std::string getData = sortData(Values_raw,FLOW);
    double FLOW_Return = convert_to_double(getData);
    return FLOW_Return;
}

double _moduleInput::getPressureData(){
    std::string getData = sortData(Values_raw,PRESSURE);
    double PRESSURE_Return = convert_to_double(getData);
    return PRESSURE_Return;
}

std::string _moduleInput::testOUT(){
    return Values_raw;
}