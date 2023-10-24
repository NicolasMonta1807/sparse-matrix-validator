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
