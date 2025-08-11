#include "sysinfo.h"
#include "config_loader.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include<iostream>
std::unordered_map<std::string, std::string> allconfig = load_config();
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
    const std::string INFO_FILE = "/proc/cpuinfo";
    final_out+="__CPU_INFO__\n";
    std::ifstream cpuinfo(INFO_FILE);
    if(cpuinfo.is_open()){
        add_data(allconfig, final_out, cpuinfo, "cpu");
    }
    cpuinfo.close();
}
void ram_info(){
    const std::string INFO_FILE = "/proc/meminfo";
    final_out+="__MEM_INFO__\n";
    std::ifstream meminfo(INFO_FILE);
    if(meminfo.is_open()){
        add_data(allconfig, final_out, meminfo, "mem");
    }
    meminfo.close();
}
std::string get_info(){
    cpu_info();
    ram_info();
    // for(std::pair<std::string, std::string> meow:allconfig){
    //     std::cout<< meow.first << ": " << meow.second << std::endl;
    // }
    return final_out;
}
