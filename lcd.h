#ifndef _LCD_H_
#define _LCD_H_

#include "board.h"
#include "timer.h"

typedef struct {
    boolean isNowOn;
    boolean isRequestOn;
} S_VIBRATO_STATE;

class CLcd {
  public:
    CLcd(CTimer* pTimer);
    void vLcdProcess();
    void vDispVibratoStateRequest(boolean isOn);
  private:
    void vInitLcd();
    CTimer* m_pTimer;
    S_VIBRATO_STATE m_sVibratoState;
};

#endif // _LCD_H_
