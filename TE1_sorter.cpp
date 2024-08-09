#include <iostream>
#include <fstream>
#include <chrono>
#include "TE1_pagedarray.cpp"  


void quickSort(PagedArray& arr, int left, int right);
void insertionSort(PagedArray& arr, int size);
void bubbleSort(PagedArray& arr, int size);

// Implementación del algoritmo QuickSort
void quickSort(PagedArray& arr, int left, int right) {
    if (left < right) {
        int i = left, j = right;
        int pivot = arr[(left + right) / 2];  

        while (i <= j) {
            while (arr[i] < pivot) i++;  
            while (arr[j] > pivot) j--;  
            if (i <= j) {
                std::swap(arr[i], arr[j]);  
                i++;
                j--;
            }
        }

        
        if (left < j) quickSort(arr, left, j);
        if (i < right) quickSort(arr, i, right);
    }
}


void insertionSort(PagedArray& arr, int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  
            j--;
        }
        arr[j + 1] = key;  
    }
}

void bubbleSort(PagedArray& arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);  
            }
        }
        if (i % 1000 == 0) {  
            std::cout << "Bubble sort progress: " << i << " / " << size - 1 << std::endl;
        }
    }
}


size_t getFileSize(const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary | std::ios::ate);  
    return inFile.tellg();  
}


int main(int argc, char* argv[]) {
    if (argc != 7) {
        
        std::cerr << "Usage: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITHM>" << std::endl;
        return 1;
    }

    // Obtiene los argumentos pasados en la línea de comandos
    std::string inputPath = argv[2];
    std::string outputPath = argv[4];
    std::string algorithm = argv[6];

    std::cout << "Reading input file: " << inputPath << std::endl;
    size_t fileSize = getFileSize(inputPath);  
    if (fileSize == 0) {
        std::cerr << "Error: Input file is empty or could not be read." << std::endl;
        return 1;
    }

    std::cout << "File size: " << fileSize << " bytes" << std::endl;

    PagedArray arr(inputPath, fileSize);  // Crea una instancia de PagedArray para manejar el archivo

    std::cout << "Starting sorting using algorithm: " << algorithm << std::endl;

    auto start = std::chrono::high_resolution_clock::now();  


    if (algorithm == "QS") {
        quickSort(arr, 0, fileSize / sizeof(int) - 1);
    } else if (algorithm == "IS") {
        insertionSort(arr, fileSize / sizeof(int));
    } else if (algorithm == "BS") {
        bubbleSort(arr, fileSize / sizeof(int));
    } else {
        std::cerr << "Invalid algorithm argument. Use QS, IS, or BS." << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();  
    std::chrono::duration<double> duration = end - start;  

    std::ofstream outFile(outputPath, std::ios::binary);  
    std::cout << "Writing sorted data to output file: " << outputPath << std::endl;

    // Escribe los datos ordenados en el archivo de salida
    for (size_t i = 0; i < fileSize / sizeof(int); ++i) {
        int value = arr[i];
        outFile.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }

    
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    std::cout << "Algorithm used: " << algorithm << std::endl;
    std::cout << "Page faults: " << arr.getPageFaults() << std::endl;
    std::cout << "Page hits: " << arr.getPageHits() << std::endl;

    return 0;  
}
// Tambien deberia poner cada vez que se me sobrecalento el procesador de tanta cosa