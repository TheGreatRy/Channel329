#pragma once

enum TOPIC_SKILL
{
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

struct Topic
{
    public:
    TOPIC_SKILL m_skill;
    TOPIC_TYPE m_type;

    Topic(TOPIC_SKILL skill, TOPIC_TYPE type) :
        m_skill{skill},
        m_type{type}
    {}
    ~Topic() = default;

};