/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * lcd/extui/lib/dgus_tft.h
 *
 * Extensible_UI implementation for Anycubic Chiron
 * Written By Nick Wells, 2020 [https://github.com/SwiftNick]
 *  (not affiliated with Anycubic, Ltd.)
 */

#include "dgus_tft_defs.h"
#include "../../../../inc/MarlinConfigPre.h"
#include "../../ui_api.h"

#define MAIN_BOARD_FIRMWARE_VER "marlin 2.0.9.2"
using namespace ExtUI;
/****************** PAGE INDEX***********************/
#define PAGE_MAIN          (1+PAGE_OFFSET)
#define PAGE_choose        (2)
#define PAGE_FILE          (2+PAGE_OFFSET)
#define PAGE_resume        (3+PAGE_OFFSET)  // show resume
#define PAGE_pause         (4+PAGE_OFFSET)  // show pause
#define PAGE_ADJUST        (5+PAGE_OFFSET)
#define PAGE_KEYBPARD      (6+PAGE_OFFSET)
#define PAGE_TOOL          (7+PAGE_OFFSET)
#define PAGE_MOVE          (8+PAGE_OFFSET)
#define PAGE_TEMP          (9+PAGE_OFFSET)
#define PAGE_SPEED         (10+PAGE_OFFSET)
#define PAGE_SYSTEM_CHS_AUDIO_ON   (11+PAGE_OFFSET)
#define PAGE_WIFI          (12+PAGE_OFFSET)
#define PAGE_ABOUT         (13+PAGE_OFFSET)
#define PAGE_RECORD        (14+PAGE_OFFSET)
#define PAGE_PREPARE       (15+PAGE_OFFSET)
#define PAGE_PreLEVEL      (16+PAGE_OFFSET)
#define PAGE_LEVEL_ADVANCE (17+PAGE_OFFSET)
#define PAGE_PREHEAT       (18+PAGE_OFFSET)
#define PAGE_FILAMENT      (19+PAGE_OFFSET)

#define PAGE_DONE           (20+PAGE_OFFSET)
#define PAGE_ABNORMAL       (21+PAGE_OFFSET)
#define PAGE_PRINT_FINISH   (22+PAGE_OFFSET)
#define PAGE_WAIT_STOP      (23+PAGE_OFFSET)
#define PAGE_FILAMENT_LACK  (25+PAGE_OFFSET)
#define PAGE_FORBIT         (26+PAGE_OFFSET)
#define PAGE_STOP_CONF      (27+PAGE_OFFSET)
#define PAGE_NO_SD          (29+PAGE_OFFSET)
#define PAGE_FILAMENT_HEAT  (30+PAGE_OFFSET)
#define PAGE_WAIT_PAUSE     (32+PAGE_OFFSET)

#define PAGE_LEVEL_ENSURE   (33+PAGE_OFFSET)
#define PAGE_LEVELING       (34+PAGE_OFFSET)




#define PAGE_AUTO_OFFSET    (115+PAGE_OFFSET)

#define PAGE_SYSTEM_CHS_AUDIO_OFF   (117+PAGE_OFFSET)

#define PAGE_SYSTEM_ENG_AUDIO_ON    (131+PAGE_OFFSET)
#define PAGE_SYSTEM_ENG_AUDIO_OFF   (170+PAGE_OFFSET)

#define PAGE_OUTAGE_RECOVERY        (171+PAGE_OFFSET)
#define PAGE_ENG_OUTAGE_RECOVERY    (173+PAGE_OFFSET)

#define PAGE_CHS_PROBE_PREHEATING   (176+PAGE_OFFSET)
#define PAGE_ENG_PROBE_PREHEATING   (175+PAGE_OFFSET)


#define Default_back_color   0x755e   //Ç³À¶É«
#define Seclect_f_color   0xF800    
#define N_Seclect_f_color 0
#define Line_height          24
#define max_item_buf_num     10
#define max_string_buf       32
namespace Anycubic {

  typedef struct _lcd_info_t {
    ExtUI::language_t       language;
    ExtUI::audio_t          audio;
  } lcd_info_t;
 

  class DgusTFT {
   
      static FileList  filelist;
      static printer_state_t  printer_state;
      static uint32_t         page_index;
      static uint32_t         last_page_index;
      static uint32_t         page_max_item;
      static uint32_t         page_now_item;
      static char item_string[max_item_buf_num][max_string_buf];
   
//    static paused_state_t   pause_state;
//    static heater_state_t   hotend_state;
//    static heater_state_t   hotbed_state;
//    static xy_uint8_t       selectedmeshpoint;
//    static char             panel_command[MAX_CMND_LEN];
//    static uint8_t          command_len;
//    static char             selectedfile[MAX_PATH_LEN];
//    static float            live_Zoffset;
//    static file_menu_t      file_menu;
//    static bool             data_received;
//    static uint8_t          data_buf[64];
//    static uint8_t          data_index;
//    static uint32_t         page_index_last;
//	static uint8_t          message_index;
//    static uint8_t          pop_up_index;
//	static uint32_t         key_index;
//    static uint32_t         key_value;
//    static uint16_t         filenumber;
//    static uint16_t         filepage;
//    static uint8_t          lcd_txtbox_index;
//    static uint8_t          lcd_txtbox_page;
//    static uint16_t         change_color_index;
//    static uint8_t          TFTpausingFlag;
//    static uint8_t          TFTStatusFlag;
//    static uint8_t          TFTresumingflag;
//    static uint8_t          ready;

    public:
      DgusTFT();
      
      static lcd_info_t       lcd_info;
      void Startup();
      void ParamInit();
      void IdleLoop();
//      void PrinterKilled(PGM_P,PGM_P);
      void MediaEvent(media_event_t);
//      void TimerEvent(timer_event_t);
//      void FilamentRunout();
//      void ConfirmationRequest(const char * const );
//      void StatusChange(const char * const );
      void PowerLoss();
      void PowerLossRecovery();

       void show_item(uint32_t num,char seclect);
      typedef void (*p_fun)(void);
      static void PAGE_choose_oper(void);
//      static void page2_handle(void);
//      static void page3_handle(void);
//      static void page4_handle(void);
//      static void page5_handle(void);
//      static void page6_handle(void);
//      static void page7_handle(void);   // tool
//      static void page8_handle(void);
//      static void page9_handle(void);
//      static void page10_handle(void);  // fan and print speed
//      static void page11_handle(void);  // system
//      static void page12_handle(void);
//      static void page13_handle(void);
//      static void page14_handle(void);
//      static void page15_handle(void);
//      static void page16_handle(void);
//      static void page17_handle(void);
//      static void page18_handle(void);
//      static void page19_handle(void);
//      static void page20_handle(void);
//      static void page21_handle(void);
//      static void page22_handle(void);
//      static void page23_handle(void);
//      static void page24_handle(void);
//      static void page25_handle(void);
//      static void page26_handle(void);
//      static void page27_handle(void);
//      static void page28_handle(void);
//      static void page29_handle(void);
//      static void page30_handle(void);
//      static void page31_handle(void);
//      static void page32_handle(void);
//      static void page33_handle(void);
//      static void page34_handle(void);
//      static void page115_handle(void);
//      static void page117_handle(void);     // CHS Mute handler
//      static void page170_handle(void);     // ENG Mute handler
//      static void page171_handle(void);     // CHS power outage resume handler
//      static void page173_handle(void);     // ENG power outage resume handler
//      static void page175_handle(void);     // CHS probe preheating handler
//      static void page176_handle(void);     // ENG probe preheating handler
//      static void pop_up_manager(void);

//      void SendtoTFT(PGM_P);
//      void SendtoTFTLN(PGM_P);
//      bool ReadTFTCommand();
//      int8_t Findcmndpos(const char *, char);
//      void CheckHeaters();
//      static void SendFileList(int8_t);
//      void SelectFile();
//      void InjectCommandandWait(PGM_P);
//      void ProcessPanelRequest();
//      void PanelInfo(uint8_t);
//      void PanelAction(uint8_t);
//      void PanelProcess(uint8_t);

//      static void SendValueToTFT(uint32_t value, uint32_t address);
//      static void RequestValueFromTFT(uint32_t address);
//      static void SendTxtToTFT(const char *pdata, uint32_t address);
//      static void SendColorToTFT(uint32_t color, uint32_t address);
//      static void SendReadNumOfTxtToTFT(uint8_t number, uint32_t address);
//      static void ChangePageOfTFT(uint32_t page_index);
//      static void LcdAudioSet(ExtUI::audio_t audio);

    private:
    
  };

  extern DgusTFT Dgus;

}
