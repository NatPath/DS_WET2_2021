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
        GroupsUF.unionGroupsByID(GroupID1,GroupID2);
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
            return StatusType::FAILURE;
        }
        
        Group& found_group = GroupsUF.findByID(GroupID);
        // in group general
        found_group.insertPlayer(new_player);
        /*
        found_group.setGroupZeroCounter(found_group.getGroupZeroCounter()+1);
        // in group by score
        int current_group_by_score_zero_counter = found_group.get_groupSS()[score].get_ZeroCounter();
        found_group.get_groupSS()[score].set_ZeroCounter(current_group_by_score_zero_counter+1);
        */
        // all over
        Group& all_players_group = GroupsUF.findByID(0);
        all_players_group.insertPlayer(new_player);
        /*
        
        all_groups_ss[score].set_ZeroCounter(all_groups_ss[score].get_ZeroCounter()+1);

        int found_group_size = found_group.getSize();
        found_group.setSize(found_group_size);
        all_players_zero_level_counter++;
        */
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
    playerGroup.removePlayer(currentPlayer);
    /*

    if(currentPlayer->getLevel() == 0){
        //reduce the zero counter in the current score, group and whole system
        
        groupSS[currentPlayerScore].set_ZeroCounter(groupSS[currentPlayerScore].get_ZeroCounter()-1);

        playerGroup.setGroupZeroCounter(playerGroup.getGroupZeroCounter()-1);

        all_groups_ss[currentPlayerScore].set_ZeroCounter(all_groups_ss[currentPlayerScore].get_ZeroCounter()-1);

        all_players_zero_level_counter--;

    }

    else{
        //remove from the tree represented by player's score inside the group
        AVL_Tree<PlayerSeat,PlayerSeat>& playerGroupScoreTree =  groupSS[currentPlayerScore].get_ScoreTree();
        playerGroupScoreTree.deleteNode(currentPlayer);

        //remove from the group player's tree
        AVL_Tree<PlayerSeat,PlayerSeat>& playerGroupTree = playerGroup.getPlayersTree();
        playerGroupTree.deleteNode(currentPlayer);

        //change the number of players in the group
        playerGroup.setSize(playerGroup.getSize()-1);
        
        //remove from the tree represented by player's score in the system
        AVL_Tree<PlayerSeat,PlayerSeat>& playerSystemScoreTree = all_groups_ss[currentPlayerScore].get_ScoreTree();
        playerSystemScoreTree.deleteNode(currentPlayer);

        //remove from the system's players tree
        PlayerByLevelTree.deleteNode(currentPlayer);
    }
    */

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



        /*
        int currentPlayerScore = player_p->getScore();
        int groupSS_current_zero = groupSS[currentPlayerScore].get_ZeroCounter();
        int all_groups_ss_zero_counter = all_groups_ss[currentPlayerScore].get_ZeroCounter();
        int group_current_zero = playerGroup.getGroupZeroCounter();
        
        int player_current_level=player_p->getLevel();    
        if (player_current_level==0){
            //decrease zero counters        
            all_players_zero_level_counter--;
            all_groups_ss[currentPlayerScore].set_ZeroCounter(all_groups_ss_zero_counter-1);
            groupSS[currentPlayerScore].set_ZeroCounter(groupSS_current_zero-1);
            playerGroup.setGroupZeroCounter(group_current_zero-1);

        }
        PlayerSeat player_seat(player_p);
        // remove from trees
        PlayerByLevelTree.deleteNode(player_seat);
        all_groups_ss[currentPlayerScore].get_ScoreTree().deleteNode(player_seat);
        groupSS[currentPlayerScore].get_ScoreTree().deleteNode(player_seat);
        playerGroup.getPlayersTree().deleteNode(player_seat);
        
        //change the level
        player_p->setLevel(player_current_level+LevelIncrease);

        // insert to trees
        PlayerByLevelTree.insertNode(player_seat,player_seat);
        all_groups_ss[currentPlayerScore].get_ScoreTree().insertNode(player_seat,player_seat);
        groupSS[currentPlayerScore].get_ScoreTree().insertNode(player_seat,player_seat);
        playerGroup.getPlayersTree().insertNode(player_seat,player_seat);
        */

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
    
    /*
    currentPlayer->setScore(NewScore);

    Group& playerGroup = GroupsUF.findByID(currentPlayer->getGroupID());
    Score_structure* groupSS = playerGroup.get_groupSS();
    int currentPlayerScore = currentPlayer->getScore();
    
    try{
        if(currentPlayer->getLevel() == 0){

            //change the zero counter in the groups score array
            int old_ss_zero_counter = groupSS[currentPlayerScore].get_ZeroCounter(); 
            groupSS[currentPlayerScore].set_ZeroCounter(old_ss_zero_counter-1);
            int new_ss_zero_counter = groupSS[NewScore].get_ZeroCounter(); 
            groupSS[NewScore].set_ZeroCounter(new_ss_zero_counter+1);

            // change the zero counter in the system score array
            int old_all_ss_zero_counter = all_groups_ss[currentPlayerScore].get_ZeroCounter();
            all_groups_ss[currentPlayerScore].set_ZeroCounter(old_all_ss_zero_counter-1);
            int new_all_ss_zero_counter = all_groups_ss[NewScore].get_ZeroCounter();
            all_groups_ss[NewScore].set_ZeroCounter(new_all_ss_zero_counter+1);
        }

        else{
            //get the group's current and new scores trees and the system's current and new scores trees
            AVL_Tree<PlayerSeat,PlayerSeat>& oldPlayerGroupScoreTree = groupSS[currentPlayerScore].get_ScoreTree();
            AVL_Tree<PlayerSeat,PlayerSeat>& oldPlayerSystemScoreTree = all_groups_ss[currentPlayerScore].get_ScoreTree();
            AVL_Tree<PlayerSeat,PlayerSeat>& newPlayerGroupScoreTree = groupSS[NewScore].get_ScoreTree();
            AVL_Tree<PlayerSeat,PlayerSeat>& newPlayerSystemScoreTree = all_groups_ss[NewScore].get_ScoreTree();
            
            //delete the player from the old trees and insert to the new trees
            oldPlayerGroupScoreTree.deleteNode(PlayerSeat(currentPlayer));
            oldPlayerSystemScoreTree.deleteNode(PlayerSeat(currentPlayer));

            newPlayerGroupScoreTree.insertNode(PlayerSeat(currentPlayer), PlayerSeat(currentPlayer));
            newPlayerSystemScoreTree.insertNode(PlayerSeat(currentPlayer), PlayerSeat(currentPlayer));
        }

    }catch(const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    */
    return SUCCESS;
}

