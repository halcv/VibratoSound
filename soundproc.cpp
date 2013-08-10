#include "soundproc.h"

#define SOUND_TABLE_MAX (22)

static int st_nSoundTable[] = {7634,6803,6061,5714,5102,4545,4049,3817,3401,3030,2865,2551,2272,2024,1912,
                               1703,1517,1433,1276,1136,1012,955};

CSoundProc::CSoundProc(CTimer* pTimer,CPwmProc* pPwmProc)
{
    m_pTimer = pTimer;
    m_pPwmProc = pPwmProc;
    m_nSoundPos = 0;
     m_isSoundStart = false;
}

void CSoundProc::vSoundProcess()
{
    if (m_pTimer->isCheckSoundTime() == false) {
        return;
    }

    if (m_isSoundStart == false) {
        return;
    }
    
    m_pPwmProc->vSetPwmRequest(st_nSoundTable[m_nSoundPos]);
    m_nSoundPos++;
    if (m_nSoundPos >= SOUND_TABLE_MAX) {
        m_nSoundPos = 0;
    }
}

void CSoundProc::vSoundOnOffRequest()
{
    if (m_isSoundStart == false) {
        m_nSoundPos = 0;
    }
    m_pPwmProc->vSoundOffRequest();
    m_isSoundStart = !m_isSoundStart;
}

