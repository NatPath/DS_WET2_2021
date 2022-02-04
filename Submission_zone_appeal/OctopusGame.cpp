#include "OctopusGame.h"

int global_scale;
int global_k;
OctopusGame::OctopusGame(int k , int scale):k(k),scale(scale),PlayersTable(2),GroupsUF(k){
    GroupsUF.initilize(scale);
    global_scale=scale;
    global_k=k;
}


StatusType OctopusGame::MergeGroups(int GroupID1, int GroupID2){
    if(GroupID1 <= 0 || GroupID2 <= 0 || GroupID1 > k || GroupID2 > k){
        return INVALID_INPUT;
    }
    try{
        if(GroupID1!=GroupID2){
            GroupsUF.unionGroupsByID(GroupID1,GroupID2);
        }
        return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    
}

StatusType OctopusGame::AddPlayer(int PlayerID, int GroupID, int score){
    if(GroupID <= 0 || GroupID > k || PlayerID <= 0 || score <= 0 || score > scale){
        return INVALID_INPUT;
    }
    

    try{
        Player* new_player= new Player(PlayerID,GroupID,score);
        bool insert_success = PlayersTable.insert(*new_player);

        if (!insert_success){// playerID is already in the table
            delete new_player;
            return StatusType::FAILURE;
        }
        
        Group& found_group = GroupsUF.findByID(GroupID);
        // in group general
        found_group.insertPlayer(new_player);
        // all over
        Group& all_players_group = GroupsUF.findByID(0);
        all_players_group.insertPlayer(new_player);

        delete new_player;

        return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

}

StatusType OctopusGame::RemovePlayer(int PlayerID){
    if(PlayerID <= 0){
        return INVALID_INPUT;
    }
    Player dummyPlayer(PlayerID,0,0);
    ListNode<Player>* found_node = PlayersTable.find(dummyPlayer);
    if(found_node == nullptr){
        return FAILURE;
    }
    Player* currentPlayer = found_node->getValue().get();
    
    Group& playerGroup = GroupsUF.findByID(currentPlayer->getGroupID());
    Group& allplayersGroup= GroupsUF.findByID(0);
    playerGroup.removePlayer(currentPlayer);
    allplayersGroup.removePlayer(currentPlayer);


    PlayersTable.remove(dummyPlayer);

    return SUCCESS;
}

StatusType OctopusGame::IncreasePlayerIDLevel(int PlayerID, int LevelIncrease){
    if(PlayerID <= 0 || LevelIncrease <= 0){
        return INVALID_INPUT;
    }
    try{
        Player dummyPlayer(PlayerID,0,0);
        ListNode<Player>* found_node = PlayersTable.find(dummyPlayer);
        if(found_node == nullptr){
            return FAILURE;
        }
        Player* player_p = found_node->getValue().get();

        Group& playerGroup = GroupsUF.findByID(player_p->getGroupID());
        Group& allplayersGroup = GroupsUF.findByID(0);

        //remove player from his group 
        playerGroup.removePlayer(player_p);
        //remove player from allplayers group
        allplayersGroup.removePlayer(player_p);

        //increase its level
        player_p->increaseLevel(LevelIncrease);

        //insert to his group 
        playerGroup.insertPlayer(player_p);
        //insert to allplayers group
        allplayersGroup.insertPlayer(player_p);

        return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType OctopusGame::ChangePlayerIDScore(int PlayerID, int NewScore){
    if(PlayerID <= 0 || NewScore > scale || NewScore <= 0){
        return INVALID_INPUT;
    }
    try{
        Player dummyPlayer(PlayerID,0,0);
        ListNode<Player>* found_node = PlayersTable.find(dummyPlayer);
        
        if(found_node == nullptr){
            return FAILURE;
        }
        Player* currentPlayer = found_node->getValue().get();

        Group& playerGroup = GroupsUF.findByID(currentPlayer->getGroupID());
        Group& allplayersGroup = GroupsUF.findByID(0);
        
        playerGroup.removePlayer(currentPlayer);
        allplayersGroup.removePlayer(currentPlayer);

        currentPlayer->setScore(NewScore);

        playerGroup.insertPlayer(currentPlayer);
        allplayersGroup.insertPlayer(currentPlayer);

        return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    
    return SUCCESS;
}

 
/**
 * @brief 
 * returns the number of players between lowerLevel and higherLevel.
 * if score==0: of all players in the group
 * if score!=0: of all players with exactly the score in the group
 * @param GroupID 
 * @param lowerLevel 
 * @param higherLevel 
 * @param score 
 * @return double 
 */
double OctopusGame::calculate_number_of_players_in_bound(int GroupID, int lowerLevel,int higherLevel,int score){
    Group& playersGroup = GroupsUF.findByID(GroupID);
    Score_structure* groupSS_s = playersGroup.get_groupSS();
    Score_structure& groupSS= groupSS_s[score];

    //calc non_zero_level
    double total;

    Player maxDummyPlayer(-1, GroupID, score);
    Player minDummyPlayer(0,GroupID, score);
    maxDummyPlayer.setLevel(higherLevel);
    minDummyPlayer.setLevel(lowerLevel);
    Player* maxPlayer = &maxDummyPlayer;
    Player* minPlayer = &minDummyPlayer;
    
    playersGroup.insertPlayer(maxPlayer);
    playersGroup.insertPlayer(minPlayer);

    AVL_Tree<PlayerSeat,PlayerSeat>& scorePlayersTree = groupSS.get_ScoreTree();
    PlayerSeat maxPlayerSeat(maxPlayer);
    PlayerSeat minPlayerSeat(minPlayer);
    double max_index = scorePlayersTree.findIndex(maxPlayerSeat);
    double min_index = scorePlayersTree.findIndex(minPlayerSeat);

    total = max_index - min_index - 1;

    if (lowerLevel<=0 && higherLevel >=0){
        total+= groupSS.get_ZeroCounter();
    }
    playersGroup.removePlayer(maxPlayer);
    playersGroup.removePlayer(minPlayer);

    return total;
}
StatusType OctopusGame::GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double * players){
    if(players == NULL || GroupID < 0 || GroupID > k){
        return INVALID_INPUT;
    }

    try{

        // calculate number of players in the range
        double total_number_of_players = calculate_number_of_players_in_bound(GroupID,lowerLevel,higherLevel,0);

        //after calculatiion..
        if (total_number_of_players<=0){
            return StatusType::FAILURE;
        }
        // calculate number of players with the score in the range
        double number_of_players_with_score = calculate_number_of_players_in_bound(GroupID,lowerLevel,higherLevel,score);
        //
        *players = number_of_players_with_score*100/total_number_of_players;

        return StatusType::SUCCESS;
        
    }catch(const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return SUCCESS;
        
}

    

StatusType OctopusGame::AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level){
    if(level == NULL || m <= 0 || GroupID < 0 || GroupID > k){
        return INVALID_INPUT;
    }
    try{
        Group& found_group = GroupsUF.findByID(GroupID);
        int group_size = found_group.getSize();
        if (found_group.getSize()<m){
            return StatusType::FAILURE;
        }

        
        Score_structure* groupSS = found_group.get_groupSS();
        int zero_count=groupSS[0].get_ZeroCounter();
        int n_prime=group_size-zero_count;
        if (n_prime==0){
            *level=0;
            return StatusType::SUCCESS;
        }
        int index_to_select= n_prime-m+1;
        if (n_prime<m){
            index_to_select=1;
        }

        AVL_Tree<PlayerSeat,PlayerSeat>& all_players_in_group_tree = groupSS[0].get_ScoreTree();
        int sum_of_smaller_levels=0;
        all_players_in_group_tree.select_and_sum(index_to_select,&sum_of_smaller_levels);
        int sum=0;
        all_players_in_group_tree.select_and_sum(n_prime,&sum);
        Node_ptr<PlayerSeat,PlayerSeat> m_from_last_player= all_players_in_group_tree.select(index_to_select);
        int m_from_last_level=m_from_last_player->getValue().getPlayerOnSeat()->getLevel();
        int res_sum = sum- sum_of_smaller_levels+m_from_last_level;//the sum of levels of m highest level players
        double res = (double)res_sum/(double)m;
        *level=res;

        return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

}

//bonus
StatusType OctopusGame::GetPlayersBound(int GroupID, int score, int m, int *LoverBoundPlayers, int *HigherBoundPlayers){
    return StatusType::SUCCESS;
}
    

