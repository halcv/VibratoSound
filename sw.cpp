#include "sw.h"

#define LONG_ON_COUNTER_MAX 100

CSw::CSw(CTimer* pTimer,CPwmProc* pPwmProc,CSoundProc* pSoundProc)
{
    m_pTimer = pTimer;
    m_pPwmProc = pPwmProc;
    m_pSoundProc = pSoundProc;
    m_iLongOnCounter = 0;
    for (int i = 0;i < SW_NAME_MAX;i++) {
        m_tSwStatus[i].eNowState = SW_STATE_OFF;
        m_tSwStatus[i].iLongOnCounter = 0;
    }
}

void CSw::vSwStateMachine()
{
    if (m_pTimer->isCheckSwTime() == false) {
        return;
    }
    
    for (int i = 0;i < SW_NAME_MAX;i++) {
        int iNewState = digitalRead(iGetPort((E_SW_NAME)i));

        switch(m_tSwStatus[i].eNowState) {
        case SW_STATE_OFF:
            if (iNewState == LOW) {
                vOffToOff((E_SW_NAME)i);
            } else {
                vOffToOn((E_SW_NAME)i);
            }
            break;
        case SW_STATE_ON:
            if (iNewState == LOW) {
                vOnToOff((E_SW_NAME)i);
            } else {
                vOnToOn((E_SW_NAME)i);
            }
            break;
        case SW_STATE_LONG_ON:
            if (iNewState == LOW) {
                vLongOnToOff((E_SW_NAME)i);
            } else {
                vLongOnToLongOn((E_SW_NAME)i);
            }
            break;
        }
    }
}

int CSw::iGetPort(E_SW_NAME eSwName)
{
    int iPort = VIBRATO_SW_PORT;
    switch(eSwName) {
    case SW_NAME_VIBRATO_ONOFF:
        iPort = VIBRATO_SW_PORT;
        break;
    case SW_NAME_SOUND_ONOFF:
        iPort = SOUND_SW_PORT;
        break;
    }
    
    return iPort;
}

void CSw::vOffToOff(E_SW_NAME eSwName)
{
    m_tSwStatus[eSwName].eNowState = SW_STATE_OFF;
    m_tSwStatus[eSwName].iLongOnCounter = 0;
}

void CSw::vOffToOn(E_SW_NAME eSwName)
{
    m_tSwStatus[eSwName].eNowState = SW_STATE_ON;
    m_tSwStatus[eSwName].iLongOnCounter = 0;
    vOn(eSwName);
}

void CSw::vOnToOff(E_SW_NAME eSwName)
{
    m_tSwStatus[eSwName].eNowState = SW_STATE_OFF;
    m_tSwStatus[eSwName].iLongOnCounter = 0;
    vOff(eSwName);
}

void CSw::vOnToOn(E_SW_NAME eSwName)
{
    m_tSwStatus[eSwName].eNowState = SW_STATE_ON;
    m_tSwStatus[eSwName].iLongOnCounter++;
    if (m_tSwStatus[eSwName].iLongOnCounter >= LONG_ON_COUNTER_MAX) {
        vOnToLongOn(eSwName);
    }
}

void CSw::vOnToLongOn(E_SW_NAME eSwName)
{
    m_tSwStatus[eSwName].eNowState = SW_STATE_LONG_ON;
    m_tSwStatus[eSwName].iLongOnCounter = 0;
}

void CSw::vLongOnToLongOn(E_SW_NAME eSwName)
{
    m_tSwStatus[eSwName].eNowState = SW_STATE_LONG_ON;
    m_tSwStatus[eSwName].iLongOnCounter = 0;
    vLongOn(eSwName);
}

void CSw::vLongOnToOff(E_SW_NAME eSwName)
{
    m_tSwStatus[eSwName].eNowState = SW_STATE_OFF;
    m_tSwStatus[eSwName].iLongOnCounter = 0;
    vOff(eSwName);
}

void CSw::vOn(E_SW_NAME eSwName)
{
    switch(eSwName) {
    case SW_NAME_VIBRATO_ONOFF:
        m_pPwmProc->vChangeVibratoRequest();
        break;
    case SW_NAME_SOUND_ONOFF:
        m_pSoundProc->vSoundOnOffRequest();
        break;
    }
}

void CSw::vLongOn(E_SW_NAME eSwName)
{
    switch(eSwName) {
    case SW_NAME_VIBRATO_ONOFF:
        break;
    case SW_NAME_SOUND_ONOFF:
        break;
    }
}

void CSw::vOff(E_SW_NAME eSwName)
{
    switch(eSwName) {
    case SW_NAME_VIBRATO_ONOFF:
        break;
    case SW_NAME_SOUND_ONOFF:
        break;
    }
}
