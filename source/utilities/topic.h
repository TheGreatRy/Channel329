#pragma once

#include <string>

enum TOPIC_SKILL
{
    TOPIC_SKILL_DEFAULT,
    TOPIC_SKILL_HISTORY,
    TOPIC_SKILL_PEOPLE,
    TOPIC_SKILL_UNDGR,
    TOPIC_SKILL_CRIME,
    TOPIC_SKILL_MAGIC
};

enum TOPIC_TYPE
{
    TOPIC_TYPE_KNOWN,
    TOPIC_TYPE_INDIFF,
    TOPIC_TYPE_UNKNOWN
};

class Topic
{
    public:
    TOPIC_SKILL m_topic_skill;
    TOPIC_TYPE m_topic_type;

    Topic(TOPIC_SKILL skill, TOPIC_TYPE type) :
        m_topic_skill{skill},
        m_topic_type{type}
    {}

    Topic(TOPIC_SKILL skill) :
        m_topic_skill{skill}
    {}
    
    ~Topic() = default;

    const char* GetSkillName()
    {
        std::string name;
        switch (m_topic_skill)
        {
            case TOPIC_SKILL_DEFAULT:
                name = "DEFAULT";
                break;
            case TOPIC_SKILL_HISTORY:
                name = "HISTORY";
                break;
            case TOPIC_SKILL_PEOPLE:
                name = "PEOPLE";
                break;
            case TOPIC_SKILL_UNDGR:
                name = "UNDERGROUND";
                break;
            case TOPIC_SKILL_CRIME:
                name = "CRIME";
                break;
            case TOPIC_SKILL_MAGIC:
                name = "MAGIC";
                break;
        }
        return name.c_str();
    }
};