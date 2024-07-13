

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct Nodo{
    T valor;
    Nodo<T>* next;
    Nodo(T valor, Nodo<T>* next): valor(valor), next(next){}
};

template<typename T>
class MasTarde{
private:
    int size_cola;       // Numero de elementos en la cola
    Nodo<T>* nodo_front; // Puntero al frente de la cola
    Nodo<T>* nodo_back;  // Puntero al final de la cola
public:
    MasTarde();
    bool empty();  // Retorna true si la cola esta vacia
    int size();    // Retorna el numero de elementos en la cola
    T front();     // Retorna el elemento en el frente de la cola
    T back();      // Retorna el elemento en el final de la cola
    void push(T);  // Agrega un elemento al final de la cola
    void pop();    // Elimina el elemento en el frente de la cola
};

// El constructor inicializa los atributos de la clase
// donde 'nodo_front' y 'nodo_back' apuntan a NULL y 'size_cola' es 0
template<typename T>
MasTarde<T>::MasTarde(): size_cola(0), nodo_front(NULL), nodo_back(NULL){}

// El metodo empty() retorna true si la cola esta vacia
// y false en caso contrario (size_cola == 0)
template<typename T>
bool MasTarde<T>::empty(){
    return size_cola == 0;
}

// El metodo size() retorna el numero de elementos en la cola
template<typename T>
int MasTarde<T>::size(){
    return size_cola;
}

// El metodo front() retorna el elemento
// en el frente de la cola
template<typename T>
T MasTarde<T>::front(){
    return nodo_front->valor;
}

// El metodo back() retorna el elemento
// en el final de la cola
template<typename T>
T MasTarde<T>::back(){
    return nodo_back->valor;
}


template<typename T>
void MasTarde<T>::push(T e){
    Nodo<T>* nuevo = new Nodo<T>(e, NULL);
    if(empty()){
        nodo_front = nuevo;
    }else{
        nodo_back->next = nuevo;
    }
    nodo_back = nuevo;
    size_cola++;
}

template<typename T>
void MasTarde<T>::pop(){
    if(!empty()){
        Nodo<T>* tmp = nodo_front;
        nodo_front = nodo_front->next;
        delete tmp;
        size_cola--;
        if(empty()){
            nodo_back = NULL;
        }
    }
}









#ifndef PROYECTO_PROGRAMACION3_HISTORIAL_H
#define PROYECTO_PROGRAMACION3_HISTORIAL_H

#endif //PROYECTO_PROGRAMACION3_HISTORIAL_H
