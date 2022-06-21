
#include "logger.h"

std::fstream logFile; //handler for log file

void otworzLoga(std::string fileName)
{
    logFile.open(fileName.c_str(), std::ios_base::app);
    if (!logFile.good() == true)
    {
        std::cout << "Cannot open log file " << fileName << std::endl;
    }
    zapiszLog("Log file opened");
}

void zamknijLog(void)
{
    zapiszLog("Log file closed");
    logFile.close();
}

void zapiszLog(std::string msg)
{
    std::string ss;
    time_t aktCzas = time(NULL);
    std::string txttime = (std::string)asctime(localtime(&aktCzas));
    txttime = txttime.substr(0, txttime.length() - 1);
    ss = (std::string)"T: " + txttime + " M: " + "\n" + msg + "\n";
    logFile << ss.c_str()<<std::endl;
    logFile.flush();
    std::cout << ss.c_str() << std::endl;
    std::cout.flush();
}
