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

typedef struct{
    char * titulo;
    int paginas;
} libro;

typedef int (*t_compare)(void *, void *);
typedef void (*t_type)(void *);
typedef void (* recorre_t)(void *, size_t, size_t,t_type);

//MENU
typedef void (* menu)(void *,size_t , size_t, t_type);

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
    //Menu para elegir iterador
    int opc = -1;
    menu * opcs = (menu *) malloc(sizeof(menu)*3);

    *opcs = forwardIterator;
    *(opcs+1) = reverseIterator;
    *(opcs+2) = bidirectionalIterator;

    //Pedir cantidad de elementos al usuario
    int cantidad = 0;
    printf("¿Cuántos elementos deseas que tenga cada arreglo? : ");
    scanf("%d", &cantidad);

    //Crear arreglo de enteros random
    int * enteros = (int *) malloc(cantidad * sizeof(int));

    int * aux = enteros;
    int * last = enteros + cantidad;
    for (; aux < last; ++aux) {
        *aux = rand() % 100;
    }
    aux = enteros;
    last = enteros + cantidad;
    printf("\nElementos de arreglo de enteros: \n\n");
    for (; aux < last; ++aux) {
        printf(" %4d ", *aux);
    }

    //Crear arreglo de libros random
    libro * libros = (libro *) malloc(sizeof(libro)*cantidad);

    libro * aux1 = libros;
    libro * final = libros + cantidad;
    int i = 0;
    while(aux1 < final) {
        (libros + i )-> titulo  = (char *) malloc(sizeof(char)*25);
        strcpy((libros + i)-> titulo , "Libro genérico");
        (libros + i )-> paginas = rand() % 100;
        ++aux1;
        ++i;
    }
    printf("\n\nElementos de arreglo de libros: \n\n");
    aux1 = libros;
    for (; aux1 < final; ++aux1) {
        printf(" %4s ",aux1->titulo);
        printf(" %4d ",aux1->paginas);
    }

    //Pedir iterador
    while (opc != 0) {
        printf("\n\n¿Qué iterador deseas usar? \n 1.ForwardIterator 2.ReverseIterator 3.BidirectionalIterator 0. Salir\n\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opc);

        //Llamada a recorre dependiendo de la elección del usuario
        if (opc > 0 && opc <= 3) {
            printf("\n\nRecorriendo arreglo de números enteros.\n\n");
            recorre(enteros, &(*(opcs[opc-1])), cantidad, sizeof(*enteros), &printInt);
            printf("\n\nRecorriendo arreglo de estructuras del tipo Libro\n\n");
            recorre(libros, &(*(opcs[opc-1])), cantidad ,sizeof(*libros), &printLibro);
        }
    }
    printf("\n\n");

    //Liberar memoria
    aux1 = libros;
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
//Iterador normal
void forwardIterator(void * arreglo, size_t count, size_t size,  t_type print_type){
    void * iteratorbegin = begin(arreglo);

    while(iteratorbegin != NULL){
        (*print_type)(iteratorbegin);
        iteratorbegin = next(arreglo,iteratorbegin,count,size);
    }

}
//Iterador de reversa
void reverseIterator(void * arreglo, size_t count, size_t size,  t_type print_type){
    void * iteratorbegin = end(arreglo,count,size) - size;

    while(iteratorbegin != NULL){
        (*print_type)(iteratorbegin);
        iteratorbegin = prev(arreglo,iteratorbegin,count,size);
    }
}
//Iterador bidireccional
void bidirectionalIterator(void * arreglo, size_t count, size_t size, t_type print_type){
    void * iteratorbegin = begin(arreglo);

    while(iteratorbegin != NULL){
        (*print_type)(iteratorbegin);
        iteratorbegin = next(arreglo,iteratorbegin,count,size);
    }

    printf("\n\n");
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
//Imprimir enteros
void printInt(void * pa)
{
    int * a = (int *)pa;
    printf(" %4d ",*a);
}
//Imprimir libros
void printLibro(void * pa)
{
    libro * a = (libro *)pa;
    printf(" %4s ",a->titulo);
    printf(" %4d ",a->paginas);
}
