#include <iostream>
#include <fstream>
#include <random>
#include <string>

// Esta función se encarga de generar un archivo binario
// con números aleatorios. El tamaño del archivo se especifica
// en el argumento fileSize.
void generateFile(const std::string& outputPath, size_t fileSize) {
    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening output file: " << outputPath << std::endl;
        return;
    }

    
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> dist(1, 100); 

    size_t totalIntegers = fileSize / sizeof(int); 
    for (size_t i = 0; i < totalIntegers; ++i) {
        int randomNumber = dist(gen); // Genera un número aleatorio
        outFile.write(reinterpret_cast<const char*>(&randomNumber), sizeof(int));
    }

    outFile.close(); 
    std::cout << "Creaste un mosntruo come ram: " << outputPath << std::endl; // Mensaje de éxito
}

// Función principal que procesa los argumentos de la linea de comandos y llama a generateFile
int main(int argc, char* argv[]) {
    if (argc != 5) {
        // Si no se proporcionan los argumentos correctos, se muestra el mensaje de uso y se termina el programa
        std::cerr << "Usage: generator -size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        return 1;
    }

    // Se extraen los argumentos pasados en la linea de comandos
    std::string sizeArg = argv[1];
    std::string sizeValue = argv[2];
    std::string outputArg = argv[3];
    std::string outputPath = argv[4];
    size_t fileSize = 0; 

    if (sizeArg == "-size" && outputArg == "-output") {
        
        if (sizeValue == "SMALL") {
            fileSize = 512ULL * 1024 * 1024; // Tamaño pequeño (512MB)                                                                                       "para mis pruebas pquité  512mb y puse 5mb porque si no explotaba todo y mi ram moria"
        } else if (sizeValue == "MEDIUM") {
            fileSize = 1024ULL * 1024 * 1024; // Tamaño mediano (1GB)
        } else if (sizeValue == "LARGE") {
            fileSize = 2ULL * 1024 * 1024 * 1024; // Tamaño grande (2GB)
        } else {
            // Si el tamaño especificado no es válido, se muestra un mensaje de error
            std::cerr << "Invalid size argument. Use SMALL, MEDIUM, or LARGE." << std::endl;
            return 1;
        }
    } else {
        
        std::cerr << "Usage: generator -size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        return 1;
    }


    generateFile(outputPath, fileSize);
    return 0; 
}
