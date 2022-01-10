#ifndef UNIONFIND_H
#define UNIONFIND_H
#include "Group.h"

#define NO_PARENT -1
class UnionFind{
    int* size;
    int* parent;
    Group* groups;
    int k;

    public:
    UnionFind(int numOfEle);
    ~UnionFind();
    void initilize(int scale);
    Group& find(const Group& group);
    Group& findByID(int groupID);
    void unionGroups(const Group& group1, const Group& group2);
    void unionGroupsByID(int group1, int group2);
};

#endif //UNTITLED5_UNIONFIND_H
