#ifndef _AVL_H_
#define _AVL_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"



typedef enum Side {R,L,N} Side;
enum Order {PRE,POST,IN};

template<class KEY,class VAL>
class AVL_NODE{
    typedef struct std::shared_ptr<AVL_NODE<KEY,VAL>> Node_ptr;
    KEY key;
    VAL value;
    Node_ptr left;
    Node_ptr right;
    Node_ptr parent;
    int height;
    int rank;

    public:
    AVL_NODE(const KEY& key,const VAL& value):key(key),value(value),left(nullptr),right(nullptr),parent(nullptr),height(0),rank(1){}
    ~AVL_NODE()=default;
   

    //getters
    VAL& getValue(){
        return value;
    }
    const KEY& getKey() const{
        return key;
    }
    Node_ptr getRight() const{
        return right;
    }
    Node_ptr getLeft() const{
        return left;
    }
    Node_ptr getParent() const{
        return parent;
    }
    int getHeight() const{
        return height;
    }
    int getRank() const{
        return rank;
    }
    //setters
    void setValue(const VAL& new_value){
        value=new_value;
    }
    void setKey(const KEY& new_key){
        key=new_key;
    }
    void setRight(Node_ptr new_right){
        right=new_right;
    }
    void setLeft(Node_ptr new_left){
        left=new_left;
    }
    void setParent(Node_ptr new_parent){
        parent=new_parent;
    }
    void setHeight(int new_height){
        height=new_height;
    }
    void setRank(int new_rank){
        rank=new_rank;
    }

    //Height functions
    /*
    * Gets a vertex of a tree and returns the height of it
    * The height of a vertex is calculated by the max height of its children +1
    * Input Expectations:
    *   left-child and right-child have correct heights already 
    */
    int calcHeight(Node_ptr parent_node) const{

        int left_height=-1;
        int right_height=-1;
        Node_ptr left= parent_node->getLeft();
        if (left!=nullptr){
            left_height=left->height;
        }
        Node_ptr right= parent_node->getRight();
        if (right!=nullptr){
            right_height=right->height;
        }
        return max(left_height,right_height)+1;
    }
    /*
    * Member function of AVL_NODE, does the same as calcHeight(Node_ptr):
    */
    int calcHeight() const{
        int left_height=-1;
        int right_height=-1;
        if (left!=nullptr){
            left_height=left->height;
        }
        if (right!=nullptr){
            right_height=right->height;
        }
        return max(left_height,right_height)+1;

    }
    //Calculates height and sets new height to be it
    void updateHeight(){
        height=this->calcHeight();
    }
    //Rank functions
    /**
     * 
     * */
    int calcRank(){
        int left_rank=0;
        int right_rank=0;
        if (left!=nullptr){
            left_rank=left->rank;
        }
        if (right!=nullptr){
            right_rank=right->rank;
        }
        return right_rank+left_rank+1;
    }
    void updateRank(){
        rank=this->calcRank();
    }
    void updateAttributes(){
        this->updateHeight();
        this->updateRank();
    }
    // print functions- expects printable type
    void printValue() const{
        print("value:");
        print(value);
    }
    void printKey() const{
        print("key:");
        print(key);
    }

};
/*
* AREA_NODE functions:
*/
template <typename KEY,typename VAL>
using Node_ptr=std::shared_ptr<AVL_NODE<KEY,VAL>>;

template<class KEY,class VAL>
void printNode(Node_ptr<KEY,VAL>& node) {
    std::cout<<node->getKey()<<" BF: "<<balance_factor(node)<<" Height: "<< node->getHeight()<<std::endl;
}

/**
 * swapNodes-
 *   gets 2 nodes and swaps their places, after doing so the function also switches their names 
 * */  

