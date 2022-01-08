#include "PlayerSeat.h"

void updatePlayerSeatGroup(Node_ptr<PlayerSeat, PlayerSeat> player_seat)
{
}
Player *PlayerSeat::getPlayerOnSeat() const
{
    return player_on_seat;
}
bool operator<(PlayerSeat const &player_seat_1, PlayerSeat const &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) < *(player_seat_2.getPlayerOnSeat());
}
bool operator<=(PlayerSeat const &player_seat_1, PlayerSeat const &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) <= *(player_seat_2.getPlayerOnSeat());
}
bool operator>(PlayerSeat const &player_seat_1, PlayerSeat const &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) > *(player_seat_2.getPlayerOnSeat());
}
bool operator>=(PlayerSeat const &player_seat_1, PlayerSeat const &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) >= *(player_seat_2.getPlayerOnSeat());
}
bool operator==(PlayerSeat const &player_seat_1, PlayerSeat const &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) == *(player_seat_2.getPlayerOnSeat());
}
bool operator!=(PlayerSeat const &player_seat_1, PlayerSeat const &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) != *(player_seat_2.getPlayerOnSeat());
}
/*
bool operator<(const PlayerSeat &player_seat_1, const PlayerSeat &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) < *(player_seat_2.getPlayerOnSeat());
}
bool operator<=(const PlayerSeat &player_seat_1, const PlayerSeat &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) <= *(player_seat_2.getPlayerOnSeat());
}
bool operator>(const PlayerSeat &player_seat_1, const PlayerSeat &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) > *(player_seat_2.getPlayerOnSeat());
}
bool operator>=(const PlayerSeat &player_seat_1, const PlayerSeat &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) >= *(player_seat_2.getPlayerOnSeat());
}
bool operator==(const PlayerSeat &player_seat_1, PlayerSeat &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) == *(player_seat_2.getPlayerOnSeat());
}
bool operator!=(const PlayerSeat &player_seat_1, PlayerSeat &player_seat_2)
{
    return *(player_seat_1.getPlayerOnSeat()) != *(player_seat_2.getPlayerOnSeat());
}
*/
