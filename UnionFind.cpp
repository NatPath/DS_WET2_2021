#include "UnionFind.h"

//UnionFind::UnionFind(int numOfEle) : size(new int[numOfEle+1]), parent(new int[numOfEle+1]), groups(new Group[numOfEle+1]), k(numOfEle){
UnionFind::UnionFind(int numOfEle){
    k=numOfEle;
    size=new int[numOfEle+1];
    parent=new int[numOfEle+1];
    groups=new Group[numOfEle+1];
    for (int i=0;i<=numOfEle;i++){
        groups[i].setID(i);
        size[i]=0;
        parent[i]=NO_PARENT;
    }
}
void UnionFind::initilize(int scale){
    for (int i=0;i<=k;i++){
        groups[i].initSS(scale);
    }    
}
void UnionFind::unionGroupsByID(int group1, int group2){
    UnionFind::unionGroups(groups[group1], groups[group2]);
}
void UnionFind::unionGroups(const Group &group1, const Group &group2) {
    Group& group1_root = find(group1);
    Group& group2_root = find(group2);


    if(size[group1_root.getID()] < size[group2_root.getID()]){
        parent[group1_root.getID()] = group2_root.getID();
        size[group2_root.getID()] += size[group1_root.getID()];


        unite_groups(group2_root,group1_root); 
    }
    else{
        parent[group2_root.getID()] = group1_root.getID();
        size[group1_root.getID()] += size[group2_root.getID()];

        unite_groups(group1_root,group2_root); 
    }
}

Group &UnionFind::find(const Group &group) {
    int current = group.getID();
    while(parent[current] != NO_PARENT){
        current = parent[current];
    }
    int group_root = current;
    current = group.getID();

    int temp = current;
    while(parent[current] != NO_PARENT){
        temp = current;
        current = parent[current];
        parent[temp] = group_root;
    }

    return groups[group_root];
}

Group& UnionFind::findByID(int groupID){
    int current = groupID;
    while(parent[current] != NO_PARENT){
        current = parent[current];
    }
    int group_root = current;
    current = groupID;

    int temp = current;
    while(parent[current] != NO_PARENT){
        temp = current;
        current = parent[current];
        parent[temp] = group_root;
    }

    return groups[group_root];
}