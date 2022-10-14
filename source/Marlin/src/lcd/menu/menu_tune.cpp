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

//
// Tune Menu
//

#include "../../inc/MarlinConfigPre.h"

#if HAS_LCD_MENU
#include "menu.h"
#include "canvas.h"
#include "probe.h"
#include "menu_item.h"
#include "../../module/motion.h"
#include "../../module/planner.h"
#include "../../module/temperature.h"
#include "../../MarlinCore.h"

#if ENABLED(SINGLENOZZLE_STANDBY_TEMP)
  #include "../../module/tool_change.h"
#endif

#if HAS_LEVELING
  #include "../../feature/bedlevel/bedlevel.h"
#endif

#if ENABLED(BABYSTEPPING)

  #include "../../feature/babystep.h"
  #include "../lcdprint.h"
  #if HAS_MARLINUI_U8GLIB
    #include "../dogm/marlinui_DOGM.h"
  #endif

  void _lcd_babystep(const AxisEnum axis, PGM_P const msg) {
    if (ui.use_click()) return ui.goto_previous_screen_no_defer();
    if (ui.encoderPosition) {
      const int16_t steps = int16_t(ui.encoderPosition) * (
        #if ENABLED(BABYSTEP_XY)
          axis == X_AXIS ? BABYSTEP_SIZE_X :
          axis == Y_AXIS ? BABYSTEP_SIZE_Y :
        #endif
        BABYSTEP_SIZE_Z
      );
      ui.encoderPosition = 0;
      ui.refresh(LCDVIEW_REDRAW_NOW);
      babystep.add_steps(axis, steps);
    }
    if (ui.should_draw()) {
      const float mps = planner.steps_to_mm[axis];
      MenuEditItemBase::draw_edit_screen(msg, BABYSTEP_TO_STR(mps * babystep.accum));
      #if ENABLED(BABYSTEP_DISPLAY_TOTAL)
        const bool in_view = TERN1(HAS_MARLINUI_U8GLIB, PAGE_CONTAINS(LCD_PIXEL_HEIGHT - MENU_FONT_HEIGHT, LCD_PIXEL_HEIGHT - 1));
        if (in_view) {
          TERN_(HAS_MARLINUI_U8GLIB, ui.set_font(FONT_MENU));
          #if ENABLED(TFT_COLOR_UI)
            lcd_moveto(4, 3);
            lcd_put_u8str_P(GET_TEXT(MSG_BABYSTEP_TOTAL));
            lcd_put_wchar(':');
            lcd_moveto(10, 3);
          #else
            lcd_moveto(0, TERN(HAS_MARLINUI_U8GLIB, LCD_PIXEL_HEIGHT - MENU_FONT_DESCENT, LCD_HEIGHT - 1));
            lcd_put_u8str_P(GET_TEXT(MSG_BABYSTEP_TOTAL));
            lcd_put_wchar(':');
          #endif
          lcd_put_u8str(BABYSTEP_TO_STR(mps * babystep.axis_total[BS_TOTAL_IND(axis)]));
        }
      #endif
    }
  }

  inline void _lcd_babystep_go(const screenFunc_t screen) {
    ui.goto_screen(screen);
    ui.defer_status_screen();
    babystep.accum = 0;
  }

  #if ENABLED(BABYSTEP_XY)
    void _lcd_babystep_x() { _lcd_babystep(X_AXIS, GET_TEXT(MSG_BABYSTEP_X)); }
    void _lcd_babystep_y() { _lcd_babystep(Y_AXIS, GET_TEXT(MSG_BABYSTEP_Y)); }
  #endif

  #if DISABLED(BABYSTEP_ZPROBE_OFFSET)
    void _lcd_babystep_z() { _lcd_babystep(Z_AXIS, GET_TEXT(MSG_BABYSTEP_Z)); }
    void lcd_babystep_z()  { _lcd_babystep_go(_lcd_babystep_z); }
  #endif

#endif // BABYSTEPPING

