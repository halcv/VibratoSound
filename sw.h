#ifndef _SW_H_
#define _SW_H_

#include "board.h"
#include "timer.h"
#include "soundproc.h"
#include "pwmproc.h"

typedef enum {
    SW_NAME_VIBRATO_ONOFF,
    SW_NAME_SOUND_ONOFF,
    SW_NAME_MAX
} E_SW_NAME;

typedef enum {
    SW_STATE_OFF,
    SW_STATE_ON,
    SW_STATE_LONG_ON
} E_SW_STATE;

typedef struct {
    E_SW_STATE eNowState;
    int iLongOnCounter;
} T_SW_STATUS;

class CSw {
  public:
    CSw(CTimer* pTimer,CPwmProc* pPwmProc,CSoundProc* pSoundProc);
    void vSwStateMachine();
    
  private:
    void vOffToOff(E_SW_NAME eSwName);
    void vOffToOn(E_SW_NAME eSwName);
    void vOnToOn(E_SW_NAME eSwName);
    void vOnToOff(E_SW_NAME eSwName);
    void vOnToLongOn(E_SW_NAME eSwName);
    void vLongOnToLongOn(E_SW_NAME eSwName);
    void vLongOnToOff(E_SW_NAME eSwName);
    void vOn(E_SW_NAME eSwName);
    void vLongOn(E_SW_NAME eSwName);
    void vOff(E_SW_NAME eSwName);
    int iGetPort(E_SW_NAME eSwName);
    CTimer* m_pTimer;
    CPwmProc* m_pPwmProc;
    CSoundProc* m_pSoundProc;
    T_SW_STATUS m_tSwStatus[SW_NAME_MAX];
    int m_iLongOnCounter;
};

#endif // _SW_H_
