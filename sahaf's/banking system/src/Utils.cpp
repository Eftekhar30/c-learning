#include "Utils.h"
#include <ctime>
#include <fstream>

std::string getCurrentTime() {
    time_t now = time(0);
    char dateStr[11];
    char timeStr[9];
    
    #ifdef _WIN32
        _strdate_s(dateStr, 11);
        _strtime_s(timeStr, 9);
    #else
        // Cross-platform alternative
        struct tm* timeinfo = localtime(&now);
        strftime(dateStr, 11, "%m/%d/%Y", timeinfo);
        strftime(timeStr, 9, "%H:%M:%S", timeinfo);
    #endif
    
    return std::string(dateStr) + " " + std::string(timeStr);
}

int countLinesInFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return 0;
    
    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) count++;
    }
    file.close();
    return count;
}