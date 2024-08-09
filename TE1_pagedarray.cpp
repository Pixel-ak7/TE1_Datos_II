#include <iostream>
#include <fstream>
#include <unordered_map>
#include <array>
#include <deque>  


class PagedArray {
public:
    PagedArray(const std::string& filePath, size_t fileSize); 
    ~PagedArray();  
    int& operator[](size_t index); 
    void savePagesToFile();  

    size_t getPageFaults() const { return pageFaults; } 
    size_t getPageHits() const { return pageHits; }  
private:
    std::string filePath;  
    size_t fileSize;  
    std::unordered_map<size_t, std::array<int, 1024>> pages;  
    std::deque<size_t> pageOrder;
    size_t pageFaults = 0;  // Contador de page faults
    size_t pageHits = 0;  // Contador de page hits

    void loadPage(size_t pageIndex);  // Carga una página desde el archivo a memoria
    void savePage(size_t pageIndex);  // Guarda una página de la memoria al archivo
    size_t getPageIndex(size_t index);  // Calcula el índice de la página correspondiente a un índice dado
    size_t getOffset(size_t index);  // Calcula el offset dentro de una página para un índice dado
};


PagedArray::PagedArray(const std::string& filePath, size_t fileSize)
    : filePath(filePath), fileSize(fileSize) {
}

// Destructor que asegura que todas las páginas en memoria se guardan en el archivo
PagedArray::~PagedArray() {
    savePagesToFile();
}

// Sobrecarga del operador [] para acceder a un elemento específico en el array paginado
int& PagedArray::operator[](size_t index) {
    size_t pageIndex = getPageIndex(index);  // Calcula la página en la que está el índice
    size_t offset = getOffset(index);  // Calcula el offset dentro de la página

    // Si la página ya está cargada en memoria, cuenta como un page hit
    if (pages.find(pageIndex) != pages.end()) {
        pageHits++;
    } else {
        // Si hay más de 4 páginas cargadas, se descarga la más antigua (FIFO)
        if (pages.size() >= 4) {
            size_t pageToUnload = pageOrder.front();
            savePage(pageToUnload);  // Guarda la página en el archivo
            pages.erase(pageToUnload);  // Elimina la página de la memoria
            pageOrder.pop_front();  // Quita la página del deque
        }
        loadPage(pageIndex);  // Carga la nueva página desde el archivo
        pageFaults++;
    }

    pageOrder.push_back(pageIndex);  // Añade la página al final del deque
    return pages[pageIndex][offset];  // Devuelve la referencia al elemento en la página
}


void PagedArray::loadPage(size_t pageIndex) {
    std::ifstream inFile(filePath, std::ios::binary);  
    if (!inFile) {
        std::cerr << "Error opening input file: " << filePath << std::endl;
        exit(1);
    }

    inFile.seekg(pageIndex * 1024 * sizeof(int), std::ios::beg);  
    std::array<int, 1024> pageData;  
    inFile.read(reinterpret_cast<char*>(pageData.data()), 1024 * sizeof(int));  
    pages[pageIndex] = pageData;  

    inFile.close();  
}


void PagedArray::savePage(size_t pageIndex) {
    std::ofstream outFile(filePath, std::ios::binary | std::ios::in);  
    if (!outFile) {
        std::cerr << "Error opening output file: " << filePath << std::endl;
        exit(1);
    }

    outFile.seekp(pageIndex * 1024 * sizeof(int), std::ios::beg);  
    outFile.write(reinterpret_cast<const char*>(pages[pageIndex].data()), 1024 * sizeof(int));  

    outFile.close();  
}

// Función que guarda todas las páginas cargadas en el archivo al terminar
void PagedArray::savePagesToFile() {
    for (const auto& pageIndex : pages) {
        savePage(pageIndex.first);  // Guarda cada página que esté en memoria
    }
}


size_t PagedArray::getPageIndex(size_t index) {
    return index / 1024;  // Cada página tiene 1024 enteros, se usa división entera
}


size_t PagedArray::getOffset(size_t index) {
    return index % 1024;  
}
