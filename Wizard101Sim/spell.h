#pragma once

#include "spell_effect.h"
#include <string>
#include <vector>

using namespace std;

class Spell
{
public:
	// Constructor
	Spell(int spell_id, const char* spell_name, const char* spell_description, int spell_school, int spell_accuracy, int spell_pips, int spell_type, bool spell_shadow);

	// Prints the details of the spell
	void print_details();

	// Prints the effects of the spell
	void print_effects();

	// Sets the effect(s) of the spell
	void set_effects(vector<Spell_Effect> spell_effects);
private:
	string name, description;
	int school, accuracy, pips, type, id;
	bool shadow;
	vector<Spell_Effect> effects;
};