template <typename KEY,typename VAL>
void swapNodes(Node_ptr<KEY,VAL>& node1,Node_ptr<KEY,VAL>& node2){
    Node_ptr<KEY,VAL> temp_left1=node1->getLeft();
    Node_ptr<KEY,VAL> temp_right1=node1->getRight();
    Node_ptr<KEY,VAL> temp_parent1=node1->getParent();

    Node_ptr<KEY,VAL> temp_left2=node2->getLeft();
    Node_ptr<KEY,VAL> temp_right2=node2->getRight();
    Node_ptr<KEY,VAL> temp_parent2=node2->getParent();

    Side side1=childSide(temp_parent1,node1);
    Side side2=childSide(temp_parent2,node2);

    //corner cases
    if (temp_left1==node2 || temp_right1==node2){
        //node1 is the parent of node2
        connectNodes(node1,temp_left2,L);
        connectNodes(node1,temp_right2,R);


        connectNodes(temp_parent1,node2,side1);
        if (side2==L){
            connectNodes(node2,temp_right1,R);
        }
        else{
            connectNodes(node2,temp_left1,L);
        }

        connectNodes(node2,node1,side2);
    }
    else if (temp_left2==node1 || temp_right2==node1){
        //nodes2 is the parent of node1
        connectNodes(node2,temp_left1,L);
        connectNodes(node2,temp_right1,R);

        connectNodes(temp_parent2,node1,side2);
        if (side1==L){
            connectNodes(node1,temp_right2,R);
        }
        else{
            connectNodes(node1,temp_left2,L);
        }

        connectNodes(node1,node2,side1);
    }
    else{
        connectNodes(temp_parent2,node1,side2);
        connectNodes(node1,temp_left2,L);
        connectNodes(node1,temp_right2,R);

        connectNodes(temp_parent1,node2,side1);
        connectNodes(node2,temp_left1,L);
        connectNodes(node2,temp_right1,R);
    }
    //change back the names
    Node_ptr<KEY,VAL> temp=node1;
    node1=node2;
    node2=temp;
}
// frees the memory of a single node
template <typename KEY,typename VAL>
void freeNode(Node_ptr<KEY,VAL>& to_delete){
    Side side=childSide(to_delete->getParent(),to_delete);
    Node_ptr<KEY,VAL> parent = to_delete->getParent();
   
    connectNodes(parent,Node_ptr<KEY,VAL>(nullptr),side);
     to_delete.reset();
}

//Given children with correct heights, returns balance factor (left.height - right.height)
template <typename KEY,typename VAL>
int balance_factor(Node_ptr<KEY,VAL> parent_node) {
    if (parent_node==nullptr){
        return 0;
    }
    int left_height=-1;
    int right_height=-1;
    Node_ptr<KEY,VAL> left= parent_node->getLeft();
    Node_ptr<KEY,VAL> right= parent_node->getRight();
    if (left!=nullptr){
        left_height=left->getHeight();
    }
    if (right!=nullptr){
        right_height=right->getHeight();
    }
    return left_height-right_height;
}

template<class KEY,class VAL>
class AVL_Tree{
    //fields if splitting
    typedef struct std::shared_ptr<AVL_NODE<KEY,VAL>> Node_ptr;
    Node_ptr root;

    
    //given correct height of childrens, calculates the height of the parent
    public:
    AVL_Tree():root(nullptr){}
    //AVL_Tree(Node_ptr root):root(root){} // **2021** this one might not work, 
    ~AVL_Tree();
    /**
     * 2021
     * might be a bad idea.. use only if you know what you're doing.
     * */
    void setRoot(Node_ptr new_root){
        root.reset();
        root=new_root;
    }
    /**
     * 2021
     * copy c'tor
     * just copies the root. no deep copy or anything
     * */
    AVL_Tree(const AVL_Tree& to_copy){
        root=to_copy.getRoot();
    }
    /**
     * 2021
     * assignment operator
     * just assign the root
     * */
    AVL_Tree& operator=(AVL_Tree<KEY,VAL>& to_assign ){
        root=to_assign.getRoot();
        return *this;
    }

    Node_ptr getRoot() const{return root;}

    VAL getRootValue() const{
        if(root==nullptr){
            //default values when the root is null(?)
            return VAL();
        }
        return root->getValue();
    }
    KEY getRootKey() const{
        if(root==nullptr){
            //default values when the root is null(?)
            return KEY();
        }
        return root->getKey();
    }

    
     /*
        returns the number of nodes in the tree, which is the rank of its root
    */
    int getNumNodes(){
        if(root==nullptr){
            return 0;
        }
        return root->getRank();
    }
    
