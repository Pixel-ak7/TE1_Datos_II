unicamente se necesita Compilador de C++, todos los archvios en el mismo directorio. 

y aproximadamente 32 años de vida para poder ver el resultado de IS con el archivo de 2 GB.

(NO ENTIENDO NADA PORQUE UN ARCHIVO DE 500MB CON QUICKSORT DURA 42 HORAS??? a lo mejor fue mala implementacion o mala optimizacion)
entiendo que puede ser el tema ed los arrerglos y que solo sean 4 y estar cargando y descargando la memoria o que hayan muchos page faults pero ni idea :D



Comando de uso: 
crear el .exe del sorter: g++ -o sorter TE1_sorter.cpp
crear el .exe del generator: g++ -o generator TE1_generator.cpp    
crear arhcivo pequeño,mediano o grande segun corresponda: ./generator -size SMALL -output small_test.dat (Cambiar SMALL por MEDIUM o LARGE en dado caso de ser necesario)
ejecutar el jsorter con el archivo: ./sorter -input small_test.dat -output sorted_test.dat -alg QS   (Cambiar QS a IS o BS para cada tipo de algoritmo.)


Ejemplo:

PS C:\Users\tenci\OneDrive\Escritorio\TAREA e1> ./sorter -input small_test.dat -output sorted_test.dat -alg QS
>> 
Reading input file: small_test.dat
File size: 5242880 bytes   (5 MB)
Starting sorting using algorithm: QS
Writing sorted data to output file: sorted_test.dat
Time taken: 10.1712 seconds
Algorithm used: QS
Page faults: 1285
Page hits: 52995245













en este caso con quicksort y un archivo de solo 5MB duro 10 segundos, y el arpoximado para el archvio de 512MB duraria 37 horas con lo cual mejor no hablar del de 1GB, mucho menos el de 2GB...

PS C:\Users\tenci\OneDrive\Escritorio\TAREA e1> ./sorter -input small_test.dat -output sorted_test.dat -alg BS
>> 
Reading input file: small_test.dat
File size: 5242880 bytes
Starting sorting using algorithm: BS
Bubble sort progress: 0 / 1310719
Bubble sort progress: 1000 / 1310719
terminate called after throwing an instance of 'std::bad_alloc'


Con BS y el archivo de 5MB vs code llego a cosumir 28GB de ram...(NO DIO LA MEMORIA Y SE DETUVO) tan mal lo he implementado ? 

(Ya pude solucinarlo, erque que liberaba mal la memoria, ya no usa 29GB de ram, pero igual dura una semana en ordenar el de 51mb)







PS C:\Users\tenci\OneDrive\Escritorio\TAREA e1> ./sorter -input small_test.dat -output sorted_test.dat -alg BS
>> 
Reading input file: small_test.dat
File size: 12288 bytes
Starting sorting using algorithm: BS
Bubble sort progress: 0 / 3071
Bubble sort progress: 1000 / 3071
Bubble sort progress: 2000 / 3071
Bubble sort progress: 3000 / 3071
Writing sorted data to output file: sorted_test.dat
Time taken: 0.934672 seconds
Algorithm used: BS
Page faults: 3
Page hits: 11044241


PS C:\Users\tenci\OneDrive\Escritorio\TAREA e1> ./sorter -input small_test.dat -output sorted_test.dat -alg IS
>> 
Reading input file: small_test.dat
File size: 5120 bytes
Starting sorting using algorithm: IS
Writing sorted data to output file: sorted_test.dat
Time taken: 0.105306 seconds
Algorithm used: IS
Page faults: 2
Page hits: 1240763
PS C:\Users\tenci\OneDrive\Escritorio\TAREA e1> 





Aqui si funcionó para BS y IS con un archivo super pequeño.