void menu_tune() {
  START_MENU();
  BACK_ITEM(MSG_BACK);

  //
  // Speed:
  //

	EDIT_ITEM_FAST(int3, MSG_SPEED, &feedrate_percentage, 10, 300);
 	//MenuItem_int3::action(MSG_SPEED, &feedrate_percentage, 10, 999);
  // Manual bed leveling, Bed Z:
  //
  #if BOTH(MESH_BED_LEVELING, LCD_BED_LEVELING)
    EDIT_ITEM(float43, MSG_BED_Z, &mbl.z_offset, -1, 1);
  #endif

  //
  // Nozzle:
  // Nozzle [1-4]:
  //
  #if HOTENDS == 1
    EDIT_ITEM_FAST(int3, MSG_NOZZLE, &thermalManager.temp_hotend[0].target, 0, thermalManager.hotend_max_target(0), []{ thermalManager.start_watching_hotend(0); });
  #elif HAS_MULTI_HOTEND
    HOTEND_LOOP()
      EDIT_ITEM_FAST_N(int3, e, MSG_NOZZLE_N, &thermalManager.temp_hotend[e].target, 0, thermalManager.hotend_max_target(e), []{ thermalManager.start_watching_hotend(MenuItemBase::itemIndex); });
  #endif

  #if ENABLED(SINGLENOZZLE_STANDBY_TEMP)
    LOOP_S_L_N(e, 1, EXTRUDERS)
      EDIT_ITEM_FAST_N(int3, e, MSG_NOZZLE_STANDBY, &thermalManager.singlenozzle_temp[e], 0, thermalManager.hotend_max_target(0));
  #endif

  //
  // Bed:
  //
  #if HAS_HEATED_BED
    EDIT_ITEM_FAST(int3, MSG_BED, &thermalManager.temp_bed.target, 0, BED_MAX_TARGET, thermalManager.start_watching_bed);
  #endif

  //
  // Fan Speed:
  //
  #if HAS_FAN

    DEFINE_SINGLENOZZLE_ITEM();

    #if HAS_FAN0
      _FAN_EDIT_ITEMS(0,FIRST_FAN_SPEED);
    #endif
    #if HAS_FAN1
      FAN_EDIT_ITEMS(1);
    #elif SNFAN(1)
      singlenozzle_item(1);
    #endif
    #if HAS_FAN2
      FAN_EDIT_ITEMS(2);
    #elif SNFAN(2)
      singlenozzle_item(2);
    #endif
    #if HAS_FAN3
      FAN_EDIT_ITEMS(3);
    #elif SNFAN(3)
      singlenozzle_item(3);
    #endif
    #if HAS_FAN4
      FAN_EDIT_ITEMS(4);
    #elif SNFAN(4)
      singlenozzle_item(4);
    #endif
    #if HAS_FAN5
      FAN_EDIT_ITEMS(5);
    #elif SNFAN(5)
      singlenozzle_item(5);
    #endif
    #if HAS_FAN6
      FAN_EDIT_ITEMS(6);
    #elif SNFAN(6)
      singlenozzle_item(6);
    #endif
    #if HAS_FAN7
      FAN_EDIT_ITEMS(7);
    #elif SNFAN(7)
      singlenozzle_item(7);
    #endif

  #endif // HAS_FAN

  //
  // Flow:
  //
  #if HAS_EXTRUDERS
    EDIT_ITEM(int3, MSG_FLOW, &planner.flow_percentage[active_extruder], 10, 300, []{ planner.refresh_e_factor(active_extruder); });
    // Flow En:
    #if HAS_MULTI_EXTRUDER
      LOOP_L_N(n, EXTRUDERS)
        EDIT_ITEM_N(int3, n, MSG_FLOW_N, &planner.flow_percentage[n], 10, 300, []{ planner.refresh_e_factor(MenuItemBase::itemIndex); });
    #endif
  #endif

  //
  // Advance K:
  //
  #if ENABLED(LIN_ADVANCE) && DISABLED(SLIM_LCD_MENUS)
    #if EXTRUDERS == 1
      EDIT_ITEM(float42_52, MSG_ADVANCE_K, &planner.extruder_advance_K[0], 0, 10);
    #elif HAS_MULTI_EXTRUDER
      LOOP_L_N(n, EXTRUDERS)
        EDIT_ITEM_N(float42_52, n, MSG_ADVANCE_K_E, &planner.extruder_advance_K[n], 0, 10);
    #endif
  #endif

  //
  // Babystep X:
  // Babystep Y:
  // Babystep Z:
  //
  #if ENABLED(BABYSTEPPING)
    #if ENABLED(BABYSTEP_XY)
      SUBMENU(MSG_BABYSTEP_X, []{ _lcd_babystep_go(_lcd_babystep_x); });
      SUBMENU(MSG_BABYSTEP_Y, []{ _lcd_babystep_go(_lcd_babystep_y); });
    #endif
    #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
      SUBMENU(MSG_ZPROBE_ZOFFSET, lcd_babystep_zoffset);
   //    EDIT_ITEM(float42_52, MSG_ZPROBE_ZOFFSET, &probe.offset.z, -5.00, 5.00, []{ lcd_babystep_zoffset(); });
    #else
      SUBMENU(MSG_BABYSTEP_Z, lcd_babystep_z);
    #endif
  #endif

  END_MENU();
}
void Lcd_set_feedrate()
{
   static int16_t  fresh_data;
   static char fresh_flag;
   
    if (ui.use_click())   {
        ui.AC_bar_control=false;
        ui.enable_encoder_multiplier(false);
        feedrate_percentage=fresh_data;
        fresh_flag=0;
    return  ui.goto_previous_screen_no_defer();
  }
      ui.defer_status_screen();
       if(fresh_flag==0)
       {
         ui.AC_bar_control=true;
         ui.enable_encoder_multiplier(true);
         fresh_flag=1;
         fresh_data= feedrate_percentage;

       }

    if (ui.encoderPosition) {
      fresh_data +=ui.encoderPosition;
       ui.encoderPosition = 0;
       LIMIT(fresh_data, 10, 300);
       feedrate_percentage=fresh_data;   //打印速度不同于温度，他可以直接生效，如果注释这一行就不生效，注释掉就是最后确定才生效
       ui.refresh(LCDVIEW_CALL_REDRAW_NEXT); 
    }

    if (ui.should_draw()) {
 
 
         MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_SPEED), pct16tostrpctrj(fresh_data));
        #define SLIDER_LENGTH 224
        #define SLIDER_Y_POSITION 140

        tft.canvas((TFT_WIDTH - SLIDER_LENGTH) / 2, SLIDER_Y_POSITION, SLIDER_LENGTH, 9);
        tft.set_background(COLOR_PROGRESS_BG);
        tft.add_rectangle(0, 0, SLIDER_LENGTH, 9, COLOR_PROGRESS_FRAME);
        tft.add_bar(1, 1, ((SLIDER_LENGTH-2) * fresh_data) /300, 7, COLOR_GREEN);
    } 
}

