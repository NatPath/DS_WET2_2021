#include "Group.h"

int Group::getSize() const{
    return size;
}
void Group::setSize(int new_size){
    size = new_size;
}
void Group::insertPlayer(Player* player_p){
    PlayerSeat player_seat(player_p);
    groupPlayersTree.insertNode(player_seat,player_seat);
    size++;
    highest_level_player= groupPlayersTree.select(size);
}
Node_ptr<PlayerSeat,PlayerSeat> Group::getHighestLevelPlayer(){
    return highest_level_player;
}
//O(logn)
void Group::updateHighestLevelPlayer(){
    if (size==0){
        highest_level_player=nullptr;
        return;
    }
    highest_level_player= groupPlayersTree.select(size);
}

/**
 * helper function for updateGroupPLayersAboutGroup.
 * practicly inorders the tree and updates the players in the players seats.
 * (The general inorder function of the tree does not have an extra argument for the group pointer)
 * */
void updateGroupPlayersAboutGroup_wrap(Node_ptr<PlayerSeat,PlayerSeat> root,Group* group_p){
    if (root==nullptr){
        return;
    }
    updateGroupPlayersAboutGroup_wrap(root->getLeft(),group_p);
    (root->getValue()).getPlayerOnSeat()->setGroup(group_p);
    updateGroupPlayersAboutGroup_wrap(root->getRight(),group_p);

}
void Group::updateGroupPlayersAboutGroup(){
    Node_ptr<PlayerSeat,PlayerSeat> root = groupPlayersTree.getRoot();
    updateGroupPlayersAboutGroup_wrap(root,this);

    
}