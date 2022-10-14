#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__


#include "hc32_ddl.h"


//// PB09 TIMA_4_PWM4
//#define BOARD_PWM_CH0_PORT    PortB
//#define BOARD_PWM_CH0_PIN     Pin09
//#define BOARD_PWM_CH0_FUNC    Func_Tima0
//#define BOARD_PWM_CH0_BASE    (M4_TMRA4)
//#define BOARD_PWM_CH0_CH      (TimeraCh4)
//#define BOARD_PWM_CH0_IDX     (0)


// PA13 TIMA_2_PWM5 TIMA_6_PWM2
//#define BOARD_PWM_CH1_PORT    PortA
//#define BOARD_PWM_CH1_PIN     Pin13
//#define BOARD_PWM_CH1_FUNC    Func_Tima0
//#define BOARD_PWM_CH1_BASE    (M4_TMRA2)
//#define BOARD_PWM_CH1_CH      (TimeraCh5)
//#define BOARD_PWM_CH1_IDX     (1)

// PA14 TIMA_2_PWM6 TIMA_6_PWM3
#define BOARD_PWM_CH2_PORT    PortB                 //fan1
#define BOARD_PWM_CH2_PIN     Pin13
#define BOARD_PWM_CH2_FUNC    Func_Tima0
#define BOARD_PWM_CH2_BASE    (M4_TMRA1)
#define BOARD_PWM_CH2_CH      (TimeraCh5)
#define BOARD_PWM_CH2_IDX     (2)

// PA00 TIMA_2_PWM1 
#define BOARD_PWM_CH3_PORT    PortB                  //fan2
#define BOARD_PWM_CH3_PIN     Pin12
#define BOARD_PWM_CH3_FUNC    Func_Tima0
#define BOARD_PWM_CH3_BASE    (M4_TMRA1)
#define BOARD_PWM_CH3_CH      (TimeraCh8)
#define BOARD_PWM_CH3_IDX     (3)

// PB05 TIMA_3_PWM2
#define BOARD_PWM_CH4_PORT    PortB                  //fan0
#define BOARD_PWM_CH4_PIN     Pin05
#define BOARD_PWM_CH4_FUNC    Func_Tima0
#define BOARD_PWM_CH4_BASE    (M4_TMRA3)
#define BOARD_PWM_CH4_CH      (TimeraCh2)
#define BOARD_PWM_CH4_IDX     (4)



#define BOARD_PWM_BEEP_PORT    PortB
#define BOARD_PWM_BEEP_PIN     Pin07
#define BOARD_PWM_BEEP_FUNC    Func_Tima0
#define BOARD_PWM_BEEP_BASE    (M4_TMRA4)
#define BOARD_PWM_BEEP_CH      (TimeraCh2)

void fan_pwm_init(void);
void hal_fan_pwm_init(uint8_t fan);

void BSP_PWMx_Init(void);

void fan0_pwm_init();
void fan2_pwm_init();

void fan_pwm_set_ratio(uint8_t fan, uint8_t ratio);

void beep_pwm_init(void);

void BSP_BUZ_Init(uint32_t freq);

void BSP_PWM_SetDuty(uint8_t pwm_index,uint8_t duty);

void beep_pwm_set_frequency(uint32_t frequency, uint8_t ratio);
void beep_pwm_stop(void);



#endif

