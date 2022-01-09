#ifndef _GROUP_H_
#define _GROUP_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "library2.h"
#include "Avl.h"
#include "Player.h"
#include "Scores_structure.h"
#include "OctopusGame.h"

class Group
{
    int group_id;
    int size;
    Score_structure* groupSS;
    //This part was moved to groupSS[0]
    /* 
    AVL_Tree<PlayerSeat,PlayerSeat> groupPlayersByLevelTree;
    int group_players_zero_level_counter;
    */

public:
    Group(int groupID) : group_id(groupID),size(0){
        groupSS=new Score_structure[global_scale+1];
        for (int i=0;i<=global_scale;i++){
            groupSS[i].set_score(i);
        }
    };
    Group(): group_id(-1),size(0){}
    ~Group()=default;

    int setID(int new_id);
    int getID() const;

    Score_structure* get_groupSS();
    void set_groupSS(Score_structure* new_groupSS);


    //gets the size of the group
    int getSize() const;
    void setSize(int new_size);


    /**
     * insert player into group
     * */
    void insertPlayer(Player* player_p);

    /**
     * remove player from group
     * */
    void removePlayer(Player* player_p);
    
    //not used anymore
    /*
    int getGroupZeroCounter();
    void setGroupZeroCounter(int new_zero_counter);
    AVL_Tree<PlayerSeat, PlayerSeat>& getPlayersTree();
    void setGroupsPlayerTree(AVL_Tree<PlayerSeat,PlayerSeat>& new_tree);
    */
    
};
void unite_groups(Group& group_root,Group& group_to_add);

#endif
