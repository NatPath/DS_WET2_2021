#ifndef AVL_EXTRA_FUNC_H
#define AVL_EXTRA_FUNC_H

#include "List.h"
#include "Pair.h"
#include "Avl.h"

/* *
 * make an ordered list of Pairs (ordered by key of course) into a tree
 * 
 * 
 * */
template <typename KEY,typename VAL>
using Node_ptr=std::shared_ptr<AVL_NODE<KEY,VAL>>;

/**
 * gets an array. make an avl tree from all of it.
 * */
template <typename KEY,typename VAL>
AVL_Tree<KEY,VAL> ArrayToTree(DynamicArray<Pair<KEY,VAL>>& array){
    int size = array.getSize();
    AVL_Tree<KEY,VAL> tree;
    Node_ptr<KEY,VAL> root = ArrayToTree(array,0,size-1);
    tree.setRoot(root);
    return tree;
}

/**
 * gets an array. make an avl tree of the element between start_index and end_index.
 * */
template <typename KEY,typename VAL>
Node_ptr<KEY,VAL> ArrayToTree(DynamicArray<Pair<KEY,VAL>>& array,int start_index,int end_index){

    if(start_index>end_index){
        return nullptr;
    }

    int size = end_index-start_index+1;
    int mid= start_index+size/2;
    Node_ptr<KEY,VAL> tree=std::make_shared<AVL_NODE<KEY,VAL>>(array[mid].getKey(),array[mid].getValue());
    if (start_index==end_index){
        return tree;
    }
    Node_ptr<KEY,VAL> left_tree = ArrayToTree(array,start_index,mid-1);
    Node_ptr<KEY,VAL> right_tree = ArrayToTree(array,mid+1,end_index);
    connectNodes(tree,left_tree,L);
    connectNodes(tree,right_tree,R);
    tree->updateHeight();
    tree->updateRank();
    return tree;
}

/* Trying a different approach, return Node_ptr instead of AVL_Tree
template <typename KEY,typename VAL>
AVL_Tree<KEY,VAL> ArrayToTree(DynamicArray<Pair<KEY,VAL>>& array,int start_index,int end_index){

    if(start_index>end_index){
        return AVL_Tree<KEY,VAL>();
    }

    int size = end_index-start_index+1;
    int mid= start_index+size/2;
    AVL_Tree<KEY,VAL> tree;
    tree.insertNode(array[mid].getKey(),array[mid].getValue());
    if (start_index==end_index){
        return tree;
    }
    AVL_Tree<KEY,VAL> left_tree = ArrayToTree(array,start_index,mid-1);
    AVL_Tree<KEY,VAL> right_tree = ArrayToTree(array,mid+1,end_index);
    connectNodes(tree.getRoot(),left_tree.getRoot(),L);
    connectNodes(tree.getRoot(),right_tree.getRoot(),R);
    tree.getRoot()->updateHeight();
    tree.getRoot()->updateRank();
    left_tree.setRoot(nullptr);
    right_tree.setRoot(nullptr);
    return tree;
}
*/

template <typename KEY,typename VAL>
AVL_Tree<KEY,VAL> ListToTree(List<Pair<KEY,VAL>>& list){
    DynamicArray<Pair<KEY,VAL>> array = listToArray(list);
    return ArrayToTree(array);
}

template <typename KEY,typename VAL>
List<Pair<KEY,VAL>> TreeToList(AVL_Tree<KEY,VAL>& tree){
    if( tree.getRoot()==nullptr){
        return List<Pair<KEY,VAL>>();
    }
    Node_ptr<KEY,VAL> leftest =tree.select(1);
    int tree_size=(tree.getRoot())->getRank();
    int index=0;
    DynamicArray<Pair<KEY,VAL>> arr(tree_size);
    reverseClimbTreeFromLeft(leftest,true,true,true,&index,arr,tree_size);    
    return List<Pair<KEY,VAL>>(arr);
}

template <typename KEY,typename VAL>
void reverseClimbTreeFromLeft(std::shared_ptr<AVL_NODE<KEY,VAL>> current,bool goUp,bool goLeft,bool goRight,int *index,DynamicArray<Pair<KEY,VAL>>& arr , int m){
    if (!current|| *index >= m)
    {
        return;
    }
    // go left 
    if (current->getLeft() && goLeft)
    {
        reverseClimbTreeFromLeft(current->getLeft(), false, true, true, index, arr, m);
    }

    if (*index >= m)
    {
        return;
    }

    // save this node
    arr[*index] = Pair<KEY,VAL>(current->getKey(),current->getValue());
    *index += 1;

    // go right 
    if (current->getRight() && goRight)
    {
        reverseClimbTreeFromLeft(current->getRight(), false, true, true, index, arr, m);
    }

    // go up
    if (current->getParent() && goUp)
    {
        // decide if this is the right or left child so we don't return here
        if (current->getKey() > current->getParent()->getKey())
        {
            reverseClimbTreeFromLeft(current->getParent(), true, true, false, index, arr, m);
        }
        else
        {
            reverseClimbTreeFromLeft(current->getParent(), true, false, true, index, arr, m);
        }
    }

}

template <typename KEY,typename VAL>
void reverseClimbTreeFromRight(std::shared_ptr<AVL_NODE<KEY,VAL>> current,bool goUp,bool goLeft,bool goRight,int *index, DynamicArray<Pair<KEY,VAL>>& arr, int m){

    if (!current|| *index >= m)
    {
        return;
    }
    // go right
    if (current->getRight() && goRight)
    {
        reverseClimbTreeFromRight(current->getRight(), false, true, true, index, arr, m);
    }

    if (*index >= m)
    {
        return;
    }

    // save this node
    arr[*index] = Pair<KEY,VAL>(current->getKey(),current->getValue());
    *index += 1;

    // go left
    if (current->getLeft() && goLeft)
    {
        reverseClimbTreeFromRight(current->getLeft(), false, true, true, index, arr, m);
    }

    // go up
    if (current->getParent() && goUp)
    {
        // decide if this is the right or left child so we don't return here
        if (current->getKey() > current->getParent()->getKey())
        {
            reverseClimbTreeFromRight(current->getParent(), true, true, false, index, arr, m);
        }
        else
        {
            reverseClimbTreeFromRight(current->getParent(), true, false, true, index, arr, m);
        }
    }
}

template <typename KEY,typename VAL>
void updateAttributes(Node_ptr<KEY,VAL>& node_ptr){
    node_ptr->updateAttributes();    
}
/**
 * merge tree1 and tree2 into one big tree.
 * both of the input trees are valid after the merge.
 * NOTE:(complex object behaivor should be checked)
 * O(n1+n2)
 * 
 * */
template <typename KEY,typename VAL>
AVL_Tree<KEY,VAL> merge_trees(AVL_Tree<KEY,VAL>& tree1,AVL_Tree<KEY,VAL>& tree2){
    List<Pair<KEY,VAL>> list1 = TreeToList(tree1);
    List<Pair<KEY,VAL>> list2 = TreeToList(tree2);

    List<Pair<KEY,VAL>> merged_list = mergeOrderedLists(list1,list2);

    AVL_Tree<KEY,VAL> res = ListToTree(merged_list);
    itterateOrder(res.getRoot(),POST,updateAttributes,false);
    return res;

}



#endif