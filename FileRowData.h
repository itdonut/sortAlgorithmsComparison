#ifndef FILEROWDATA_H_INCLUDED
#define FILEROWDATA_H_INCLUDED

#include <string>
#include <cstdint>
#include <unordered_map>

struct FileRowData {
    std::string algorithm;
    std::string dataType;
    int64_t minValue;
    int64_t maxValue;
    uint32_t itemsCount;
    double duration;
    std::string datetime;
};

#endif // FILEROWDATA_H_INCLUDED
