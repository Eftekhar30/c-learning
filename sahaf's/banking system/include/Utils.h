#ifndef UTILS_H
#define UTILS_H

#include <string>

// Get current date and time as formatted string
std::string getCurrentTime();

// Count non-empty lines in a file
int countLinesInFile(const std::string& filename);

#endif