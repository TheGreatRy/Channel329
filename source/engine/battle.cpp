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
    if (keysUp() & KEY_LEFT)
    {
        (m_tone_pos > 1) ? m_tone_pos-- : m_tone_pos = 1;
    }
    else if (keysUp() & KEY_RIGHT)
    {
        (m_tone_pos < 31) ? m_tone_pos++ : m_tone_pos = 31;
    }

    m_attk_tone = new Tone(static_cast<TONE_SKILL>(m_tone_pos));
    m_tone_text->SetText(m_attk_tone->GetSkillName(), false);
    m_tone_text->DisplayTextConsole(&m_tone_text->m_print_console);
    
    ValidateToneTopicChoice();
}

void Battle::CycleTopics()
{
    if (keysUp() & KEY_LEFT)
    {
        (m_topic_pos > 1) ? m_topic_pos-- : m_topic_pos = 1;
    }
    else if (keysUp() & KEY_RIGHT)
    {
        (m_topic_pos < 5) ? m_topic_pos++ : m_topic_pos = 5;
    }

    m_attk_topic = new Topic(static_cast<TOPIC_SKILL>(m_topic_pos));
    m_topic_text->SetText(m_attk_topic->GetSkillName(), false);
    m_topic_text->DisplayTextConsole(&m_topic_text->m_print_console);
    
    ValidateToneTopicChoice();
}

void Battle::ValidateToneTopicChoice()
{
    u32 attk_index = -1;
    for (u32 i = 0; i < m_attack_phrases.size(); i++)
    {
        attk_index = (m_attack_phrases[i]->m_phrase_tone == m_attk_tone->m_tone_skill && m_attack_phrases[i]->m_phrase_topic == m_attk_topic->m_topic_skill) ? i : -1;
        if (attk_index == i) break;

    }
    if (attk_index != -1)
    {
        m_battle_response->SetText(m_attack_phrases[attk_index]->m_text, false);
        
    }
    else
    {
        m_battle_response->SetText("(YOU STRUGGLE TO PHRASE IT THAT WAY...)", false);
    }

    m_battle_response->DisplayTextConsole(&m_battle_response->m_print_console);
}

/// @brief Checks the attacker's phrase against the defender. 0 is `NEGATIVE`, 1 is `UNKNOWN`, 2 is `POSITIVE KNOWN`, 
// 3 is `NEUTRAL KNOWN`, 4 is `POSITIVE INDIFFERENT`, 5 is `NEUTRAL INDIFFERENT` 
/// @return the defender phrase that corresponds to the given tone and topic
void Battle::CheckAttackPhrase()
{
    //search for the attacker's tone in the defenders list of tones
    u32 tone_index = -1;
    for (u32 i = 0; i < m_defender->m_tones.size(); i++)
    {
        tone_index = (m_defender->m_tones[i]->m_tone_skill == m_attk_tone->m_tone_skill) ? i : -1;
        if (tone_index == i) break;
    }

    if (tone_index != -1)
    {
        TONE_TYPE tty = m_defender->m_tones[tone_index]->m_tone_type;
        
        switch(tty)
        {
            case TONE_TYPE_POSITIVE:
                m_attacker_advantage = true;
                break;
            case TONE_TYPE_NEUTRAL:
                m_attacker_advantage = false;
                break;
            case TONE_TYPE_NEGATIVE:
                m_battle_response->SetText(m_defend_phrases[0]->m_text, false);
                return;
        }
    }
    else
    {
        m_battle_response->SetText("I DON'T THINK I UNDERSTAND...", false);
    }

     //search for the attacker's tone in the defenders list of tones
    u32 topic_index = -1;
    for (u32 i = 0; i < m_defender->m_topics.size(); i++)
    {
        topic_index = (m_defender->m_topics[i]->m_topic_skill == m_attk_topic->m_topic_skill) ? i : -1;
        if (topic_index == i) break;
    }

    if (topic_index != -1)
    {
        TOPIC_TYPE tty = m_defender->m_topics[topic_index]->m_topic_type;
        
        switch(tty)
        {
            case TOPIC_TYPE_KNOWN:
                if (m_defender->m_tones[tone_index]->m_tone_type == TONE_TYPE_POSITIVE) 
                    m_battle_response->SetText(m_defend_phrases[2]->m_text, false);
                else 
                    m_battle_response->SetText(m_defend_phrases[3]->m_text, false);
                break;
                case TOPIC_TYPE_INDIFF:
                if (m_defender->m_tones[tone_index]->m_tone_type  == TONE_TYPE_POSITIVE) 
                    m_battle_response->SetText(m_defend_phrases[4]->m_text, false);
                else 
                    m_battle_response->SetText(m_defend_phrases[4]->m_text, false);
                break;
            case TOPIC_TYPE_UNKNOWN:
                m_battle_response->SetText(m_defend_phrases[1]->m_text, false);
                break;
        }
    }

    else 
    {
        m_battle_response->SetText("I DON'T THINK I UNDERSTAND...", false);
    }

    m_battle_response->DisplayTextConsole(&m_battle_response->m_print_console);
}

void Battle::WaitForInput()
{
    while (1)
    {
        swiWaitForVBlank();

        scanKeys();

        if (keysUp() & KEY_A) break;
    }
}
