#include "player.h"
#include "constants.h"

#include <fstream>
#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <time.h>

using namespace std;

Player::Player(int lv, int sch)
{
	level = lv;
	school = sch;
	set_hp_mana();
}

// Shuffle the deck of cards
void Player::shuffle()
{
	// Move both deck and discard pile into discard buffer
	while (!deck.empty())
	{
		shuffle_buffer.push_back(deck.top());
		deck.pop();
	}
	while (!discard.empty())
	{
		shuffle_buffer.push_back(discard.top());
		discard.pop();
	}

	// Apply Fisher-Yates shuffle algorithm to buffer vector
	for (int i = shuffle_buffer.size()-1; i > 0; i--)
	{
		srand((unsigned int)time(NULL));
		int j = rand() % (i + 1);
		Spell temp = shuffle_buffer[i];
		shuffle_buffer[i] = shuffle_buffer[j];
		shuffle_buffer[j] = temp;
	}

	// Push back into deck
	while (!shuffle_buffer.empty())
	{
		deck.push(shuffle_buffer[shuffle_buffer.size() - 1]);
		shuffle_buffer.pop_back();
	}
}

// Add a card to the deck
void Player::add_to_deck(Spell card)
{
	deck.push(card);
}

void Player::init_player()
{
	// Shuffle the deck
	shuffle();

	// Add the top seven cards of the hand to the deck if full, otherwise add whatever is in there
	if (deck.size() < 7)
	{
		while (!deck.empty())
		{
			hand.push_back(deck.top());
			deck.pop();
		}
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			hand.push_back(deck.top());
			deck.pop();
		}
	}
}

// Returns a pointer to the array of spells that correspond to the player's hand
vector<Spell> Player::get_hand()
{
	return hand;
}

void Player::set_hp_mana()
{
	// Parse the level table
	ifstream level_table(CONSTANTS::LEVEL_CHART_PATH);
	string line;

	for (int i = 1; i < level; i++) getline(level_table, line);
	for (int i = 1; i < school; i++) getline(level_table, line, '\t');

	getline(level_table, line, '\t'); // We should be at the desired position now
	hp = atoi(line.c_str());

	// Determine mana
	for (int i = school + 1; i < 8; i++) getline(level_table, line, '\t');
	getline(level_table, line, '\t');
	mana = atoi(line.c_str());
}