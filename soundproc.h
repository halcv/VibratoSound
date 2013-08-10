#ifndef _SOUND_PROC_H_
#define _SOUND_PROC_H_

#include "board.h"
#include "timer.h"
#include "pwmProc.h"

class CSoundProc {
  public:
    CSoundProc(CTimer* pTimer,CPwmProc* pPwmProc);
    void vSoundProcess();
    void vSoundOnOffRequest();
    boolean isVibratoOn();
    boolean isSoundOn();
  private:
    CTimer* m_pTimer;
    CPwmProc* m_pPwmProc;
    int m_nSoundPos;
    boolean m_isSoundStart;
};

#endif // _SOUND_PROC_H_
