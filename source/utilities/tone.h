#pragma once

#include <string>

enum TONE_SKILL
{
    TONE_SKILL_DEFAULT,
    TONE_SKILL_AUTHOR,
    TONE_SKILL_CARING,
    TONE_SKILL_CASUAL,
    TONE_SKILL_CHATTY,
    TONE_SKILL_CHEER,
    TONE_SKILL_CONSERV,
    TONE_SKILL_DIRECT,
    TONE_SKILL_EDGY,
    TONE_SKILL_ENTHUS,
    TONE_SKILL_FORMAL,
    TONE_SKILL_FRANK,
    TONE_SKILL_FRIEND,
    TONE_SKILL_HUMOR,
    TONE_SKILL_INFORM,
    TONE_SKILL_IRREV,
    TONE_SKILL_PASSION,
    TONE_SKILL_PLAY,
    TONE_SKILL_PROFESS,
    TONE_SKILL_PROVOC,
    TONE_SKILL_QUIRKY,
    TONE_SKILL_RESON,
    TONE_SKILL_RESPECT,
    TONE_SKILL_ROM,
    TONE_SKILL_SAR,
    TONE_SKILL_SER,
    TONE_SKILL_SNARKY,
    TONE_SKILL_SYMPATH,
    TONE_SKILL_TRENDY,
    TONE_SKILL_TRUST,
    TONE_SKILL_UNAPOLO,
    TONE_SKILL_WITTY
};

enum TONE_TYPE
{
    TONE_TYPE_NONE,
    TONE_TYPE_POSITIVE,
    TONE_TYPE_NEUTRAL,
    TONE_TYPE_NEGATIVE

};

class Tone
{
    public:
    TONE_SKILL m_tone_skill;
    TONE_TYPE m_tone_type;

    Tone(TONE_SKILL skill, TONE_TYPE type) :
        m_tone_skill{skill},
        m_tone_type{type}
    {}
    
    ~Tone() = default;

    const char *GetSkillName()
    {
        std::string name;
        switch (m_tone_skill)
        {
            case TONE_SKILL_DEFAULT:
                name = "DEFAULT";
                break;
            case TONE_SKILL_AUTHOR:
                name = "AUTHORITIVE";
                break;
            case TONE_SKILL_CARING:
                name = "CARING";
                break;
            case TONE_SKILL_CASUAL:
                name = "CASUAL";
                break;
            case TONE_SKILL_CHATTY:
                name = "CHATTY";
                break;
            case TONE_SKILL_CHEER:
                name = "CHEERFUL";
                break;
            case TONE_SKILL_CONSERV:
                name = "CONSERVED";
                break;
            case TONE_SKILL_DIRECT:
                name = "DIRECT";
                break;
            case TONE_SKILL_EDGY:
                name = "EDGY";
                break;
            case TONE_SKILL_ENTHUS:
                name = "ENTHUSIASTIC";
                break;
            case TONE_SKILL_FORMAL:
                name = "FORMAL";
                break;
            case TONE_SKILL_FRANK:
                name = "FRANK";
                break;
            case TONE_SKILL_FRIEND:
                name = "FRIENDLY";
                break;
            case TONE_SKILL_HUMOR:
                name = "HUMOR";
                break;
            case TONE_SKILL_INFORM:
                name = "INFORMATIVE";
                break;
            case TONE_SKILL_IRREV:
                name = "IRREVERENT";
                break;
            case TONE_SKILL_PASSION:
                name = "PASSIONATE";
                break;
            case TONE_SKILL_PLAY:
                name = "PLAYFUL";
                break;
            case TONE_SKILL_PROFESS:
                name = "PROFESSIONAL";
                break;
            case TONE_SKILL_PROVOC:
                name = "PROVOCATIVE";
                break;
            case TONE_SKILL_QUIRKY:
                name = "QUIRKY";
                break;
            case TONE_SKILL_RESON:
                name = "RESONATING";
                break;
            case TONE_SKILL_RESPECT:
                name = "RESPECTFUL";
                break;
            case TONE_SKILL_ROM:
                name = "ROMANTIC";
                break;
            case TONE_SKILL_SAR:
                name = "SARCASTIC";
                break;
            case TONE_SKILL_SER:
                name = "SERVING";
                break;
            case TONE_SKILL_SNARKY:
                name = "SNARKY";
                break;
            case TONE_SKILL_SYMPATH:
                name = "SYMPATHETIC";
                break;
            case TONE_SKILL_TRENDY:
                name = "TRENDY";
                break;
            case TONE_SKILL_TRUST:
                name = "TRUSTING";
                break;
            case TONE_SKILL_UNAPOLO:
                name = "UNAPOLOGETIC";
                break;
            case TONE_SKILL_WITTY:
                name = "WITTY";
                break;
        }
        return name.c_str();
    }
};