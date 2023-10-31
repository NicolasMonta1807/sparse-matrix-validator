Autores: Gabriel Espitia Romero y Nicolás Montañez Velasco - Pontificia Universidad Javeriana

Esta aplicación permite validar si una matriz es dispersa o no, es decir, si el porcentaje de ceros es mayor al porcentaje de elementos diferentes de cero. 
Para esto se utilizan dos programas, uno que utiliza hilos y otro que utiliza procesos. 

Ambos programas reciben como parámetros el número de filas, el número de columnas, el porcentaje de aceptación, 
el número de hilos o procesos y el nombre del archivo que contiene la matriz a evaluar.

Instrucciones de compilación:

Diríjase a la carpeta  sparse-matrix-validator.

Ya dentro de la carpeta escriba el siguiente comando: “make”

De esta forma ya deberían compilarse los programas del manejo tanto con hilos como con procesos

Para correr cada uno se utiliza el comando:
	Progama con PROCESOS:  ./bin/process
	
	Programa con HILOS: ./bin/threads

Junto con esto le tiene que añadir lo siguiente:

	-f [número de filas] -c [número de columnas] -p [porcentaje de aceptación] -n [número de procesos] -a [Fichero con la matriz a evaluar]

Ejemplo del comando completo:

./bin/threads -f 1000 -c 2000 -p 50 -n 4 -a ./data/1000x2000.txt

La carpeta "./data" contiene algunas matrices de ejemplo para su uso.
