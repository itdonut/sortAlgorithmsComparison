#ifndef DATATYPE_H_INCLUDED
#define DATATYPE_H_INCLUDED

#include <unordered_map>

enum DataType {
    INT8_T,
    INT16_T,
    INT32_T,
    INT64_T,
    CHAR,
    STRING,
    DOUBLE,
    FLOAT
};

std::unordered_map<DataType, std::string> DataTypeName = {
    {INT8_T, "INT8_T"},
    {INT16_T, "INT16_T"},
    {INT32_T, "INT32_T"},
    {INT64_T, "INT64_T"},
    {CHAR, "CHAR"},
    {STRING, "STRING"},
    {DOUBLE, "DOUBLE"},
    {FLOAT, "FLOAT"}
};

#endif // DATATYPE_H_INCLUDED
