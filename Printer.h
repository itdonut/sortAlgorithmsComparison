#ifndef PRINTER_H_INCLUDED
#define PRINTER_H_INCLUDED

class Printer {
public:
    template<class T>
    static void printArray2D(T*, int32_t);
private:

};

template<class T>
void Printer::printArray2D(T* arr, int32_t n) {
    for (int32_t i = 0; i < n; i++) {
        std::cout << arr[i] << "\t";
        if (i == n - 1) {
            std::cout << std::endl;
            break;
        }
        if ((i + 1) % 5 == 0 && i + 1 <= n) std::cout << std::endl;
    }
}

#endif // PRINTER_H_INCLUDED
