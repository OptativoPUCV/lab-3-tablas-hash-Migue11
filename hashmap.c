#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value){
    Pair * pair = createPair(key, value);
    int index = hash(key, map->capacity);
    while(map->buckets[index] != NULL){
        if(map->buckets[index]->key != NULL && is_equal(map->buckets[index]->key, key)){
            map->buckets[index]->value = value;
        }
        index = (index + 1) % map->capacity;
    }
    map->buckets[index] = pair;
    map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)

}


HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (Pair **)calloc(capacity, sizeof(Pair *)); // Aqui todas las casillas se inicializan en NULL
    map->size = 0; // Inicializamos el tamaño a 0
    map->capacity = capacity; // Inicializamos el tamaño completo del array a capacity
    map->current = -1; // Incializamos el current en -1 para que asi cuando lo reccoramos, tome el primer elemento correctamente
    return map;
}

void eraseMap(HashMap * map,  char * key){ 
    Pair * pair = searchMap(map, key);
    if(pair != NULL){
        pair->key = NULL;
        pair->value = NULL;
        map->size--;
    }

}

Pair * searchMap(HashMap * map,  char * key) {   
}

Pair * firstMap(HashMap * map){
    for (int i = 0; i < map->capacity; i++){
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;

}
Pair * nextMap(HashMap * map) {
    for (int i = map->current + 1; i < map->capacity; i++) { // empezamos desde el siguiente del current
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) { // verificamos que ese elemento no sea NULL
            map->current = i; 
            return map->buckets[i];
        }
    }
    return NULL; 
}
