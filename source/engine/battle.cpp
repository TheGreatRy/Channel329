#include "battle.h"

void Battle::SetAttacker(Character *attacker)
{
    m_attacker = attacker;
}

void Battle::SetDefender(Character *defender)
{
    m_defender = defender;
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

void Battle::CycleTones()
{
    auto skl = static_cast<TONE_SKILL>(m_tone_pos);
    Tone* tone_ptr = new Tone(skl);
    if (keysUp() & KEY_LEFT)
    {
        m_tone_text->ClearText();
        if (m_tone_pos > 1) m_tone_pos--;
        m_tone_text->AddText(tone_ptr->GetSkillName());
        m_tone_text->WriteText();
    }
    else if (keysUp() & KEY_RIGHT)
    {
        m_tone_text->ClearText();
        if (m_tone_pos < 31) m_tone_pos++;
        m_tone_text->AddText(tone_ptr->GetSkillName());
        m_tone_text->WriteText();
    }
    NF_UpdateTextLayers();
}

void Battle::CycleTopics()
{
    auto skl = static_cast<TOPIC_SKILL>(m_topic_pos);
    Topic* topic_ptr = new Topic(skl);
    if (keysUp() & KEY_LEFT)
    {
        m_topic_text->ClearText();
        if (m_topic_pos > 1) m_topic_pos--;
        m_topic_text->AddText(topic_ptr->GetSkillName());
        m_topic_text->WriteText();
    }
    else if (keysUp() & KEY_RIGHT)
    {
        m_topic_text->ClearText();
        if (m_topic_pos < 5) m_topic_pos++;
        m_topic_text->AddText(topic_ptr->GetSkillName());
        m_topic_text->WriteText();
    }
    NF_UpdateTextLayers();
}

/// @brief Checks the attacker's phrase against the defender. 0 is `NEGATIVE`, 1 is `UNKNOWN`, 2 is `POSITIVE KNOWN`, 
// 3 is `NEUTRAL KNOWN`, 4 is `POSITIVE INDIFFERENT`, 5 is `NEUTRAL INDIFFERENT`
/// @param atk_phr_index 
/// @return the defender phrase that corresponds to the given tone and topic
Phrase* Battle::CheckAttackPhrase(int atk_phr_index)
{
    Tone* atk_tone = new Tone{m_attack_phrases[atk_phr_index]->m_phrase_tone, m_defender->m_tones[atk_phr_index]->m_tone_type};
    Topic* atk_topic = new Topic{m_attack_phrases[atk_phr_index]->m_phrase_topic, m_defender->m_topics[atk_phr_index]->m_topic_type};

    //search for the attacker's tone in the defenders list of tones
    u32 tone_index = -1;
    for (u32 i = 0; i < m_defender->m_tones.size(); i++)
    {
        tone_index = (m_defender->m_tones[i] == atk_tone) ? i : -1;
        if (tone_index == i) break;
    }

    if (tone_index != 0)
    {
        switch(atk_tone->m_tone_type)
        {
            case TONE_TYPE_POSITIVE:
                m_attacker_advantage = true;
                break;
            case TONE_TYPE_NEUTRAL:
                m_attacker_advantage = false;
                break;
            case TONE_TYPE_NEGATIVE:
                return m_defend_phrases[0];
        }
    }

     //search for the attacker's tone in the defenders list of tones
    u32 topic_index = -1;
    for (u32 i = 0; i < m_defender->m_topics.size(); i++)
    {
        topic_index = (m_defender->m_topics[i] == atk_topic) ? i : -1;
        if (topic_index == i) break;
    }

    if (topic_index != 0)
    {
        switch(atk_topic->m_topic_type)
        {
            case TOPIC_TYPE_KNOWN:
                if (atk_tone->m_tone_type == TONE_TYPE_POSITIVE) return m_defend_phrases[2];
                else return m_defend_phrases[3];
                case TOPIC_TYPE_INDIFF:
                if (atk_tone->m_tone_type == TONE_TYPE_POSITIVE) return m_defend_phrases[4];
                else return m_defend_phrases[5];
            case TOPIC_TYPE_UNKNOWN:
                return m_defend_phrases[1];
        }
    }
    return new Phrase{"I don't think I understand...", TONE_SKILL_DEFAULT, TOPIC_SKILL_DEFAULT, PHRASE_TYPE_DEFEND};
}