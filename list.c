#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// 1. Programe la función List* createList(), la cual retorna el puntero del tipo de dato List con sus valores inicializados en NULL.
// Recuerda reservar memoria al puntero usando malloc o calloc.

List * createList() {
    //se reserva memoria para la lista
    List *lista = (List*)malloc(sizeof(List));
    //se inicializan valores de la lista
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

// 2. Programe las funciones void * firstList(List * list) y void * nextList(List * list).
//   - La primera retorna el dato del primer nodo de la lista (head) y actualiza el current para que apunte a ese nodo.
//   - La segunda función retorna el dato del nodo a continuación del current y actualiza el current para que apunte a ese nodo.

void * firstList(List * list) {
    //se revisa si la lista es valida
    if (list == NULL)return NULL;
    //se revisa si el primer nodo es valido
    if (list->head == NULL)return NULL;
    //se crea un nodo que apunta al primer nodo de la lista
    Node* auxNode = list->head;
    //se crea un dato que apunta al dato dentro del primer nodo
    void* dato = list->head->data;
    //el nodo actual se actualiza al primer elemento de la lista
    list->current = auxNode;
    return dato;
}

void * nextList(List * list) {
    //se verifica si la lista es valida o si el actual de la lista es valido o si existe algo despues del actual
    if (list == NULL || list->current == NULL || list->current->next == NULL)return NULL;
    //se crea un nodo que apunta al siguiente del nodo actual
    Node* siguiente = list->current->next;
    //se crea dato que apunta al dato almacenado en el nodo siguiente al actual
    void* dato = siguiente->data;
    //nodo actual es el que antes fue siguiente 
    list->current = siguiente;
    return dato;
}

// 3. Programe las funciones void * lastList(List * list) y void * prevList(List * list).
//   - La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
//   - La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.

void * lastList(List * list) {
    //si la lista no existe
    if (list == NULL)return NULL;
    //si el ultimo nodo es valido
    if (list->tail == NULL)return NULL;
    //se crea variable dato que apunta al dato del ultimo nodo
    void* dato = list->tail->data;
    //se actualiza la posicion actual al final de la lista
    list->current = list->tail;
    return dato;
}

void * prevList(List * list) {
    //se verifica si la lista es calida
    if (list == NULL)return NULL;
    //se verifica si el actual existe o el actual es la cabeza (sino no hay anterior) o si el anterior de la lista es valido
    if ((list->current == NULL) || (list->current == list->head) || (list->current->prev == NULL))return NULL;
    //se crea dato que apunta al contenido del nodo anterior al actual
    void* dato = list->current->prev->data;
    //el nodo actual ahora es el anterior
    list->current = list->current->prev;
    return dato;
}

// 4. Programe la función void pushFront(List * list, void * data), la cual agrega un dato al comienzo de la lista.
// Puede utilizar la función Node* createNode(void * data) la cual crea, incializa y retorna un nodo con el dato correspondiente.

void pushFront(List * list, void * data) {
    //si la lista es nula
    if (list == NULL)return;
    //se crea nuevo nodo con la funcion, con el dato correspondiente
    Node* newNode = createNode(data);
    //si es que la lista estaba vacia se mete el nuevo nodo y seria la cabeza y cola
    if (list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
        return;
    }
    //recordar que next en el nodo no en el prev del nodo
    //el siguiente del nuevo nodo apunta a la cabeza
    newNode->next = list->head;
    //ahora la cabeza es el nuevo nodo
    list->head = newNode;
    //ahora la cabeza (nuevo nodo) su prev apunta a NULL
    list->head->prev = NULL;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

// 5. Programe la función void pushCurrent(List * list, void* data), la cual agrega un dato a continuación del nodo apuntado por list->current.

void pushCurrent(List * list, void * data) {
    //si la lista es nula
    if (list == NULL)return;
    //se crea nuevo nodo para insertar despues del current(actual)
    Node* newNode = createNode(data);
    //si la lista esta vacia, se pega dentro el nuevo nodo en cabeza ycola
    if (list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
        return;
    }
    //si el actual esta al final de la lista
    if (list->current == list->tail){
        //el prev del nuevo nodo apunta al actual
        newNode->prev = list->current;
        //el siguiente al actual apunta al nuevo nodo
        list->current->next = newNode;
        //la cola apunta al nuevo nodo
        list->tail = newNode;
        //el siguiente del nuevo nodo es nulo
        list->tail->next = NULL;
        return;
    }
    //##si hay mas de un dato en la lista##
    //el prev del nuevo nodo apunta al nodo actual
    newNode->prev = list->current;
    //el siguiente del nuevo nodo apunta al que viene despues del actual
    //aqui nuevo nodo ya tiene apuntando atras y adelante
    newNode->next = list->current->next;
    //el prev del siguiente al nodo actual apunta al nuevo nodo
    list->current->next->prev = newNode;
    //el siguiente al nodo actual apunta al nuevo nodo
    list->current->next = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// 6. Programe la función void* popCurrent(List * list), la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el dato del nodo eliminado.
// Nota: El current debe quedar apuntando al nodo siguiente del eliminado.

void * popCurrent(List * list) {
    if (list == NULL)return NULL;
    if (list->current == NULL)return NULL;
    void* dato = list->current->data;
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    list->current = list->current->next;
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
