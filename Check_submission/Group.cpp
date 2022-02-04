#include "Group.h"
#include "OctopusGame.h"

Group::Group() : group_id(-1),size(0),groupSS(nullptr),scale(-1){
}
Group::Group(int groupID) : group_id(groupID),size(0){
    groupSS=new Score_structure[global_scale+1];
    for (int i=0;i<=global_scale;i++){
        groupSS[i].set_score(i);
    }
}
Group::~Group(){
    delete[] groupSS;
}
void Group::initSS(int new_scale){
    scale=new_scale;
    groupSS = new Score_structure[scale+1];
    for (int i=0; i<=scale ; i++){
        groupSS[i].set_score(i);
    }
}
void Group::setID(int new_id){
    group_id= new_id;
}
int Group::getID() const
{
    return group_id;
}
Score_structure* Group::get_groupSS(){
    return groupSS;
}
void Group::set_groupSS(Score_structure* new_groupSS){
    groupSS=new_groupSS;
}
int Group::getSize() const{
    return size;
}
void Group::setSize(int new_size){
    size = new_size;
}
void Group::insertPlayer(Player* player_p){
    PlayerSeat player_seat(player_p);
    int player_score=player_p->getScore();
    groupSS[player_score].addPlayer_to_ss(player_seat);
    groupSS[0].addPlayer_to_ss(player_seat);
    size++;
}
void Group::removePlayer(Player* player_p){
    PlayerSeat player_seat(player_p);
    int player_score=player_p->getScore();
    groupSS[player_score].removePlayer_from_ss(player_seat);
    groupSS[0].removePlayer_from_ss(player_seat);
    size--;
}

void unite_groups(Group& group_root,Group& group_to_add){
    int group_root_size=group_root.getSize();
    int group_to_add_size=group_to_add.getSize();
    Score_structure* root_ss = group_root.get_groupSS();
    Score_structure* to_add_ss = group_to_add.get_groupSS();
    for (int i=0;i<=group_root.scale;i++){
        unite_score_structures(root_ss[i],to_add_ss[i]);
    }
    group_root.setSize(group_root_size+group_to_add_size);
    /*
    AVL_Tree<PlayerSeat,PlayerSeat> root_tree = group_root.getPlayersTree();
    AVL_Tree<PlayerSeat,PlayerSeat> to_add_tree= group_to_add.getPlayersTree();
    AVL_Tree<PlayerSeat,PlayerSeat> res_tree = merge_trees(root_tree,to_add_tree);
    group_root.setGroupsPlayerTree(res_tree);



    int zero_counter1 = group_root.getGroupZeroCounter();
    int zero_counter2 = group_to_add.getGroupZeroCounter();
    group_root.setGroupZeroCounter(zero_counter1+zero_counter2);

    int size1 = group_root.getSize();
    int size2 = group_to_add.getSize();
    group_root.setSize(size1+size2);
    */

}

/*
AVL_Tree<PlayerSeat, PlayerSeat>& Group::getPlayersTree() {
    return groupPlayersByLevelTree; // !!!!!!! Check if returning only the root is required !!!!!!!
}
void Group::setGroupsPlayerTree(AVL_Tree<PlayerSeat,PlayerSeat>& new_tree){
    groupPlayersByLevelTree = new_tree;
}
Score_structure* Group::get_groupSS(){
    return groupSS;
}
void Group::set_groupSS(Score_structure* new_group_ss){
    groupSS= new_group_ss;
}
int Group::getGroupZeroCounter(){
    return group_players_zero_level_counter;
}

void Group::setGroupZeroCounter(int new_zero_counter){
    group_players_zero_level_counter = new_zero_counter;
}
*/