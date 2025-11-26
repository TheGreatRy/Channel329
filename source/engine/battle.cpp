#include "battle.h"

void Battle::SetAttacker(Character *attacker)
{
    m_attacker = *attacker;
}

void Battle::SetDefender(Character *defender)
{
    m_defender = *defender;
}

void Battle::AddSinglePhrase(Phrase *phrase)
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

void Battle::AddMultiplePhrases(Phrase *phrases[], int size)
{
    for (int i = 0; i < size; i++)
    {
        AddSinglePhrase(phrases[i]);
    }
}

Character *Battle::ResolveTurn(int index)
{

    // search for the tone in the defender's tone list
    int found_tone = -1;
    for (int i = 0; i < m_defender.m_tones.size(); i++)
    {
        found_tone = (m_attack_phrases[index]->m_tone_skill == m_defender.m_tones[i]->m_skill) ? i : -1;
        if (found_tone == i) 
            break;
    }

    // if tone is valid
    if (found_tone > -1)
    {
        switch (m_defender.m_tones[found_tone]->m_type)
        {
        // Attacker has the advantage
        case TONE_TYPE_POSITIVE:
            m_attacker_advantage = true;
            break;

        // Attacker has no advantage but hasn't lost
        case TONE_TYPE_NEUTRAL:
            m_attacker_advantage = false;
            break;

        // Attacker lost tone check, they will not get information
        // note to add this to their memory object once that's done so they do not talk to you initally (you have to fight for it)
        case TONE_TYPE_NEGATIVE:
            return &m_defender;
            break;
        }
    }

    // search for the topic in the defender's topic list
    int found_topic = -1;
    for (int i = 0; i < m_defender.m_topics.size(); i++)
    {
        found_topic = (m_attack_phrases[index]->m_topic_skill == m_defender.m_topics[i]->m_skill) ? i : -1;
        if (found_topic == i)
            break;
    }
    // if tone is valid
    if (found_topic > -1)
    {
        switch (m_defender.m_topics[found_topic]->m_type)
        {
        // Defender has knowledge about the topic, attacker wins
        case TOPIC_TYPE_KNOWN:
            return &m_attacker;
            break;

        // Defender doesnt have enough useful information. Defender wins if tone was neutral, but attacker wins if it was positive (they get a hint!)
        case TOPIC_TYPE_INDIFF:
            if (m_attacker_advantage)
                return &m_attacker;
            else
                return &m_defender;
            break;
        // Defender does not know anything about the topic, defender wins
        case TOPIC_TYPE_UNKNOWN:
            return &m_defender;
            break;
        }
    }

        return &m_defender;
}