    /*
    * Gets a key, searches for the vertex in the AVL with the key. 
    * if a vertex with the same key is found , returns it.
    * otherwise, returns the last vertex on the search path.(note: it must be a leaf or with only one child)
    */
    Node_ptr findLastOfSearchPath(const KEY& to_find) const{
        Node_ptr i=root;
        if(i==nullptr){
            return nullptr;
        }
        do{
            if (i->getKey()==to_find){
                return i;
            }
            if (i->getKey()>to_find){
                
                if (i->getLeft()!=nullptr){
                    i=i->getLeft();
                }
                else {
                    return i;
                }
            }
            else{
                if (i->getRight()!=nullptr){
                    i=i->getRight();
                }
                else {
                    return i;
                }
            }

        } while (true);
        
    }
    /*
    * InsertNode:
    *   create a new Node and enter it into the tree. returns wether the insertion was successful or not.
    * 1)  searching for the place it should apear. - if already exists return false
    * 2)  connecting it in the correct spot.
    * 3)  update heights in the search path and do a roll if needed 
    * O(log(n))
    */
    bool insertNode(const KEY& key_insert,const VAL& val_insert){
        // search for the key in the tree O(log(n))
        Node_ptr found_spot=findLastOfSearchPath(key_insert);
        if (found_spot==nullptr){
            //first node in the tree
            root=std::make_shared<AVL_NODE<KEY,VAL>>(key_insert,val_insert);
            return true;
        }
        if (found_spot->getKey()==key_insert){
            //value is already in the tree
            return false;
        }
        //
        
        //creates the new node and connects it
        Node_ptr i=std::make_shared<AVL_NODE<KEY,VAL>>(key_insert,val_insert);
        if(found_spot->getKey() < key_insert){
            connectNodes(found_spot,i,R);               
        }
        else{
            connectNodes(found_spot,i,L);
        }
        i->setHeight(0);

        //update Ranks in the search path loop
        Node_ptr itt=i;
        //O(log(n) - iteration over the search path
        while (itt!=nullptr){
            itt->updateRank();
            itt=itt->getParent();
        }
        itt.reset();
        //
        //iterates over the search path and update the heights and rank accordingly, checks balance factor and do rolls accordingly
        //O(log(n)) - iteratation over the search path is log(n) , rolls are O(1)
        Node_ptr parent = i->getParent();
        int bf;
        while(i!=root){ 
            bf=balance_factor(parent);
            //?
            parent->updateHeight();
            //
            if(bf>1){
                //left
                if(balance_factor(i)>0){
                    //left left
                    roll_ll(parent);

                }
                else{
                    // left right
                    roll_lr(parent);
                }
                root=getRootClimb(parent);


                return true;

            }
            else if(bf<-1){
                //right
                if(balance_factor(i)<0){
                    //right right
                    roll_rr(parent);
                }
                else{
                    // right left
                    roll_rl(parent);
                }
                root=getRootClimb(parent);
                return true;
            }
            i=parent;
            parent=i->getParent();
        }
        

        return true;
    }
    
