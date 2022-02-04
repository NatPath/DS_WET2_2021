#ifndef _DARRAY_H
#define _DARRAY_H
#include <exception>
#include <stdexcept>
#include "Auxiliaries.h"

template <class T>
class DynamicArray{
    T* _data;
    int _size;
    int _counter;
    public:
    DynamicArray(int size):_size(size){
        _data=new T[size];
        _counter = 0;
    }
    //c'tor with default value
    DynamicArray(int size,T default_value){
        _size=size;
        _data=new T[size];
        for (int i=0;i<_size;i++){
            _data[i]=default_value;
        }
    }
    //copy c'tor
    DynamicArray(DynamicArray<T>& to_copy){
        _size=to_copy.getSize();
        T* temp_data;
        int temp_size;
        try{
            temp_data=new T[_size];
            temp_size=to_copy.getSize();
            for (int i=0;i<temp_size;i++){
                temp_data[i]=to_copy[i];
            }
        }
        catch(std::exception& e){
            delete[] temp_data;
            throw std::runtime_error("Failed to copy Dynamic Array");
        }
        _counter=to_copy._counter;
        _size=temp_size;
        _data=temp_data;
    }
    /**
     * 2021
     * copy c'tor for const
     * */
    DynamicArray(const DynamicArray<T>& to_copy){
        _size=to_copy.getSize();
        T* temp_data;
        int temp_size;
        try{
            temp_data=new T[_size];
            temp_size=to_copy.getSize();
            for (int i=0;i<temp_size;i++){
                temp_data[i]=to_copy[i];
            }
        }
        catch(std::exception& e){
            delete[] temp_data;
            throw std::runtime_error("Failed to copy Dynamic Array");
        }
        _counter=to_copy._counter;
        _size=temp_size;
        _data=temp_data;
    }

    DynamicArray& operator=(DynamicArray<T>& to_assign){
        T* assign_data;
        T* temp_data;
        try{
            int new_size = to_assign.getSize();
            assign_data = to_assign.getData();
            temp_data = new T[new_size];
            
            for(int i = 0; i<new_size;i++){
                temp_data[i] = assign_data[i]; 
            }

            delete[] _data;
            _size = new_size;
            _counter = to_assign.getCounter();
            _data = temp_data;
            
        }
        catch(...){
            delete[] temp_data;
        }
        return *this;
    }

    void push(T new_value){
        if (_counter+1<_size){
            _data[_counter++] = new_value;
        }
        else{
            expand();
            _data[_counter++] = new_value;
        }
        
    }

    void expand(){
        T* new_data;
        try{
            new_data = new T[_size * 2];
            for (int i = 0; i < _size; i++)
            {
                new_data[i] = _data[i];
            }
            delete[] _data;
            _size = _size*2;
            _data = new_data;
        }
        catch(...){
            throw std::runtime_error("Failed to expand Dynamic Array");  
            delete[] new_data;          
        }


    }
    //Getters
    int getSize() const{
        return _size;
    }

    int getCounter() const{
        return _counter;
    }


    T* getData(){
        return _data;
    }

    T& operator[](int index){
        if (index<_size){
            return _data[index];
        }
        else{
            throw std::runtime_error("Out of range index");
        }
    }
    /**
     * 2021
     * allows const dynamicArrays
     * 
     * */
    T& operator[](int index) const{
        if (index<_size){
            return _data[index];
        }
        else{
            throw std::runtime_error("Out of range index");
        }
    }

    ~DynamicArray<T>(){
        delete[] _data;
    }
    void printArray(){
        for (int i=0;i<_counter;i++){
            print(_data[i]);
        }
    }

};
#endif