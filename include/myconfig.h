/*  @file myconfig.h - 读取配置文件config/config.json（环参数，系统参数等）  */ 

#ifndef MYCONFIG_H
#define MYCONFIG_H

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <mutex>

#include "palisade.h"

using json = nlohmann::json;
using namespace lbcrypto;

class MyConfig
{
public:
    //获取单例对象的引用
    static MyConfig& getConfig();

    //删除拷贝构造函数和赋值操作符确保单例
    MyConfig(const MyConfig &) = delete;
    MyConfig& operator=(const MyConfig&) = delete;
    
    int getIntValue(const std::string &key);

    usint getUsintValue(const std::string &key);


 
private:
    static std::mutex mutex_;

    //私有构造函数
    MyConfig();

    //存储配置信息的json对象
    json configData;

    //加载json配置文件
    bool loadConfig(const std::string& filePath);
    
};

#endif //MYCONFIG_H