//
//  main.c
//  Actividad 2
//  Recorrer un arreglo de cualquier tipo de datos utilizando diferentes tipos de iteradores
//  Created by Sab on 8/24/20.
//  Copyright © 2020 Sab. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10
#define L 3

typedef struct{
    char * titulo;
    int paginas;
} libro;

typedef int (*t_compare)(void *, void *);
typedef void (*t_type)(void *);
typedef void (* recorre_t)(void *, size_t, size_t,t_type);

void printInt(void *);
void printLibro(void *);

void recorre(void *, recorre_t ,size_t , size_t, t_type);
void forwardIterator(void * arreglo, size_t count, size_t size, t_type);
void reverseIterator(void * arreglo, size_t count, size_t size, t_type);
void bidirectionalIterator(void * arreglo, size_t count, size_t size, t_type);

void * begin(void * vector);
void * end(void * vector, size_t count, size_t size);
void * next(void * vector,void * actual, size_t count, size_t size);
void * prev(void * vector,void * actual,size_t count, size_t size);

int main(int argc, const char * argv[])
{
    //Crear números enteros random
    int * enteros = (int *) malloc(N * sizeof(int));

    int * aux = enteros;
    int * last = enteros + N;
    for (; aux < last; ++aux) {
        *aux = rand() % 100;
    }
    aux = enteros;
    last = enteros + N;
    for (; aux < last; ++aux) {
        printf(" %4d ", *aux);
    }

    printf("\nRecorriendo un arreglo de números enteros utilizando un Forward Iterator.\n");
    recorre(enteros, &forwardIterator, N,sizeof(*enteros), &printInt);

    printf("\nRecorriendo un arreglo de números enteros utilizando un Reverse Iterator.\n");
    recorre(enteros, &reverseIterator, N,sizeof(*enteros), &printInt);


    //Crear números enteros random arreglo de libros
    libro * libros = (libro *) malloc(sizeof(libro)*L);

    libros -> titulo  = (char *) malloc(sizeof(char)*25);
    strcpy(libros -> titulo , "Percy Jackson");
    libros -> paginas = 100;
    (libros + 1 )-> titulo  = (char *) malloc(sizeof(char)*25);
    strcpy((libros + 1 )-> titulo , "Ready player one");
    (libros + 1 )-> paginas = 200;
    (libros + 2 )-> titulo  = (char *) malloc(sizeof(char)*25);
    strcpy((libros + 2 )-> titulo , "Maze runner");
    (libros + 2 )-> paginas = 300;

    printf("\nRecorriendo un arreglo de estructuras del tipo Libro, utilizando un Bidirectional Iterator.\n");
    recorre(libros, &bidirectionalIterator, L ,sizeof(*libros), &printLibro);

    printf("\n\n");

    libro * aux1 = libros;
    libro * final = libros + L;
    for (; aux1 < final; ++aux1) {
        free(aux1-> titulo);
    }
    free(libros);
    free(enteros);
    return 0;
}

//Funciones genéricas
void recorre(void * arreglo, recorre_t iterador,size_t count, size_t size, t_type print_type){
    //Debe recorrer el arreglo utilizando el iterador especificado y mostrar el contenido del arreglo.
    (* iterador)(arreglo, count, size,print_type);
}

void forwardIterator(void * arreglo, size_t count, size_t size,  t_type print_type){
    void * iteratorbegin = begin(arreglo);

    while(iteratorbegin != NULL){
        (*print_type)(iteratorbegin);
        iteratorbegin = next(arreglo,iteratorbegin,count,size);
    }

}
void reverseIterator(void * arreglo, size_t count, size_t size,  t_type print_type){
    void * iteratorbegin = end(arreglo,count,size) - size;

    while(iteratorbegin != NULL){
        (*print_type)(iteratorbegin);
        iteratorbegin = prev(arreglo,iteratorbegin,count,size);
    }
}
void bidirectionalIterator(void * arreglo, size_t count, size_t size, t_type print_type){
    void * iteratorbegin = begin(arreglo);

    while(iteratorbegin != NULL){
        (*print_type)(iteratorbegin);
        iteratorbegin = next(arreglo,iteratorbegin,count,size);
    }

    printf("\nOther direction\n");
    iteratorbegin = end(arreglo,count,size) - size;

    while(iteratorbegin != NULL){
        (*print_type)(iteratorbegin);
        iteratorbegin = prev(arreglo,iteratorbegin,count,size);
    }
}

//Apuntador al primer elemento
void * begin(void * vector){
    return vector;
}
//Apuntador al último elemento
void * end(void * vector, size_t count, size_t size){
    return vector + (count*size);
}
//Apuntador al siguiente elemento
void * next(void * vector,void * actual, size_t count, size_t size){
    if(vector+(count*size) == actual+size){
        return NULL;
    } else {
        return actual + size;
    }
}
//Apuntador elemento anterior
void * prev(void * vector,void * actual, size_t count, size_t size){
    if(vector == actual){
        return NULL;
    } else {
        return actual - size;
    }
}

void printInt(void * pa)
{
    int * a = (int *)pa;
    printf(" %4d ",*a);
}
void printLibro(void * pa)
{
    libro * a = (libro *)pa;
    printf(" %4s ",a->titulo);
    printf(" %4d ",a->paginas);
}
