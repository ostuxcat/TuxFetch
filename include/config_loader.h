#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H
#include <unordered_map>
#include<string>
std::unordered_map<std::string, std::string> load_config(const std::string &CONFIG_FILE = "./config/config.ini");
#endif
