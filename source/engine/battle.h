#pragma once

//Actors
#include "../actors/character.h"
 

class Battle
{
    public:
    Battle() = default;
    ~Battle() = default;

    Character m_attacker;
    Character m_defender;



};