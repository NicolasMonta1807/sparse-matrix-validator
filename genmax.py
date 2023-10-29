import random
import argparse

def generar_matriz(filas, columnas):
    matriz = [[random.randint(0, 1) for _ in range(columnas)] for _ in range(filas)]
    return matriz

def guardar_matriz_en_archivo(matriz, nombre_archivo):
    with open(nombre_archivo, 'w') as archivo:
        for fila in matriz:
            fila_str = ' '.join(map(str, fila))
            archivo.write(fila_str + '\n')

def main():
    parser = argparse.ArgumentParser(description="Generar una matriz de 1's y 0's y guardarla en un archivo de texto.")
    parser.add_argument('filas', type=int, help='Número de filas de la matriz.')
    parser.add_argument('columnas', type=int, help='Número de columnas de la matriz.')
    parser.add_argument('nombre_archivo', type=str, help='Nombre del archivo donde se guardará la matriz.')
    args = parser.parse_args()

    filas = args.filas
    columnas = args.columnas
    nombre_archivo = args.nombre_archivo

    matriz = generar_matriz(filas, columnas)
    guardar_matriz_en_archivo(matriz, nombre_archivo)

    print(f"Matriz guardada en {nombre_archivo}.")

if __name__ == '__main__':
    main()
