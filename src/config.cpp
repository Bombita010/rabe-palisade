// @file config.cpp - 读取配置文件config/config.json（环参数，系统参数等）

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <unistd.h>

#include "palisade.h"

using json = nlohmann::json;
using namespace lbcrypto;

class Config
{
private:
    /* data */
public:
    static usint ringSize;
    static usint base;
    static usint numAttributes;

    Config(/* args */);
    ~Config();
 
    static void LoadConfig(const std::string& filePath)
    {
        std::ifstream file(filePath);
        json j;
        file >> j;

        ringSize = j["ringSize"].get<usint>();
        base = j["base"].get<usint>();
        numAttributes = j["numOfAttributes"].get<usint>();
    }
};

Config::Config(/* args */)
{
}

Config::~Config()
{
}

usint Config::ringSize;
usint Config::base;
usint Config::numAttributes;

int main()
{
    //输出当前工作路径
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        std::cout << "当前工作目录" << cwd << std::endl;
    }
    else
    { 
        perror("getcwd() error ");
        return 1;
    }

    //测试能否成功打开config.json
    /*绝对路径*/
    std::ifstream file("/home/bombita/rabe/config/config.json");
    /*相对路径，需要在项目根目录下运行？？？好像还是无法成功打开*/
    /*std::ifstream file("/config/config.json");*/
    if (!file.is_open())
    {
        std::cerr << "无法打开文件：" << "/home/bombita/rabe/config/config.json" << std::endl;
        return 0;
    }
    
    Config::LoadConfig("/home/bombita/rabe/config/config.json");
    std::cout << "环大小：" << Config::ringSize << std::endl;
    std::cout << "基：    " << Config::base     << std::endl;

    return 0;
}