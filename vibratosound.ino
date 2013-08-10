#include <LiquidCrystal.h>
#include <MsTimer2.h>
#include <TimerOne.h>
#include "board.h"
#include "timer.h"
#include "soundproc.h"
#include "pwmproc.h"
#include "lcd.h"
#include "sw.h"

static void vInitTimer();
static void vTimer1Interrupt();
static void vTimer2Interrupt();
static void vInitPort();
static void vInitInstance();

static CTimer* g_pTimer = NULL;
static CSoundProc* g_pSoundProc = NULL;
static CPwmProc* g_pPwmProc = NULL;
static CLcd* g_pLcd = NULL;
static CSw* g_pSw = NULL;

void setup()
{
    vInitPort();
    vInitInstance();
    vInitTimer();
}

void loop()
{
    g_pSoundProc->vSoundProcess();
    g_pSw->vSwStateMachine();
    g_pLcd->vLcdProcess();
}

static void vTimer1Interrupt()
{
    g_pPwmProc->vPwmProcess();
}

static void vTimer2Interrupt()
{
    g_pTimer->vSoundIncTime();
    g_pTimer->vSwIncTime();
    g_pTimer->vLcdIncTime();
}

static void vInitTimer()
{
    MsTimer2::set(10,vTimer2Interrupt);
    MsTimer2::start();
    Timer1.initialize();
    Timer1.attachInterrupt(vTimer1Interrupt);
}

static void vInitInstance()
{
    g_pTimer = new CTimer();
    g_pLcd = new CLcd(g_pTimer);
    g_pPwmProc = new CPwmProc(g_pLcd);
    g_pSoundProc = new CSoundProc(g_pTimer,g_pPwmProc);
    g_pSw = new CSw(g_pTimer,g_pPwmProc,g_pSoundProc);
}

static void vInitPort()
{
    pinMode(SOUND_PORT,OUTPUT);
    digitalWrite(SOUND_PORT,LOW);
    pinMode(VIBRATO_SW_PORT,INPUT);
    pinMode(SOUND_SW_PORT,INPUT);
}

