#include "bsp_pwm.h"


void fan_pwm_init(void)
{
//    hal_fan_pwm_init(0);
//    hal_fan_pwm_init(2);
    hal_fan_pwm_init(3);
    hal_fan_pwm_init(4);
}

void hal_fan_pwm_init(uint8_t fan)
{  
    uint32_t period;

    stc_timera_base_init_t stcTimeraInit;
    stc_timera_compare_init_t stcTimerCompareInit;
    stc_irq_regi_conf_t stcIrqRegiConf;

    /* configuration structure initialization */
    MEM_ZERO_STRUCT(stcTimeraInit);
    MEM_ZERO_STRUCT(stcIrqRegiConf);
    MEM_ZERO_STRUCT(stcTimerCompareInit);

    /* Configuration peripheral clock */
    PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIMA1|PWC_FCG2_PERIPH_TIMA2 | PWC_FCG2_PERIPH_TIMA3 | PWC_FCG2_PERIPH_TIMA4, Enable);
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_PERIPH_AOS, Enable);

    M4_TMRA_TypeDef *tim_base;
    en_timera_channel_t tim_ch;
    en_port_t tim_port;
    en_pin_t tim_pin;
    en_port_func_t tim_func;

    switch(fan) {
//    case 0:
//        tim_base = BOARD_PWM_CH0_BASE;
//        tim_ch   = BOARD_PWM_CH0_CH;
//        tim_port = BOARD_PWM_CH0_PORT;
//        tim_pin  = BOARD_PWM_CH0_PIN;
//        tim_func = BOARD_PWM_CH0_FUNC;
//        break;

//    case 1:
//        tim_base = BOARD_PWM_CH1_BASE;
//        tim_ch   = BOARD_PWM_CH1_CH;
//        tim_port = BOARD_PWM_CH1_PORT;
//        tim_pin  = BOARD_PWM_CH1_PIN;
//        tim_func = BOARD_PWM_CH1_FUNC;
//        break;

    case 2:                                //fan1       
        tim_base = BOARD_PWM_CH2_BASE;
        tim_ch   = BOARD_PWM_CH2_CH;
        tim_port = BOARD_PWM_CH2_PORT;
        tim_pin  = BOARD_PWM_CH2_PIN;
        tim_func = BOARD_PWM_CH2_FUNC;
        break;
    case 3:                              //fan2        
        tim_base = BOARD_PWM_CH3_BASE;
        tim_ch   = BOARD_PWM_CH3_CH;
        tim_port = BOARD_PWM_CH3_PORT;
        tim_pin  = BOARD_PWM_CH3_PIN;
        tim_func = BOARD_PWM_CH3_FUNC;
        break;		
		case 4:
        tim_base = BOARD_PWM_CH4_BASE;     //PB5  fan0
        tim_ch   = BOARD_PWM_CH4_CH;
        tim_port = BOARD_PWM_CH4_PORT;
        tim_pin  = BOARD_PWM_CH4_PIN;
        tim_func = BOARD_PWM_CH4_FUNC;
        break;

    default:
        return;
        break;
    }

    /* Configuration TIMERA compare pin */
    PORT_SetFunc(tim_port, tim_pin, tim_func, Disable);

// period = 100M / Div4 / frequency = 1250
// period = 84M / Div4 / frequency  = 1050
    period = 1050 - 1;

    stcTimeraInit.enClkDiv = TimeraPclkDiv4;
    stcTimeraInit.enCntMode = TimeraCountModeSawtoothWave;
    stcTimeraInit.enCntDir = TimeraCountDirUp;
    stcTimeraInit.enSyncStartupEn = Disable;
    stcTimeraInit.u16PeriodVal = period;

    TIMERA_BaseInit(tim_base, &stcTimeraInit);
    TIMERA_IrqCmd(  tim_base, TimeraIrqOverflow, Disable);

    stcTimerCompareInit.u16CompareVal = 0;
    stcTimerCompareInit.enStartCountOutput = TimeraCountStartOutputKeep;
    stcTimerCompareInit.enStopCountOutput = TimeraCountStopOutputLow;

    stcTimerCompareInit.enCompareMatchOutput = TimeraCompareMatchOutputLow;
    stcTimerCompareInit.enPeriodMatchOutput = TimeraPeriodMatchOutputHigh;
    stcTimerCompareInit.enSpecifyOutput = TimeraSpecifyOutputLow;

    stcTimerCompareInit.enCacheEn = Disable;
    stcTimerCompareInit.enTriangularTroughTransEn = Disable;
    stcTimerCompareInit.enTriangularCrestTransEn = Disable;
    stcTimerCompareInit.u16CompareCacheVal = stcTimerCompareInit.u16CompareVal;

    TIMERA_CompareInit(tim_base, tim_ch, &stcTimerCompareInit);
    TIMERA_CompareCmd( tim_base, tim_ch, Enable);

    TIMERA_Cmd(tim_base, Enable);

    TIMERA_SetCompareValue( tim_base, tim_ch, 0);
    TIMERA_SpecifyOutputSta(tim_base, tim_ch, TimeraSpecifyOutputInvalid);
}

