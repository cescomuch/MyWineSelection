#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include "myexception.h"


//Template di un array dinamico creato ad hoc

template <class T>
class Container{
private:
    unsigned int size;
    unsigned int capacity;
    T* buffer;
    void  reserve();

public:
    class iterator{
        friend class Container<T>;
    private:
        T* punt;
        iterator(T*);
    public:
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

        T& operator* ();
        T* operator-> ();

        iterator& operator++(); //ho scelto di fare solo l'incremento prefisso, e non il postfisso
        iterator& operator--(); //stessa scelta anche per il decremento
        iterator &operator+(unsigned int);
        iterator &operator-(unsigned int);
    };

    class const_iterator{
        friend class Container<T>;
    private:
        const T* cpunt;
        const_iterator(T*);
    public:
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

        const T& operator*() const;
        const T* operator->() const;

        const_iterator& operator++();
        const_iterator& operator--();
        const_iterator &operator+(unsigned int);
        const_iterator &operator-(unsigned int);
    };

     //due costruttori con i parametri e un costruttore di copia
     Container(unsigned int=2);
     Container(const T&, unsigned int=2);
     Container(const Container<T>&);
     ~Container();
     Container<T>& operator=(const Container<T> &);

    T& operator[] (unsigned int);
    bool operator== (const Container<T>&) const;

    unsigned int getSize() const; // ritorna il numero degli elementi presenti nel vector
    unsigned int getCapacity()const; //ritorna la capacita' del vector
    void clear();
    bool isEmpty() const;
    T& front();
    T& back();
    void push_back(const T&);
    void pop_back();

    //tre metodi erase:  uno per indice, uno per intervallo di indici, uno per elemento T
    void erase(unsigned int=0);
    void erase(unsigned int, unsigned int);
    void erase(T);
    T& at(unsigned int);

    //iteratori
    iterator begin() const;
    iterator end() const;

    //const_iterator
    const_iterator cbegin() const;
    const_iterator cend() const;
};









//DEFINIZIONI (secondo il modello di compilazione per inclusione)

template <class T>
Container<T>::Container(unsigned int s) : size(0), capacity(s), buffer(new T[s]) {}

template <class T>
Container<T>::Container(const T& t, unsigned int s): size(0), capacity(s), buffer(new T[s]){
    for(int i=0; i<capacity; ++i)
        buffer[i]=t;}

template <class T>
Container<T>::Container(const Container<T>& t): size(t.size), capacity(t.capacity), buffer(new T[t.capacity]){
    for(unsigned int i=0; i<size; ++i)
        buffer[i]=t.buffer[i];}

template <class T>
Container<T>::~Container<T>() {if(buffer) delete[] buffer;}

template <class T>
Container<T>& Container<T>::operator=(const Container<T>& t){
    if(this!= &t) {
        delete[] buffer;
        size=t.size;
        capacity=t.capacity;
        buffer=new T[capacity];
        for(unsigned int i=0; i<size; ++i)
            buffer[i]=t.buffer[i];
    }
    return *this;}

template <class T>
T& Container<T>::operator[](unsigned int index){
    return buffer[index];}

template <class T>
bool Container<T>::operator==(const Container<T>& t) const {
    bool equal = (t.size== size && t.capacity== capacity);
    for (auto it1= cbegin(), it2= t.cbegin(); it1!=cend() && equal; ++it1, ++it2) {
        if(*it1!=*it2) equal=false;
    }
    return equal;
}

template <class T>
unsigned int Container<T>::getSize() const {return size;}

template <class T>
unsigned int Container<T>::getCapacity()const {return capacity;}

template <class T>
void Container<T>::clear(){
    delete [] buffer;
    buffer=new T[2];
    capacity=2;
    size=0;}

template <class T>
bool Container<T>::isEmpty() const {return size==0;}

template <class T>
T& Container<T>::front() {return buffer[0];}


template<class T>
T& Container<T>::back() {return buffer[size-1];}

template <class T>
void Container<T>::reserve(){
    //ricrea il buffer con la dimensione doppia rispetto a quella attuale
    unsigned int newCapacity=capacity*2;
    T* newBuffer=new T[newCapacity];

    for(unsigned int i=0; i<size; ++i){
        newBuffer[i]= buffer[i];}

    capacity=newCapacity;
    delete [] buffer;
    buffer=newBuffer;}

template <class T>
void Container<T>::push_back(const T& t){
    if (!(size<capacity))
        reserve();

    buffer[size++]=t;}

template <class T>
void Container<T>::pop_back() { size>0 ? --size : 0;}

template <class T>
void Container<T>::erase(unsigned int index){
    if(index>size-1) throw MyException("Index is out of range");
    for(unsigned int i=index; i<size-1; ++i )
        buffer[i]= buffer[i+1];

    size--;}

template <class T>
void Container<T>::erase(unsigned int start, unsigned int end){
    if(start<0 || end<0||start>size-1 || end>size-1 || start> end ) throw MyException("Indexes are out of bounds");

    unsigned int i=start, j=1;

    for(; i<size; ++i, ++j)
        buffer[i]=buffer[end+j];

    size=size-((end-start)+1);}

template <class T>
void  Container<T>::erase(T t) {
    unsigned int index=0;
    for(auto it=begin(); (*it)!=t && it!=end(); ++index, ++it);

    return erase(index);}

template <class T>
T& Container<T>::at(unsigned int index){
    if(index<0 || index>size-1){
        throw MyException("The index is out of range");}

    return buffer[index];}










//ITERATOR

template <class T>
typename Container<T>::iterator Container<T>::begin() const {return iterator(buffer);}

template <class T>
typename Container<T>::iterator Container<T>::end() const {return iterator(buffer+(size));}

template <class T>
typename Container<T>::const_iterator Container<T>::cbegin() const {return const_iterator(buffer);}

template <class T>
typename Container<T>::const_iterator Container<T>::cend() const {return const_iterator(buffer+(size));}

template <class T>
Container<T>::iterator::iterator(T* t) : punt(t) {}

template <class T>
bool Container<T>::iterator::operator!=(const iterator& it) const {return punt!=it.punt;}

template <class T>
bool Container<T>::iterator::operator==(const iterator& it) const {return punt==it.punt;}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator++() {
    if(punt) punt++;
    return *this;}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator--(){
    if(punt) punt--;
    return *this;}

template <class T>
T& Container<T>::iterator::operator*() {return *punt;}

template <class T>
T* Container<T>::iterator::operator->() {return punt;}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator+(unsigned int x){
    if(punt) punt=punt+x;
    return *this;
}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator-(unsigned int x){
    if(punt) punt=punt-x;
    return *this;}



//CONST ITERATOR


template <class T>
Container<T>::const_iterator::const_iterator(T* t) : cpunt(t){
}
template <class T>
bool Container<T>::const_iterator::operator!=(const const_iterator& it) const {return cpunt!=it.cpunt;}

template <class T>
bool Container<T>::const_iterator::operator==(const const_iterator& it) const {return cpunt==it.cpunt;}

template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++() {
    if(cpunt) cpunt++;
    return *this;}

template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator--() {
    if(cpunt) cpunt--;
    return *this;}

template <class T>
const T& Container<T>::const_iterator::operator*() const {return *cpunt;}

template <class T>
const T* Container<T>::const_iterator::operator->() const {return cpunt;}

template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator+(unsigned int x){
    if(cpunt) cpunt=cpunt+x;
    return *this;}

template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator-(unsigned int x){
    if(cpunt) cpunt=cpunt-x;
    return *this;
}

#endif // CONTAINER_H
