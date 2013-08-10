#include <TimerOne.h>
#include "pwmproc.h"

CPwmProc::CPwmProc(CLcd* pLcd)
{
    m_pLcd = pLcd;
    m_nDuty = 0;
    m_nVibrato = 0;
    m_isVibratoOn = true;
}

void CPwmProc::vPwmProcess()
{
    Timer1.pwm(SOUND_PORT,m_nDuty);
    if (m_nDuty == 0) {
        return;
    }
    if (m_isVibratoOn == false) {
        return;
    }
    m_nDuty += m_nVibrato;
    if (m_nDuty >= 768 || m_nDuty <= 256 ) {
        m_nVibrato *= -1;
    }
}

void CPwmProc::vSetPwmRequest(int microsec)
{
    Timer1.setPeriod(microsec);
    m_nDuty = 512;
    m_nVibrato = microsec / 160;
}

void CPwmProc::vChangeVibratoRequest()
{
    m_isVibratoOn = !m_isVibratoOn;
    m_pLcd->vDispVibratoStateRequest(m_isVibratoOn);
}

void CPwmProc::vSoundOffRequest()
{
    m_nDuty = 0;
}
