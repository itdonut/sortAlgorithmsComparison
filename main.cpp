#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <random>

#include "Object.h"
#include "Sorting.h"
#include "Printer.h"
#include "FileManager.h"
#include "Algorithm.h"
#include "DataType.h"

const uint32_t arraySize = 5000;
const int64_t minValue = INT32_MIN;
const int64_t maxValue = INT32_MAX;
const std::string fileName = "result/file.txt";

template<class T>
T getRandInteger(const int64_t min, const int64_t max) {
    T maxVal = std::numeric_limits<T>::max();

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<int64_t> distr(min, max);

    auto rn = distr(gen);

    if (rn > maxVal)
        return maxVal;

    return (T) rn; // because value can be greater then max value of the array datatype
}

template<class T>
void fillArray(T* arr, const uint32_t n, const int64_t min, const int64_t max) {
    for(uint32_t i=0; i < n; i++){
        arr[i] = getRandInteger<T>(min, max);
    }
}

template<class T>
T* copyArray(T* arr, const uint32_t n) {
    T* newArr = new T[n];
    for (uint32_t i = 0; i < n; i++)
        newArr[i] = arr[i];
    return newArr;
}

std::string getTimeUTC() {
     // Get the current time from the UTC clock
    auto now = std::chrono::system_clock::now();
    // Convert the time point to system time (seconds since epoch)
    auto now_sys = std::chrono::system_clock::to_time_t(now);
    // Convert to a readable string using std::put_time
    std::tm tm = *std::gmtime(&now_sys);  // gmtime converts time_t to UTC

    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");  // Format as YYYY-MM-DD HH:MM:SS

    return ss.str();
}

int main()
{
    int32_t* arr1 = new int32_t[arraySize];
    fillArray<int32_t>(arr1, arraySize, minValue, maxValue);

    int32_t* arr2 = copyArray<int32_t>(arr1, arraySize);
    int32_t* arr3 = copyArray<int32_t>(arr1, arraySize);
    int32_t* arr4 = copyArray<int32_t>(arr1, arraySize);
    int32_t* arr5 = copyArray<int32_t>(arr1, arraySize);
    int32_t* arr6 = copyArray<int32_t>(arr1, arraySize);

    //Printer::printArray2D<int32_t>(arr1, arraySize);
    //Printer::printArray2D<int32_t>(arr2, arraySize);
    //Printer::printArray2D<int32_t>(arr3, arraySize);
    //Printer::printArray2D<int32_t>(arr4, arraySize);
    //Printer::printArray2D<int32_t>(arr5, arraySize);
    //Printer::printArray2D<int32_t>(arr6, arraySize);

    std::cout << "Bubble sort has been starting" << std::endl;
    const auto start1 = std::chrono::high_resolution_clock::now();
    Sorting::bubble<int32_t>(arr1, arraySize);
    const auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << "Bubble sort has been ending" << std::endl;

    std::cout << "Insertion sort has been starting" << std::endl;
    const auto start2 = std::chrono::high_resolution_clock::now();
    Sorting::insertion<int32_t>(arr2, arraySize);
    const auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "Insertion sort has been ending" << std::endl;

    std::cout << "Quick sort has been starting" << std::endl;
    const auto start3 = std::chrono::high_resolution_clock::now();
    Sorting::quick<int32_t>(arr3, 0, arraySize - 1);
    const auto end3 = std::chrono::high_resolution_clock::now();
    std::cout << "Quick sort has been ending" << std::endl;

    std::cout << "Selection sort has been starting" << std::endl;
    const auto start4 = std::chrono::high_resolution_clock::now();
    Sorting::selection<int32_t>(arr4, arraySize);
    const auto end4 = std::chrono::high_resolution_clock::now();
    std::cout << "Selection sort has been ending" << std::endl;

    std::cout << "Merge sort has been starting" << std::endl;
    const auto start5 = std::chrono::high_resolution_clock::now();
    Sorting::merge<int32_t>(arr5, 0, arraySize - 1);
    const auto end5 = std::chrono::high_resolution_clock::now();
    std::cout << "Merge sort has been ending" << std::endl;

    std::cout << "Bubble_SIMD sort has been starting" << std::endl;
    const auto start6 = std::chrono::high_resolution_clock::now();
    Sorting::bubble_SIMD_int32(arr6, arraySize);
    const auto end6 = std::chrono::high_resolution_clock::now();
    std::cout << "Bubble_SIMD sort has been ending" << std::endl;

    //Printer::printArray2D<int32_t>(arr1, arraySize);
    //Printer::printArray2D<int32_t>(arr2, arraySize);
    //Printer::printArray2D<int32_t>(arr3, arraySize);
    //Printer::printArray2D<int32_t>(arr4, arraySize);
    //Printer::printArray2D<int32_t>(arr5, arraySize);
    //Printer::printArray2D<int32_t>(arr6, arraySize);

    const std::chrono::duration<double> diff1 = end1 - start1;
    const std::chrono::duration<double> diff2 = end2 - start2;
    const std::chrono::duration<double> diff3 = end3 - start3;
    const std::chrono::duration<double> diff4 = end4 - start4;
    const std::chrono::duration<double> diff5 = end5 - start5;
    const std::chrono::duration<double> diff6 = end6 - start6;

    double s1 = diff1.count();
    double s2 = diff2.count();
    double s3 = diff3.count();
    double s4 = diff4.count();
    double s5 = diff5.count();
    double s6 = diff6.count();

    FileRowData data;
    data.algorithm = AlgorithmName[Algorithm::BUBBLE];
    data.dataType = DataTypeName[DataType::INT32_T];
    data.minValue = minValue;
    data.maxValue = maxValue;
    data.itemsCount = arraySize;
    data.duration = s1;
    data.datetime = getTimeUTC();

    FileManager* fm = new FileManager(fileName);
    fm->initFileStructure();

    auto row = fm->buildDataToWrite(data);
    fm->writeDataRow(row);

    data.algorithm = AlgorithmName[Algorithm::INSERTION];
    data.duration = s2;
    data.datetime = getTimeUTC();

    row = fm->buildDataToWrite(data);
    fm->writeDataRow(row);

    data.algorithm = AlgorithmName[Algorithm::QUICK];
    data.duration = s3;
    data.datetime = getTimeUTC();

    row = fm->buildDataToWrite(data);
    fm->writeDataRow(row);

    data.algorithm = AlgorithmName[Algorithm::SELECTION];
    data.duration = s4;
    data.datetime = getTimeUTC();

    row = fm->buildDataToWrite(data);
    fm->writeDataRow(row);

    data.algorithm = AlgorithmName[Algorithm::MERGE];
    data.duration = s5;
    data.datetime = getTimeUTC();

    row = fm->buildDataToWrite(data);
    fm->writeDataRow(row);

    data.algorithm = AlgorithmName[Algorithm::BUBBLE_SIMD];
    data.duration = s6;
    data.datetime = getTimeUTC();

    row = fm->buildDataToWrite(data);
    fm->writeDataRow(row);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete fm;

    return 0;
}
