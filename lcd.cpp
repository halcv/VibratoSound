#include <LiquidCrystal.h>
#include "lcd.h"

static LiquidCrystal g_Lcd(12,11,5,4,3,2);

CLcd::CLcd(CTimer* pTimer)
{
    m_pTimer = pTimer;
    vInitLcd();
    m_sVibratoState.isNowOn = true;
    m_sVibratoState.isRequestOn = true;
}

void CLcd::vLcdProcess()
{
    if (m_pTimer->isCheckLcdTime() == false) {
        return;
    }

    if (m_sVibratoState.isNowOn != m_sVibratoState.isRequestOn) {
        g_Lcd.setCursor(0,1);
        g_Lcd.print("   ");
        g_Lcd.setCursor(0,1);
        if (m_sVibratoState.isRequestOn == true) {
            g_Lcd.print("ON");
        } else {
            g_Lcd.print("OFF");
        }
        m_sVibratoState.isNowOn = m_sVibratoState.isRequestOn;
    }
}

void CLcd::vInitLcd()
{
    g_Lcd.begin(16,2);
    g_Lcd.setCursor(0,0);
    g_Lcd.print("Vibrato Sound.");
    g_Lcd.setCursor(0,1);
    g_Lcd.print("ON");
}

void CLcd::vDispVibratoStateRequest(boolean isOn)
{
    m_sVibratoState.isRequestOn = isOn;
}

