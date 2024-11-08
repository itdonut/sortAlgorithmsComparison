#include "FileManager.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <ios>

FileManager::FileManager(std::string fileName) {
    this->fileName = fileName;
}

void FileManager::initFileStructure() {
    std::ofstream fs = this->openFile();
    if (fs.is_open()) {
        fs << "-------------------------------------------------------------------------------------------------------------------------------------------\n";
        fs << std::left << "| " << std::setw(15) << std::string("ALGORITHM").substr(0, 15);
        fs << std::left << "| " << std::setw(15) << std::string("DATA TYPE").substr(0, 15);
        fs << std::left << "| " << std::setw(22) << std::string("MIN VALUE").substr(0, 22);
        fs << std::left << "| " << std::setw(22) << std::string("MAX VALUE").substr(0, 22);
        fs << std::left << "| " << std::setw(15) << std::string("ITEMS COUNT").substr(0, 15);
        fs << std::left << "| " << std::setw(15) << std::string("DURATION").substr(0, 15);
        fs << std::left << "| " << std::setw(20) << std::string("DATETIME(UTC)").substr(0, 20) << "|\n";
        fs << "-------------------------------------------------------------------------------------------------------------------------------------------\n";
        fs.close();
    }
}

std::string FileManager::buildDataToWrite(FileRowData& data) {
    std::string algorithm = data.algorithm;
    std::string dataType = data.dataType;
    std::string minVal = std::to_string(data.minValue);
    std::string maxVal = std::to_string(data.maxValue);
    std::string itemsCount = std::to_string(data.itemsCount);
    std::string duration = std::to_string(data.duration) + "s";
    std::string datetime = data.datetime;

    std::stringstream ss;
    ss << std::left << "| " << std::setw(15) << algorithm.substr(0, 15);
    ss << std::left << "| " << std::setw(15) << dataType.substr(0, 15);
    ss << std::left << "| " << std::setw(22) << minVal.substr(0, 22);
    ss << std::left << "| " << std::setw(22) << maxVal.substr(0, 22);
    ss << std::left << "| " << std::setw(15) << itemsCount.substr(0, 15);
    ss << std::left << "| " << std::setw(15) << duration.substr(0, 15);
    ss << std::left << "| " << std::setw(20) << datetime.substr(0, 20) << "|\n";
    return ss.str();
}

void FileManager::writeDataRow(std::string row) {
    std::ofstream fs = this->openFile();
    if (fs.is_open()) {
        fs << row;
        fs << "-------------------------------------------------------------------------------------------------------------------------------------------\n";
        fs.close();
    }
}

std::ofstream FileManager::openFile() {
    return std::ofstream(this->fileName, std::ios::app);
}
