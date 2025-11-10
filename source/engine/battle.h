#pragma once

// C++ includes
#include <vector>

// Actors Folder
#include "../actors/character.h"

// Utilites Folder
#include "../utilities/phrase.h"

class Battle
{
public:
    Battle() = default;
    ~Battle() = default;

    std::vector<Phrase *> m_attack_phrases;
    std::vector<Phrase *> m_defend_phrases;
    std::vector<Phrase *> m_boss_phrases;

    Character m_attacker;
    Character m_defender;

    void SetAttacker(Character *attacker);
    void SetDefender(Character *defender);

    void AddSinglePhrase(Phrase *phrase);
    void AddMultiplePhrases(Phrase *phrases[]);

    Character *ResolveTurn(Phrase *attack_phrase);
};