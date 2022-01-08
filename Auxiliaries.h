#ifndef _AUX
#define _AUX
#include <exception>
#include <iostream>

//All the class definition needed:
class Player;
class PlayerSeat;
class Group;

// Auxilary functions used all over the program

template<class T>
const T& max(const T& a,const T& b){
    return a<b?b:a; 
}
template<class T>
void print(const T& to_print){
    std::cout<<to_print<<std::endl;
}

#endif 