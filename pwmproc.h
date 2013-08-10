#ifndef _PWM_PROC_H_
#define _PWM_PROC_H_

#include "board.h"
#include "lcd.h"

class CSoundProc;

class CPwmProc {
  public:
    CPwmProc(CLcd* pLcd);
    void vPwmProcess();
    void vSetPwmRequest(int microsec);
    void vChangeVibratoRequest();
    void vSoundOffRequest();
    
  private:
    CLcd* m_pLcd;
    int m_nDuty;
    int m_nVibrato;
    boolean m_isVibratoOn;
};

#endif // _SOUND_PROC_H_
