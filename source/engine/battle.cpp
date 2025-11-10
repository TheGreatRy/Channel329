#include "battle.h"

void Battle::SetAttacker(Character *attacker)
{
    m_attacker = *attacker;
}

void Battle::SetDefender(Character *defender)
{
    m_defender = *defender;
}

void Battle::AddSinglePhrase(Phrase* phrase)
{
    switch (phrase->m_type)
    {
        case PHRASE_TYPE_ATTACK:
            m_attack_phrases.push_back(phrase);
            break;
        case PHRASE_TYPE_DEFEND:
            m_defend_phrases.push_back(phrase);
            break;
        case PHRASE_TYPE_BOSS:
            m_boss_phrases.push_back(phrase);
            break;
    }
}

void Battle::AddMultiplePhrases(Phrase* phrases[])
{
    for (int i = 0; i < sizeof(phrases)/sizeof(*phrases); i++)
    {
        AddSinglePhrase(phrases[i]);
    }
}

void Battle::ResolveTone()
{
}

void Battle::ResovleTopic()
{
}
