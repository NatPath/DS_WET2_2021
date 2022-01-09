#ifndef _SCORE_STRUCT_H
#define _SCORE_STRUCT_H
#include "Avl.h"
#include "Player.h"
#include "PlayerSeat.h"
#include "List.h"

class Score_structure{
    AVL_Tree<PlayerSeat,PlayerSeat> score_tree;
    int zero_counter;
    int score;
    public:
    //Score_structure():zero_counter(0),score(0){};
    Score_structure();
    Score_structure(int score):zero_counter(0),score(score){};
    ~Score_structure()=default;

    void removePlayer_from_ss(PlayerSeat player_to_remove);
    void addPlayer_to_ss(PlayerSeat player_to_add);
    
    void set_score(int new_score);
    int get_score();

    int get_ZeroCounter();
    void set_ZeroCounter(int new_zero_counter);

    AVL_Tree<PlayerSeat,PlayerSeat>& get_ScoreTree();
    void set_ScoreTree(AVL_Tree<PlayerSeat,PlayerSeat>& new_score_tree );


    

};

void unite_score_structures(Score_structure& ss1,Score_structure& ss2);
#endif