// ratio is 0~255
void fan_pwm_set_ratio(uint8_t fan, uint8_t ratio)
{
    M4_TMRA_TypeDef *tim_base;
    en_timera_channel_t tim_ch;

    switch(fan) {
//    case 0:
//        tim_base = BOARD_PWM_CH0_BASE;
//        tim_ch   = BOARD_PWM_CH0_CH;
//        break;

//    case 1:
//        tim_base = BOARD_PWM_CH1_BASE;
//        tim_ch   = BOARD_PWM_CH1_CH;
//        break;

    case 2:
        tim_base = BOARD_PWM_CH2_BASE;
        tim_ch   = BOARD_PWM_CH2_CH;
        break;
    case 3:
        tim_base = BOARD_PWM_CH3_BASE;
        tim_ch   = BOARD_PWM_CH3_CH;
        break;		
		case 4:
        tim_base = BOARD_PWM_CH4_BASE;        
        tim_ch   = BOARD_PWM_CH4_CH;
        break;

    default:
        return;
        break;
    }

    uint16_t cmp = TIMERA_GetCompareValue(tim_base, tim_ch);
    uint16_t ped = TIMERA_GetPeriodValue(tim_base);

    uint16_t compareValue = ped * ratio >> 8;

    TIMERA_SetCompareValue(tim_base,  tim_ch, compareValue);

    if(compareValue == 0) {
        TIMERA_SpecifyOutputSta(tim_base, tim_ch, TimeraSpecifyOutputLow);
    } else if(compareValue == 100) {
        TIMERA_SpecifyOutputSta(tim_base, tim_ch, TimeraSpecifyOutputHigh);
    } else {
        TIMERA_SpecifyOutputSta(tim_base, tim_ch, TimeraSpecifyOutputInvalid);
    }
}


// PB07 TIMA_4_PWM2 
// PCLK1 = 100M
// frequency = PCLK1 / Div8 / period
// period = 100M / Div8 / frequency
void beep_pwm_init(void)
{  
    uint32_t period;

    stc_timera_base_init_t stcTimeraInit;
    stc_timera_compare_init_t stcTimerCompareInit;
    stc_irq_regi_conf_t stcIrqRegiConf;

    /* configuration structure initialization */
    MEM_ZERO_STRUCT(stcTimeraInit);
    MEM_ZERO_STRUCT(stcIrqRegiConf);
    MEM_ZERO_STRUCT(stcTimerCompareInit);

    /* Configuration peripheral clock */
    PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIMA4, Enable);
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_PERIPH_AOS, Enable);

    PORT_SetFunc(BOARD_PWM_BEEP_PORT, BOARD_PWM_BEEP_PIN, BOARD_PWM_BEEP_FUNC, Disable);



// PCLK1 = 400Hz
// frequency = PCLK1 / Div8 / period
// period = 100M / Div8 / 31250 = 400
// period = 84M / Div8 / 26250 = 400
    period = 31250;

    stcTimeraInit.enClkDiv = TimeraPclkDiv8;
    stcTimeraInit.enCntMode = TimeraCountModeSawtoothWave;
    stcTimeraInit.enCntDir = TimeraCountDirUp;
    stcTimeraInit.enSyncStartupEn = Disable;
    stcTimeraInit.u16PeriodVal = period;

    TIMERA_BaseInit(BOARD_PWM_BEEP_BASE, &stcTimeraInit);
    TIMERA_IrqCmd(  BOARD_PWM_BEEP_BASE, TimeraIrqOverflow, Disable);

    stcTimerCompareInit.u16CompareVal = period * 0.1;
    stcTimerCompareInit.enStartCountOutput = TimeraCountStartOutputKeep;
    stcTimerCompareInit.enStopCountOutput = TimeraCountStopOutputLow;

    stcTimerCompareInit.enCompareMatchOutput = TimeraCompareMatchOutputLow;
    stcTimerCompareInit.enPeriodMatchOutput = TimeraPeriodMatchOutputHigh;
    stcTimerCompareInit.enSpecifyOutput = TimeraSpecifyOutputLow;

    stcTimerCompareInit.enCacheEn = Disable;
    stcTimerCompareInit.enTriangularTroughTransEn = Disable;
    stcTimerCompareInit.enTriangularCrestTransEn = Disable;
    stcTimerCompareInit.u16CompareCacheVal = stcTimerCompareInit.u16CompareVal;

    TIMERA_CompareInit(BOARD_PWM_BEEP_BASE, BOARD_PWM_BEEP_CH, &stcTimerCompareInit);
    TIMERA_CompareCmd( BOARD_PWM_BEEP_BASE, BOARD_PWM_BEEP_CH, Enable);

    TIMERA_SetCompareValue( BOARD_PWM_BEEP_BASE,BOARD_PWM_BEEP_CH, period * 0.1);
    TIMERA_SpecifyOutputSta(BOARD_PWM_BEEP_BASE,BOARD_PWM_BEEP_CH,TimeraSpecifyOutputInvalid);

// no beep when init
//    TIMERA_Cmd(BOARD_PWM_CH3_BASE, Enable);

}

// PB07 TIMA_4_PWM2
// PCLK1 = 100M
// frequency = PCLK1 / Div8 / period
// period = 100M / Div8 / frequency
void beep_pwm_set_frequency(uint32_t frequency, uint8_t ratio)
{
    uint16_t periodValue = 0, compareValue = 0;

    //periodValue = (uint32_t)(100000000ul / (1 << M4_TMRA4->BCSTR_f.CKDIV)) / frequency;
		periodValue = (uint32_t)(84000000ul / (1 << M4_TMRA3->BCSTR_f.CKDIV)) / frequency;
    BOARD_PWM_BEEP_BASE->PERAR = periodValue;

    compareValue = (uint32_t)ratio * periodValue / 100;
    TIMERA_SetCompareValue(BOARD_PWM_BEEP_BASE,  BOARD_PWM_BEEP_CH, compareValue);
    TIMERA_SpecifyOutputSta(BOARD_PWM_BEEP_BASE, BOARD_PWM_BEEP_CH, TimeraSpecifyOutputInvalid);

    TIMERA_Cmd(BOARD_PWM_BEEP_BASE, Enable);
}

void beep_pwm_stop(void)
{
    TIMERA_Cmd(BOARD_PWM_BEEP_BASE, Disable);
}


