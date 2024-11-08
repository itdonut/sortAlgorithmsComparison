#ifndef FILEMANAGER_H_INCLUDED
#define FILEMANAGER_H_INCLUDED

#include <cstring>
#include <fstream>
#include <cstdint>

#include "FileRowData.h"

class FileManager {
public:
    FileManager(std::string);
    void initFileStructure();
    std::string buildDataToWrite(FileRowData&);
    void writeDataRow(std::string);
private:
    std::string fileName;
    std::ofstream openFile();
};

#endif // FILEMANAGER_H_INCLUDED