void Lcd_set_flow()
{
   static int16_t  fresh_data;
   static char fresh_flag;
   
    if (ui.use_click())   {
        ui.AC_bar_control=false;
        ui.enable_encoder_multiplier(false);
        planner.flow_percentage[active_extruder]=fresh_data;
        planner.refresh_e_factor(active_extruder);   //挤出速率确定
        fresh_flag=0;
    return  ui.goto_previous_screen_no_defer();
  }
      ui.defer_status_screen();
       if(fresh_flag==0)
       {
         ui.AC_bar_control=true;
         ui.enable_encoder_multiplier(true);
         fresh_flag=1;
         fresh_data=planner.flow_percentage[active_extruder];

       }

    if (ui.encoderPosition) {
      fresh_data +=ui.encoderPosition;
       ui.encoderPosition = 0;
       LIMIT(fresh_data, 10, 300);
       ui.refresh(LCDVIEW_CALL_REDRAW_NEXT); 
    }

    if (ui.should_draw()) {
 
         MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_FLOW), pct16tostrpctrj(fresh_data));
        #define SLIDER_LENGTH 224
        #define SLIDER_Y_POSITION 140

        tft.canvas((TFT_WIDTH - SLIDER_LENGTH) / 2, SLIDER_Y_POSITION, SLIDER_LENGTH, 9);
        tft.set_background(COLOR_PROGRESS_BG);
        tft.add_rectangle(0, 0, SLIDER_LENGTH, 9, COLOR_PROGRESS_FRAME);
        tft.add_bar(1, 1, ((SLIDER_LENGTH-2) * fresh_data) /300, 7, COLOR_GREEN);
    } 
}
void Lcd_set_Fan0()
{
   static int16_t  fresh_percent;
   static char fresh_flag;
   static uint16_t feed_per;
    if (ui.use_click())   {
        ui.AC_bar_control=false;
        ui.enable_encoder_multiplier(false);
        thermalManager.set_fan_speed(0,fresh_percent*255/100);
        fresh_flag=0;
    return  ui.goto_previous_screen_no_defer();
  }
      ui.defer_status_screen();
       if(fresh_flag==0)
       {
       	 fresh_percent = thermalManager.fanPercent(thermalManager.fan_speed[0]);		  
         ui.AC_bar_control=true;
         ui.enable_encoder_multiplier(true);
         fresh_flag=1;


       }

    if (ui.encoderPosition) {
      fresh_percent +=ui.encoderPosition;
       ui.encoderPosition = 0;
       LIMIT(fresh_percent, 0, 100);
       thermalManager.fan_speed[0]=(255*fresh_percent/100);
       ui.refresh(LCDVIEW_CALL_REDRAW_NEXT); 
    }

    if (ui.should_draw()) {
 
 
         MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_FAN_SPEED), pcttostrpctrj(fresh_percent));
        #define SLIDER_LENGTH 224
        #define SLIDER_Y_POSITION 140

        tft.canvas((TFT_WIDTH - SLIDER_LENGTH) / 2, SLIDER_Y_POSITION, SLIDER_LENGTH, 9);
        tft.set_background(COLOR_PROGRESS_BG);
        tft.add_rectangle(0, 0, SLIDER_LENGTH, 9, COLOR_PROGRESS_FRAME);
        tft.add_bar(1, 1, fresh_percent*(SLIDER_LENGTH-2)/100, 7, COLOR_GREEN);
    } 
}


#endif // HAS_LCD_MENU