    /*
    * DeleteNode:
    *   delete the vertex with the given key from the tree. returns wether the deletion was successful/
    *   
    */
    bool deleteNode(const KEY& key_to_delete){
        Node_ptr found_spot=findLastOfSearchPath(key_to_delete);
        if (root==nullptr||found_spot->getKey()!=key_to_delete){
            //value searched was not found
            return false;
        }
        Node_ptr i=found_spot;// define an iterator and assign it the found spot

        //find a subsitute to the node removed, we're looking for the minimum node to its right, or the maximum node to its left
        //O(log(n))
        Node_ptr parent_of_found=found_spot->getParent();
        Node_ptr substitute(nullptr);
        Node_ptr parent_of_subsitute(nullptr);
        if (isLeaf(found_spot)){
            if (found_spot==root){
                root.reset();
                return true;
            }
            freeNode(found_spot);
            i=parent_of_found;
        }
        else if (found_spot->getRight()!=nullptr){
            substitute= findMinNode(i->getRight());
            swapNodes(substitute,found_spot);
            i=substitute->getParent();
            if (i==found_spot){
                connectNodes(i,substitute->getRight(),R);
            }
            else{
                connectNodes(i,substitute->getRight(),L);
            }
            substitute->setParent(nullptr);
            substitute.reset();
        }
        else{
            substitute= findMaxNode(i->getLeft());
            swapNodes(substitute,found_spot);
            i=substitute->getParent();
            if (i==found_spot){
                connectNodes(i,substitute->getLeft(),L);
            }
            else{
                connectNodes(i,substitute->getLeft(),R);
            }
            substitute->setParent(nullptr);
            substitute.reset();
        }

        //trace up and update heights of nodes in the search path
        //O(log(n))
        Node_ptr j=i;//temporary iterator
        while (j!=nullptr){
            j->updateHeight();
            j->updateRank();
            j=j->getParent();
        }
        j.reset();

        //handles corner case of i being the root
        //do rolls
        Node_ptr parent =i->getParent();
        int bf;
        while(i!=nullptr){ 
            bf=balance_factor(i);
            if(bf>1){
                //left
                if(balance_factor(i->getLeft())>0){
                    //left left
                    roll_ll(i);

                }
                else{
                    // left right
                    roll_lr(i);
                }
            }
            else if(bf<-1){
                //right
                if(balance_factor(i->getRight())<0){
                    //right right
                    roll_rr(i);
                }
                else{
                    // right left
                    roll_rl(i);
                }
            }
            if (i->getParent()==nullptr){
                root=i;
            }
            i=i->getParent();
        }
        return true;
    }
    //select kth smallest node
    Node_ptr select(int k){
        int tree_size=root->getRank();
        if (k>tree_size){
            //there is no kth element because there are less than k elements
            return nullptr;
        }
        Node_ptr left=root->getLeft();
        int left_rank=0;
        Node_ptr itt=root;
        if (left!=nullptr){
            left_rank=left->getRank();
        }
        while(left_rank+1!=k){
            if (left_rank>=k){
                itt=itt->getLeft();
            }
            else{
                itt=itt->getRight();
                k=k-(left_rank+1);
            }
            if (itt==nullptr){
                throw std::runtime_error("this shouldn't happen, ever");
            }
            left=itt->getLeft();
            left_rank=0;
            if (left!=nullptr){
                left_rank=left->getRank();
            }
        }
        return itt;
    }

    int getHeight() const{
        if (root!=nullptr){
            return root->getHeight();
        }
        else{
            //if tree is empty
            return -1;
        }
    }
    // Prints the tree in the format: ${key} BF: ${BF} Height: ${Height}
    void printTree() const{
        itterateOrder(root,IN,printNode);
    }
    //an outside destructor- clears the tree(used mainly for testing)
    void treeClear(){
        if (root!=nullptr){
            itterateOrder(root->getRight(),POST,freeNode);
            itterateOrder(root->getLeft(),POST,freeNode);
            root.reset();
        }
    }
    
    
};



/*
* Desctructor of AVL_Tree-
*   delete tree from the nodes , iterating post orderly 
*   time complexity is O(n). each node costs O(1) actions
*/

template<typename KEY,typename VAL>
AVL_Tree<KEY,VAL>::~AVL_Tree(){
    if (root!=nullptr){
        itterateOrder(root->getRight(),POST,freeNode);
        itterateOrder(root->getLeft(),POST,freeNode);
        
        root.reset();
    }
}

template <typename KEY,typename VAL>
void printValue(Node_ptr<KEY,VAL>& node){
    print(node->getValue());
}


/*
*Given a vertex, returns the root.
*does so by climbing parent by parent untill the is non
*/
template <typename KEY,typename VAL>
Node_ptr<KEY,VAL> getRootClimb(Node_ptr<KEY,VAL> node){
    while(node->getParent()!=nullptr){
        node=node->getParent();
    }
    return node;
}

