#include "hc32_ddl.h"
#include "bsp_init.h"
#include "bsp_irq.h"
#include "bsp_adc.h"
#include "bsp_pwm.h"
#include "bsp_sdio.h"
#include "bsp_timer.h"
#include "bsp_ots.h"
#include "bsp_spi_tft.h"
//#include "diskio.h"

#include "marlincore.h"
#include "../../Configuration.h"

#define APP_START_ADDRESS 0x8000u
//#define APP_START_ADDRESS 0x0000u

void soft_delay_ms(uint32_t ms)
{
    for(uint32_t i=0; i<ms; i++) {
        for(uint32_t j=0; j<8192; j++) {

#if   defined ( __CC_ARM )
            __nop();
#elif defined ( __GNUC__ )
        	asm("NOP");
#endif

        }
    }
}

void scb_init(void)
{
// bootloader vector startup addr
    SCB->VTOR = ((uint32_t) APP_START_ADDRESS & SCB_VTOR_TBLOFF_Msk);
}

int32_t main(void)
{

    scb_init();

    clock_init();

    uart1_init();
    uart2_init();
    uart4_init();

    bsp_ots_init();

    get_all_clock();

    led_pin_init();

    adc_init();

    endstop_pin_init();

    stepper_pin_init();

    heater_pin_init();
		
    timerA2_bltouch_init();  
    fan_pwm_init();
    beep_pwm_init();

    hal_sdio_init();

 
    timer02A_init();     // 1k Hz, millis()
    timer02B_init();     // soft serial
    timer41_init();      // 1k Hz, used for temperature tick
    timer42_init();      // step motor


    timer01B_init();     // used for beep duration timer
      //

		//SysTick configuration
    SysTick_Init(1000u);

	LCD_Init();
 
     
     
      //test
   setup();
  
    while(1) {
        loop();

    }

    return 0;
}

