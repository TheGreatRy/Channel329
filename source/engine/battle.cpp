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

void Battle::AddMultiplePhrases(Phrase *phrases[])
{
    for (int i = 0; i < sizeof(phrases) / sizeof(*phrases); i++)
    {
        AddSinglePhrase(phrases[i]);
    }
}

Character *Battle::ResolveTurn(Phrase *attack_phrase)
{
    bool attacker_adv = false;

    // search for the tone in the defender's tone list
    int found_tone = -1;
    for (int i = 0; i < m_defender.m_tones.size(); i++)
    {
        found_tone = (attack_phrase->m_tone_skill == m_defender.m_tones[i]->m_skill) ? i : -1;
        if (attack_phrase->m_tone_skill == m_defender.m_tones[i]->m_skill)
            break;
    }

    // if tone is valid
    if (found_tone > -1)
    {
        switch (m_defender.m_tones[found_tone]->m_type)
        {
        // Attacker has the advantage
        case TONE_TYPE_POSITIVE:
            attacker_adv = true;
            break;

        // Attacker has no advantage but hasn't lost
        case TONE_TYPE_NEUTRAL:
            attacker_adv = false;
            break;

        // Attacker lost tone check, they will not get information
        case TONE_TYPE_NEGATIVE:
            return &m_defender;
            break;

        // Invalid attack (constructor should not allow this but just in case)
        default:
            return &m_defender;
        }
    }
    // defender does not have this tone in their list, defender wins
    else
        return &m_defender;

    // search for the topic in the defender's topic list
    int found_topic = -1;
    for (int i = 0; i < m_defender.m_topics.size(); i++)
    {
        found_topic = (attack_phrase->m_topic_skill == m_defender.m_topics[i]->m_skill) ? i : -1;
        if (attack_phrase->m_topic_skill == m_defender.m_topics[i]->m_skill)
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

        // Defender doesnt have enough useful information. Defender wins if tone was neutral, but attacker wins if it was positive (they get a hint!)
        case TOPIC_TYPE_INDIFF:
            if (attacker_adv)
                return &m_attacker;
            else
                return &m_defender;

        // Defender does not know anything about the topic, defender wins
        case TOPIC_TYPE_UNKNOWN:
            return &m_defender;

        // Invalid attack (constructor should not allow this but just in case)
        default:
            return &m_defender;
        }
    }
    // defender does not have this topic in their list, defender wins
    else
        return &m_defender;

    return &m_defender;
}