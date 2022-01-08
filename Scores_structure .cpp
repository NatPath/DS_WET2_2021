#include "Scores_structure.h"
#include "AVL_extra_functions.h"

//
void Score_structure::removePlayer_from_ss(PlayerSeat player_to_remove){
    Player* player_pointer= player_to_remove.getPlayerOnSeat();
    int player_score = player_pointer->getScore();
    int player_level= player_pointer->getLevel();
    if (player_level==0){
        zero_counter--;
    }
    else{
        score_tree.deleteNode(player_to_remove);
    }
}
void Score_structure::addPlayer_to_ss(PlayerSeat player_to_add){
    Player* player_pointer= player_to_add.getPlayerOnSeat();
    int player_score = player_pointer->getScore();
    int player_level= player_pointer->getLevel();
    if (player_level==0){
        zero_counter++;
    }
    else{
        score_tree.insertNode(player_to_add,player_to_add);
    }
}
int Score_structure::get_ZeroCounter(){
    return zero_counter;
}
AVL_Tree<PlayerSeat,PlayerSeat>& Score_structure::get_ScoreTree(){
    return score_tree;
}
void Score_structure::set_ScoreTree(AVL_Tree<PlayerSeat,PlayerSeat>& new_score_tree ){
    score_tree = new_score_tree;
}
    
void unite_score_structures(Score_structure&  ss_root,Score_structure& ss_to_add){
    int zero_counter1 = ss_root.get_ZeroCounter();
    int zero_counter2 = ss_to_add.get_ZeroCounter();
    AVL_Tree<PlayerSeat,PlayerSeat> root_tree = ss_root.get_ScoreTree();
    AVL_Tree<PlayerSeat,PlayerSeat> to_add_tree = ss_to_add.get_ScoreTree();
    AVL_Tree<PlayerSeat,PlayerSeat> res_tree = merge_trees(root_tree,to_add_tree);
    ss_root.set_ScoreTree(res_tree);
    ss_root.set_ZeroCounter(zero_counter1+zero_counter2);
}