StatusType OctopusGame::GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double * players){
    if(players == NULL || GroupID < 0 || GroupID > k){
        return INVALID_INPUT;
    }

    try{
        
        Group& playersGroup = GroupsUF.findByID(GroupID);
        Player maxDummyPlayer(-1, GroupID, score);
        Player minDummyPlayer(0,GroupID, score);
        maxDummyPlayer.setLevel(higherLevel);
        minDummyPlayer.setLevel(lowerLevel);
        Player* maxPlayer = &maxDummyPlayer;
        Player* minPlayer = &minDummyPlayer;
        
        playersGroup.insertPlayer(maxPlayer);
        playersGroup.insertPlayer(minPlayer);

        Score_structure* groupSS = playersGroup.get_groupSS();
        AVL_Tree<PlayerSeat,PlayerSeat>& scorePlayersTree = groupSS[score].get_ScoreTree();
        PlayerSeat maxPlayerSeat(maxPlayer);
        PlayerSeat minPlayerSeat(minPlayer);
        double max_index = scorePlayersTree.findIndex(maxPlayerSeat);
        double min_index = scorePlayersTree.findIndex(minPlayerSeat);
        Node_ptr<PlayerSeat, PlayerSeat> root = scorePlayersTree.getRoot();
        double total_players = root->getRank();

        double difference = max_index - min_index - 2;
        if(lowerLevel <= 0){
            double zero_counter = groupSS->get_ZeroCounter();
            difference += zero_counter;
        }
        
        if(difference <= 0){
            return FAILURE;
        }
        *players = (difference*100)/total_players;
        playersGroup.removePlayer(maxPlayer);
        playersGroup.removePlayer(minPlayer);
        
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
        Node_ptr<PlayerSeat,PlayerSeat> n_minus_m_player= all_players_in_group_tree.select(index_to_select);
        int n_minus_m_player_level=n_minus_m_player->getValue().getPlayerOnSeat()->getLevel();
        int res_sum = sum- sum_of_smaller_levels+n_minus_m_player_level;//the sum of levels of m highest level players
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
    

