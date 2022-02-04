#ifndef _PAIR_H
#define _PAIR_H
#include <iostream>

template <typename KEY, typename VALUE>
class Pair{
    KEY key;
    VALUE value;
    
    public:
    Pair(){};
    Pair(KEY key,VALUE value):key(key),value(value){};
    Pair(Pair& to_copy)=default;
    Pair(const Pair& to_copy)=default;
    Pair& operator=(Pair& copy)=default;
    Pair& operator=(const Pair& copy)=default;
    KEY getKey() const{
        return key;
    }
    VALUE getValue() const{
        return value;
    }
    void setKey(KEY& new_key){
        key=new_key;
    }
    void setValue(VALUE& new_value){
        value=new_value;
    }
    bool operator==(const Pair<KEY,VALUE>& compare) const{
        return key==compare.getKey() && value==compare.getValue();
    }
    bool operator!=(const Pair<KEY,VALUE>& compare) const{
        return !(compare==*this);
    }
    bool operator>(const Pair<KEY,VALUE>& compare) const{
        return key>compare.getKey();
    }
    bool operator>=(const Pair<KEY,VALUE>& compare) const{
        return key>=compare.getKey();
    }
    bool operator<(const Pair<KEY,VALUE>& compare) const{
        return key<compare.getKey();
    }
    bool operator<=(const Pair<KEY,VALUE>& compare) const{
        return key<=compare.getKey();
    }
    //friend std::ostream& operator<<(std::ostream& os,const Pair<KEY,VALUE>& pair);
    
};
template <typename KEY, typename VALUE>
std::ostream& operator<<(std::ostream& os,const Pair<KEY,VALUE>& pair){
    os<<"~~Printing Pair~~"<<std::endl;    
    os<<"Key:" <<pair.getKey()<<std::endl;    
    os<<"Value:" <<pair.getValue()<<std::endl;    
    os<<"~~~~~~~~~~~~~~~~~~~~"<<std::endl;    
    return os;
}
#endif