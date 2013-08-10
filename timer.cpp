#include "timer.h"

#define SOUND_TIME_MAX (50) // 500ms
#define SW_TIME_MAX     (2) // 20ms
#define LCD_TIME_MAX    (2) // 20ms

CTimer::CTimer()
{
    m_nSoundTime = 0;
    m_nSwTime = 0;
    m_nLcdTime = 0;
}

void CTimer::vSoundIncTime()
{
    if (m_nSoundTime < SOUND_TIME_MAX) {
        m_nSoundTime++;
    }
}

void CTimer::vSwIncTime()
{
    if (m_nSwTime < SW_TIME_MAX) {
        m_nSwTime++;
    }
}

void CTimer::vLcdIncTime()
{
    if (m_nLcdTime < LCD_TIME_MAX) {
        m_nLcdTime++;
    }
}

boolean CTimer::isCheckSoundTime()
{
    boolean bRet = false;

    if (m_nSoundTime >= SOUND_TIME_MAX) {
        m_nSoundTime = 0;
        bRet = true;
    }

    return bRet;
}

boolean CTimer::isCheckSwTime()
{
    boolean bRet = false;

    if (m_nSwTime >= SW_TIME_MAX) {
        m_nSwTime = 0;
        bRet = true;
    }

    return bRet;
}

boolean CTimer::isCheckLcdTime()
{
    boolean bRet = false;

    if (m_nLcdTime >= LCD_TIME_MAX) {
        m_nLcdTime = 0;
        bRet = true;
    }

    return bRet;
}
