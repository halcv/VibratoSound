#ifndef _TIMER_H_
#define _TIMER_H_

#include "board.h"

class CTimer {
  public:
    CTimer();
    void vSoundIncTime();
    boolean isCheckSoundTime();
    void vSwIncTime();
    boolean isCheckSwTime();
    void vLcdIncTime();
    boolean isCheckLcdTime();
  private:
    volatile int m_nSoundTime;
    volatile int m_nSwTime;
    volatile int m_nLcdTime;
};

#endif
