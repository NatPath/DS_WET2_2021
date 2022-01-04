#ifndef _LIST_H_
#define _LIST_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "DynamicArray.h"


template<class T>
class ListNode{
    typedef struct std::shared_ptr<T> Value_ptr;
    Value_ptr value;
    ListNode<T>* next;
    ListNode<T>* prev;

    public:
    ListNode(){
        value=nullptr;
        next=nullptr;
        prev=nullptr;
        return;
    };
    ListNode(const Value_ptr value):value(value),next(nullptr),prev(nullptr){}
    ListNode(const ListNode<T>& to_copy){
        if(to_copy){
            T actual_value;
            if (to_copy.value){
                actual_value=*(to_copy.value);
            }
            value=std::make_shared<T>(actual_value);
            next=to_copy.next;
            prev=to_copy.prev;
        }
    }
     
    Value_ptr getValue() {
        return value;
    }

    ListNode<T>* getNext(){
        return next;
    }

    
    ListNode<T>* getPrev(){
        return prev;
    }
    void setNext(ListNode<T>* new_next){
        next=new_next;

    }
    void setPrev(ListNode<T>* new_prev){
        prev=new_prev;
    }

    void setValue(Value_ptr new_value) {
        value = new_value;
    }

    void connectNext(ListNode<T>* after){
        next = after;
        if(after){
            after->prev = this;
        }
    }

    void connectPrev(ListNode<T>* before){
        prev = before;
        if(before){
            before->next =this;
        }
    }
    void orphanateNode(){
        setNext(nullptr);
        setPrev(nullptr);
    }
    void printValue(){
        if (value){
            print(*value);
        }
    }
    ~ListNode(){
        value.reset();
    }

};

template<class T>
using shared_p = std::shared_ptr<T>;

template<class T>
class List{

    typedef struct std::shared_ptr<ListNode<T>> Node_ptr;
    ListNode<T>* root;

    public:

    List():root(nullptr){};
    List(ListNode<T>*  root):root(root){}
    /**
     * NOTE from 2021:
     * this constructor probably doesn't work. anyway, it was not used.
     * */
    List(const List<T>& another_list){
        ListNode<T>* itt=another_list.root;
        T new_val;
        root=new ListNode<T>();
        ListNode<T>* new_itt=root;
        while(itt){
            new_val=*(itt->getValue());
            ListNode<T>* next=new ListNode<T>(std::make_shared<T>(new_val));
            new_itt->connectNext(next);
            itt=itt->getNext();
            new_itt=new_itt->getNext();
        }

    }
    /**
     * 2021
     * list constructor from DynamicArray
     * */
    List(DynamicArray<T>& arr){
        if(arr.getSize()==0){
            root=nullptr;
            return;
        }
        T new_val=arr[0];
        root=new ListNode<T>(std::make_shared<T>(new_val));
        ListNode<T>* new_itt=root;
        for (int i=1; i<arr.getSize(); i++){
            new_val= arr[i];            
            ListNode<T>* next = new ListNode<T>(std::make_shared<T>(new_val));
            new_itt->connectNext(next);
            new_itt= new_itt->getNext();
        }
                
    }

    
    ListNode<T>*  find( T& value){
        ListNode<T>*  i=root;
        while(i){
            if (i->getValue()){
                if(*(i->getValue()) == value){
                    return i;
                }
            }
            i = i->getNext();
        }
        return nullptr;
    }

    ListNode<T>* getRoot() const{
        return root;
    }

    bool isEmpty(){
        return root==nullptr;
    }

    bool isInList(const T& value){
        return find(value)!=nullptr;
    }

    
    void add(T& to_add){
        //check unique?
        ListNode<T>* new_node = new ListNode<T>(std::make_shared<T>(to_add));
        add(new_node);
    }
    

    void add(ListNode<T>* to_add){
        //check unique?
        if (!root){
            root=to_add;
            return;
        }
        to_add->connectNext(root);
        root = to_add;
    }

    void setRoot(ListNode<T>* new_root){
        //delete root;
        root = new_root;
    }
    

    void remove(T& to_remove){
        ListNode<T>* i=root;

       while(i){
            if(*(i->getValue())==to_remove){
                if (i->getPrev()){
                    i->getPrev()->connectNext(i->getNext());
                    delete i;
                }
                else{
                    //deleting root
                    root=i->getNext();
                    if(root){
                        root->setPrev(nullptr);
                    }
                    delete i;
                }
                
                return;
            }
           i=i->getNext();
       }


    }

    ~List(){
        ListNode<T>* i = root;

        while (i)
        {
            ListNode<T>* next = i->getNext();
            delete i;
            i = next;
        }
    }
    void printList(){
        ListNode<T>* itt=root;        
        while (itt!=nullptr){
            itt->printValue();
            itt=itt->getNext();
        }
    }

    // new functions - 2021

    int calcLength(){
        ListNode<T>* itt=root;        
        int res=0;
        while (itt!=nullptr){
            res++;
            itt=itt->getNext();
        }
        return res;
    }
    
    int calcLength() const{
        ListNode<T>* itt=root;        
        int res=0;
        while (itt!=nullptr){
            res++;
            itt=itt->getNext();
        }
        return res;
    }

};

/** 
 * 2021
 * idea 2: 
 *  use an Array of T's .
 *  here we'll use the DynamicArray from hw2 of 2020 for ease of memory manegment.
 * */
template<class T>
DynamicArray<T> listToArray(const List<T>& list){
    int length= list.calcLength();
    ListNode<T>* itt=list.getRoot();
    DynamicArray<T> res(length);
    for (int i=0; i<length; i++){
        res[i]= *(itt->getValue());
        itt=itt->getNext();
    }
    return res;
}

/**
 * 2021
 * merge two ordered lists into one big ordered list
 *  in O(n1+n2)
 * 
 * 
 * array-method
 * NOTE: 
 * 1) list1 and list2 are not changed!
 * 2) assumes there is an <= operator for type T
 * */
template <class T>
List<T> mergeOrderedLists(const List<T>& list1,const List<T>& list2){
    DynamicArray<T> array1= listToArray(list1);
    DynamicArray<T> array2= listToArray(list2);

    int length1=list1.calcLength();
    int length2=list2.calcLength();
    int combined_length= length1+length2;

    int i1=0; // index in array1
    int i2=0; // index in array2

    //make a combined ordered array
    DynamicArray<T> combined_array(combined_length);
    for (int i=0 ; i<combined_length; i++){

        if (i1>=length1){
            combined_array[i]=array2[i2];
            i2++;
        }
        else if (i2>=length2){
            combined_array[i]=array1[i1];
            i1++;
        }
        if (i1<length1 && i2<length2){
            if (array1[i1]<=array2[i2]){
                combined_array[i]=array1[i1];
                i1++;
            }
            else{
                combined_array[i]=array2[i2];
                i2++;
            }
        }
    }

    //make combined_list of combined_array
    List<T> combined_list(combined_array);
    return combined_list;
}


#endif