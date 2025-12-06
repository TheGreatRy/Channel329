#pragma once

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

};