/*
* InOrder-
*   given a root vertex, iterates Inorder over the tree under it. and activate a given function 'f' on the vertices
*/
template <typename KEY,typename VAL>
void inOrder(Node_ptr<KEY,VAL> root, void(*f)(Node_ptr<KEY,VAL>&)){
    if (root==nullptr){
        return;
    }
    if (isLeaf(root)){
        (*f)(root);
        return;
    }
    inOrder(root->getLeft(),f);
    (*f)(root);
    inOrder(root->getRight(),f);
}


/*
* ittarateOrder:
*   iterates over the tree from the root given by the order given and activates function 'f' on each vertex while doing so.
*   reverse- if set to true, the iteration is done backwards
*/
template <typename KEY,typename VAL>
void itterateOrder(Node_ptr<KEY,VAL> root,Order order, void(*f)(Node_ptr<KEY,VAL>&),bool reverse = false){
    if (root==nullptr){
        return;
    }
    if (isLeaf(root)){
        (*f)(root);
        return;
    }
    if (!reverse){
        if (order==IN){
            itterateOrder(root->getLeft(),IN,f);
            (*f)(root);
            itterateOrder(root->getRight(),IN,f);
        }
        if (order==POST){
            itterateOrder(root->getLeft(),POST,f);
            itterateOrder(root->getRight(),POST,f);
            (*f)(root);
        }
        if (order==PRE){
            (*f)(root);
            itterateOrder(root->getLeft(),PRE,f);
            itterateOrder(root->getRight(),PRE,f);
        }
    }
    else{
        if (order==IN){
            itterateOrder(root->getLeft(),IN,f,true);
            (*f)(root);
            itterateOrder(root->getRight(),IN,f,true);
        }
        if (order==POST){
            itterateOrder(root->getLeft(),POST,f,true);
            itterateOrder(root->getRight(),POST,f,true);
            (*f)(root);
        }
        if (order==PRE){
            (*f)(root);
            itterateOrder(root->getLeft(),PRE,f,true);
            itterateOrder(root->getRight(),PRE,f,true);
        }
    }
}

/*
* swaps values of two nodes given
*/
template <typename KEY,typename VAL>
void swapValues(Node_ptr<KEY,VAL> a,Node_ptr<KEY,VAL> b){
    VAL temp = a->getValue();
    a->setValue(b->getValue());
    b->setValue(temp);
}
/*
* given a root, returns the rightest node to it
*/
template <typename KEY,typename VAL>
Node_ptr<KEY,VAL> findMaxNode(Node_ptr<KEY,VAL> root){
    if (root==nullptr){
        return root;
    }
    Node_ptr<KEY,VAL> i=root;
    while (i->getRight()!=nullptr){
        i=i->getRight();
    }
    return i;
}
/*
* given a root, returns the leftest node to it
*/
template <typename KEY,typename VAL>
Node_ptr<KEY,VAL> findMinNode(Node_ptr<KEY,VAL> root){
    if (root==nullptr){
        return root;
    }
    Node_ptr<KEY,VAL> i=root;
    while (i->getLeft()!=nullptr){
        i=i->getLeft();
    }
    return i;
}

//checks wether a vertex is a leaf(has no children)
template <typename KEY,typename VAL>
bool isLeaf(Node_ptr<KEY,VAL> node){
    if (node==nullptr){
        return false;
    }
    return node->getLeft()==nullptr&&node->getRight()==nullptr;
}

/*
* connect parent to child to its side, and child to parent
*/
template <typename KEY,typename VAL>
void connectNodes(Node_ptr<KEY,VAL> parent,Node_ptr<KEY,VAL> child, Side side){
    if (parent!=nullptr){
        if (side==R){
            parent->setRight(child);
        }
        else if (side==L){
            parent->setLeft(child);
        }
        else{
            throw std::runtime_error("Excpected side to be left or right, but is either");
        }
    }
    if (child!=nullptr){
        child->setParent(parent);
    }
}
/**
 * Given a parent and a child, returns which side the child is
 * */
template <typename KEY,typename VAL>
Side childSide(Node_ptr<KEY,VAL> parent,Node_ptr<KEY,VAL> child){
    if (child==nullptr){
        //no child , no side
        return N;
    }
    if (parent==nullptr){
        //no parent , no side
        return N;
    }
    if (parent->getLeft()==child){
        return L;
    }
    if (parent->getRight()==child){
        return R;
    }
    // the child is not connected to the parent
    return N;
} 

