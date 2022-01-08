#include "Group.h"

int Group::setID(int new_id){
    group_id= new_id;
}
int Group::getID() const
{
    return group_id;
}
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
int Group::getSize() const{
    return size;
}
void Group::setSize(int new_size){
    size = new_size;
}
void Group::insertPlayer(Player* player_p){
    PlayerSeat player_seat(player_p);
    groupPlayersByLevelTree.insertNode(player_seat,player_seat);
    groupSS->addPlayer_to_ss(player_seat);
    size++;
}
void Group::removePlayer(Player* player_p){
    PlayerSeat player_seat(player_p);
    groupPlayersByLevelTree.deleteNode(player_seat);
    groupSS->removePlayer_from_ss(player_seat);
    size--;
}

void unite_groups(Group& group_root,Group& group_to_add){
    Score_structure* root_ss = group_root.get_groupSS();
    Score_structure* to_add_ss = group_to_add.get_groupSS();
    for (int i=0;i<=global_scale;i++){
        unite_score_structures(root_ss[i],to_add_ss[i]);
    }
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

}
