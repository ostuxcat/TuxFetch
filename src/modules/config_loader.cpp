#include<string>
#include<fstream>
#include <unordered_map>
#include<string>
#include<iostream>

std::unordered_map<std::string, std::string> load_config(const std::string &CONFIG_FILE){
    std::unordered_map<std::string, std::string> allconfig;
    std::ifstream file(CONFIG_FILE);
    if(!file){
        std::cerr << "Invalid Config File!" << std::endl;
        return allconfig;
    }
    std::string line;
    while(std::getline(file, line)){
        int idx = line.find("=");
        if(idx) allconfig[line.substr(0, idx)] = line.substr(idx+1);
    }
    return allconfig;
}
