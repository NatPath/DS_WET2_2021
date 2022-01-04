#ifndef _GROUP_H_
#define _GROUP_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "library1.h"
#include "Avl.h"
#include "Player.h"

class Group
{
    int group_id;
    int size;
    Scores_Structure group_ss;
    AVL_TREE<Player,Player> playersByLevelTree;


    AVL_Tree<PlayerSeat, PlayerSeat> groupPlayersTree;
    Node_ptr<PlayerSeat,PlayerSeat> highest_level_player;

public:
    Group(int groupID) : group_id(groupID),size(0),highest_level_player(nullptr){};
    ~Group()=default;

    int getID() const
    {
        return group_id;
    }
    AVL_Tree<PlayerSeat, PlayerSeat>& getPlayerTree() {
        return groupPlayersTree; // !!!!!!! Check if returning only the root is required !!!!!!!
    }
    void setGroupsPlayerTree(AVL_Tree<PlayerSeat,PlayerSeat>& new_tree){
        groupPlayersTree = new_tree;
    }
    //gets the size of the group
    int getSize() const;
    void setSize(int new_size);

    Node_ptr<PlayerSeat,PlayerSeat> getHighestLevelPlayer();
    void updateHighestLevelPlayer();

    /**
     * insert player into group
     * */
    void insertPlayer(Player* player_p);
    void updateGroupPlayersAboutGroup();

};

#endif
