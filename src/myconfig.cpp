/*  @file myconfig.cpp - 读取配置文件config/config.json（环参数，系统参数等）  */ 
#include "myconfig.h"


std::mutex MyConfig::mutex_;

MyConfig::MyConfig() 
{
    loadConfig("/home/bombita/rabe/config/config.json");
}

MyConfig& MyConfig::getConfig() 
{
    std::lock_guard<std::mutex> lock(mutex_);
    static MyConfig instance;
    return instance;
}

bool MyConfig::loadConfig(const std::string& filePath)
{
    std::ifstream file(filePath);
    if( !file.is_open())
    {
        std::cerr << "无法打开config.json文件" << filePath << std::endl;
        return false; // 无法打开文件
    }
    std::cout << "打开/home/bombita/rabe/config/config.json" << std::endl;
    file >> configData;

    return true;

    // level = j["level"].get<usint>();
    // ringSize = j["ringSize"].get<usint>();
    // base = j["base"].get<usint>();
    // numAttributes = j["numOfAttributes"].get<usint>();
}

usint MyConfig::getUsintValue(const std::string &key)
{
    try
    {
        std::cout << key << std::endl;
        return configData["level"].get<usint>();
    }
    catch(json::exception& e)
    {
        std::cerr << "JSON exception" << e.what() << std::endl;
        return 0;
    }
}

// int main()
// {
//     MyConfig &config = MyConfig::getConfig();
//     if (config.loadConfig()) 
//     {
//         // 假设配置文件中有一个名为 "level" 的usint类型的值
//         usint value = config.getUsintValue("level");
//         std::cout << "Value for 'level': " << value << std::endl;
//     } 
//     else 
//     {
//         std::cerr << "获取config失败" << std::endl;
//     }
// }

// int main()
// {
    
        ////输出当前工作路径
        // char cwd[1024];
        // if (getcwd(cwd, sizeof(cwd)) != NULL)
        // {
        //     std::cout << "当前工作目录" << cwd << std::endl;
        // }
        // else
        // { 
        //     perror("getcwd() error ");
        //     return j;
        // }

//     //测试能否成功打开config.json
//     /*绝对路径*/
//     std::ifstream file("/home/bombita/rabe/config/config.json");
//     /*相对路径，需要在项目根目录下运行？？？好像还是无法成功打开*/
//     /*std::ifstream file("/config/config.json");*/
//     if (!file.is_open())
//     {
//         std::cerr << "无法打开文件：" << "/home/bombita/rabe/config/config.json" << std::endl;
//         return 0;
//     }
    
//     Config::LoadConfig("/home/bombita/rabe/config/config.json");
//     std::cout << "环大小：" << Config::ringSize << std::endl;
//     std::cout << "基：    " << Config::base     << std::endl;

//     return 0;
// }