//left left roll
template <typename KEY,typename VAL>
void roll_ll(Node_ptr<KEY,VAL>& old_root){
    Node_ptr<KEY,VAL> parent=old_root->getParent();
    Node_ptr<KEY,VAL> new_root=old_root->getLeft();
    Node_ptr<KEY,VAL> LR_Tree=new_root->getRight();

    Side root_side =childSide(parent,old_root);
    
    //handle new_root pointers 
    connectNodes(parent,new_root,root_side);//connect to its parent
    connectNodes(new_root,old_root,R);//connect old root to its right
    
    //handle old_root pointers
    connectNodes(old_root,LR_Tree,L);

    old_root->updateHeight();
    old_root->updateRank();
    new_root->updateHeight();
    new_root->updateRank();

    old_root=new_root;


}

//right right roll
template <typename KEY,typename VAL>
void roll_rr(Node_ptr<KEY,VAL>& old_root){
    Node_ptr<KEY,VAL> parent=old_root->getParent();
    Node_ptr<KEY,VAL> new_root=old_root->getRight();
    Node_ptr<KEY,VAL> RL_Tree=new_root->getLeft();

    Side root_side =childSide(parent,old_root);
    
    //handle new_root pointers 
    connectNodes(parent,new_root,root_side);//connect to its parent
    connectNodes(new_root,old_root,L);//connect old root to its left
    
    //handle old_root pointers
    connectNodes(old_root,RL_Tree,R);
    
    //handles new heights
    old_root->updateHeight();
    old_root->updateRank();
    new_root->updateHeight();
    new_root->updateRank();

    old_root=new_root;
}


//left right roll
template <typename KEY,typename VAL>
void roll_lr(Node_ptr<KEY,VAL>& old_root){
    Node_ptr<KEY,VAL> parent=old_root->getParent();
    Node_ptr<KEY,VAL> left=old_root->getLeft();
    Node_ptr<KEY,VAL> new_root=left->getRight();
    Node_ptr<KEY,VAL> LRR_Tree=new_root->getRight();
    Node_ptr<KEY,VAL> LRL_Tree=new_root->getLeft();


    Side root_side =childSide(parent,old_root);
    
    //handle new_root pointers 
    connectNodes(parent,new_root,root_side);//connect to its parent
    connectNodes(new_root,old_root,R);//connect old root to its right
    connectNodes(new_root,left,L);//connect left to its left
    
    //handle old_root pointers
    connectNodes(old_root,LRR_Tree,L);

    //handle left pointers
    connectNodes(left,LRL_Tree,R);

    //corrects heights and ranks
    old_root->updateHeight();
    old_root->updateRank();
    left->updateHeight();
    left->updateRank();
    new_root->updateHeight();
    new_root->updateRank();
    
    old_root=new_root;
}

//right left roll
template <typename KEY,typename VAL>
void roll_rl(Node_ptr<KEY,VAL>& old_root){
    Node_ptr<KEY,VAL> parent=old_root->getParent();
    Node_ptr<KEY,VAL> right=old_root->getRight();
    Node_ptr<KEY,VAL> new_root=right->getLeft();
    Node_ptr<KEY,VAL> RLL_Tree=new_root->getLeft();
    Node_ptr<KEY,VAL> RLR_Tree=new_root->getRight();

    Side root_side =childSide(parent,old_root);
    
    //handle new_root pointers 
    connectNodes(parent,new_root,root_side);//connect to its parent
    connectNodes(new_root,old_root,L);//connect old root to its left 
    connectNodes(new_root,right,R);//connect right to its right 
    
    //handle old_root pointers
    connectNodes(old_root,RLL_Tree,R);

    //handle right pointers
    connectNodes(right,RLR_Tree,L);

    //handles new heights and ranks
    old_root->updateHeight();
    old_root->updateRank();
    right->updateHeight();
    right->updateRank();
    new_root->updateHeight();
    new_root->updateRank();

    old_root=new_root;
}

/**
 *  2021 Functions
 * */



#endif 