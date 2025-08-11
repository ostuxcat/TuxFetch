#include "sysinfo.h"
#include "config_loader.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include<iostream>
const std::string INFO_FILE = "/proc/cpuinfo";
std::string final_out;
void add_data(std::unordered_map<std::string, std::string> &allconfig, std::string &out, std::ifstream &file, std::string finder){
    std::string line;
    for(std::pair<const std::string, std::string> &config : allconfig){
        if(config.first.find(finder)!=std::string::npos){
            while(std::getline(file, line)){
                int idx = line.find(config.second);
                if(idx!=std::string::npos){
                    std::string colname = config.first;
                    out+=std::format("{}: {}\n", colname.replace(colname.find("_"), 1, " "), line.substr(line.find(": ")+1));
                    break;
                }
            }
        }
    }
}
void cpu_info(){
    std::unordered_map<std::string, std::string> allconfig = load_config();
    final_out+="__CPU_INFO__\n";
    std::ifstream file(INFO_FILE);
    if(file){
        add_data(allconfig, final_out, file, "cpu");
    }
}
std::string get_info(){
    cpu_info();
    return final_out;
}
