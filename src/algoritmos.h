#ifndef ALGORITMOS_H /* Evita declarações duplicadas. */
#define ALGORITMOS_H /* Registra que este cabeçalho já foi incluído. */

#include "metricas.h" /* Importa o tipo Metricas usado pelas funções. */

void bubbleSort(int v[], int n, Metricas *m); /* Declara a função Bubble Sort. */
void selectionSort(int v[], int n, Metricas *m); /* Declara a função Selection Sort. */
void insertionSort(int v[], int n, Metricas *m); /* Declara a função Insertion Sort. */
void mergeSort(int v[], int n, Metricas *m); /* Declara a função Merge Sort. */
void quickSort(int v[], int n, Metricas *m); /* Declara a função Quick Sort. */
void heapSort(int v[], int n, Metricas *m); /* Declara a função Heap Sort. */

#endif /* Finaliza a proteção do cabeçalho. */
