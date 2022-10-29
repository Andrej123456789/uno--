/**
 * @author: Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: runtime.h, header file for all runtime informations
*/

#pragma once

#include <stdbool.h>
#include "vec.h"

/* Max number of players */
#define MAX_PLAYERS 20

/**
 * Struct which contains the settings of the game.
 * @param players - number of players
 * @param special_mode - special mode (0 - off, 1 - on)
 * @param debug_mode - debug mode (0 - off, 1 - on)
 * @param swap_card - swap card (0 - off, 1 - on)
 * @param colors - colors (0 - off, 1 - on)
 * @param ai_sequence - contains which players are AI (needs to be written reversed)
 * @param ai_array_sequence - ai_sequence in array form
 * @param network_sequence - contains which players are network players (needs to be written reversed)
 * @param network_array_sequence - network_sequence in array form
*/
typedef struct settings_T
{
    int players;
    int special_mode;
    int debug_mode;
    int swap_card;
    int colors;
    char json_ai_sequence[MAX_PLAYERS];
    char json_network_sequence[MAX_PLAYERS];
} Settings;

/**
 * Struct which contains the cards information.
 * @param number - the number of the card
 * @param color - the color of the card
*/
typedef struct cards_T
{
    int number;
    int color;
} Cards;

/**
 * Struct which contains informations about player.
 * @param cards - array of cards which player has
 * @param cards.number - number of card
 * @param cards.color - color of card
 * @param number_of_cards - number of cards which player has
 * @param points - points which player has
 * @param legal_four - can player legally play wild draw four card
*/
typedef struct player_T
{
    Cards cards[52];
    int number_of_cards;
    int points;
    bool legal_four;
    Vector test;
    Vector new_cards;
} Player;

/**
 * Struct for holding information during the game.
 * @param available_cards - cards that are available for the players
 * @param current_card_id - current card id
 * @param player_turn - player turn
 * @param isPositive - determines if the turn is positive or negative.
 * @param top_card - array which holds information about the top card
 * @param top_card.number - number of the top card
 * @param top_card.color - color of the top card
*/
typedef struct runtime_T
{
    int avabible_cards;
    int current_card_id;
    int player_turn;
    bool isPositive;
    Cards top_card[1];
} Runtime;

/**
 * Everything releated to points in game is here, even if it is should be in another struct.
 * @param temp_points - points in the round
 * @param match_points - points needed to win the match
 * @param round_winner - player id who won the round
 * @param match_winner - player id who won the match
 * @param match_ended - if the match has ended
 * @param alReadyCreated - if file for points is already created
*/
typedef struct points_T
{
    int temp_points;
    int match_points;
    int round_winner;
    int match_winner;
    bool match_ended;
    bool alReadyCreated;
} Points;

/** Struct which holds graphics (theme releated stuff mostly) informations during runtime
 * @param dark - light or dark theme
*/
typedef struct theme_T
{
    bool dark;
} Theme;
