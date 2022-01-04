#ifndef _HASH_TABLE_H
#include <exception>
#include "List.h"
#include "DynamicArray.h"

template<class T>
class HashTable{

   List<T>* _data_chains;
   //DynamicArray<List<T>> _data_chains;
   int _size;
   int _counter;
   
   double getOverLoadFactor() const{
       return (double)_counter/(double)_size;       
   }

   int hash_function(T& to_hash) const{
       int key=to_hash.get_id();
       return hash_id(key);
   } 

   int hash_id(int id) const{
       return id%_size;
   } 

   int hash_function_modified(T& to_hash,int size) const{
       int key=to_hash.get_id();
       return key%size;
   } 
   //expands the hashtable size by 2 and rehashes all the elements
   void expand(){
       List<T>* temp_data;
       int old_size=_size;
       _size=_size*2;
       try{
           temp_data=new List<T>[_size];
           //rehash all elements
           for (int i = 0; i < old_size; i++)
           {
               //iterate over a chain
               ListNode<T>* itt= _data_chains[i].getRoot();
               ListNode<T>* next;
               while(itt){
                    int key=hash_function(*(itt->getValue()));
                    //takes node out of original list
                    next = itt->getNext();
                    if(next!=nullptr){
                        next->setPrev(nullptr);
                    }
                    _data_chains[i].setRoot(next);
                    //let the node know about it                    
                    itt->orphanateNode();
                    //transfer node to new list
                    temp_data[key].add(itt);
                    itt = _data_chains[i].getRoot();
               }
           }
           delete[] _data_chains;
           _data_chains=temp_data;
       }
       catch(...){
           _size=old_size;
           delete[] temp_data;
       }
   }
   void printTable(){
       for (int i=0;i<_size;i++){
           print(i);
           _data_chains[i].printList();
       }
   }
   void expand2(){
        HashTable* new_hash_table(_size*2);
        for (int i=0;i<_size;i++){
            new_hash_table->insert();
        }
        this=new_hash_table;
   }
   void contract(){
       List<T>* temp_data;
       int old_size=_size;
       _size=_size/2;
       try{
           temp_data=new List<T>[_size];
           //rehash all elements
           for (int i = 0; i < old_size; i++)
           {
               //iterate over a chain
               ListNode<T>* itt= _data_chains[i].getRoot();
               ListNode<T>* next;
               while(itt){
                    int key=hash_function(*(itt->getValue()));
                    //takes node out of original list
                    next = itt->getNext();
                    if(next!=nullptr){
                        next->setPrev(nullptr);
                    }
                    _data_chains[i].setRoot(next);
                    //let the node know about it                    
                    itt->orphanateNode();
                    //transfer node to new list
                    temp_data[key].add(itt);
                    itt = _data_chains[i].getRoot();
               }
           }
           delete[] _data_chains;
           _data_chains=temp_data;
       }
       catch(...){
           _size=old_size;
           delete[] temp_data;
       }
   }
   public:
   HashTable(int size=2){
       _size=size;
       _counter=0;
       _data_chains=new List<T>[_size];
   }
   ListNode<T>* find(T& to_find){
      int table_index=hash_function(to_find);
       return _data_chains[table_index].find(to_find);
   }

   bool insert(T& to_insert){
       if (find(to_insert)!=nullptr){
           return false;
       }
       else{
           int key=hash_function(to_insert);
           _data_chains[key].add(to_insert);
           _counter++;
           if (getOverLoadFactor()>2){
               expand();
           }
           return true;
       }
   }
   bool insert2(ListNode<T>& to_insert){
       if (find(to_insert.getValue().get)!=nullptr){
           return false;
       }
       else{
           int key=hash_function(to_insert.getValue().get);
           _data_chains[key].add(to_insert);
           _counter++;
           return true;
       }
   }

   void remove(T& to_remove){
       _data_chains[hash_function(to_remove)].remove(to_remove);
       _counter--;
       if (getOverLoadFactor()<0.5){
           contract();
       }
   }

   ~HashTable(){
       expand();
       delete[] _data_chains;
   }
};

#endif