//<File !Start!>
// FILE: [fishTank_GSLC.h]
// Created by GUIslice Builder version: [0.17.b02]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XCheckbox.h"
#include "elem/XProgress.h"
#include "elem/XRingGauge.h"
#include "elem/XTogglebtn.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if defined(DRV_DISP_TFT_ESPI)
  #error Project tab->Target Platform should be tft_espi
#endif
#include <Adafruit_GFX.h>
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_BASE,E_PG_MAIN,E_PG_POPUP1,E_PG_POPUP2,E_PG2};
enum {E_DRAW_LINE2,E_DRAW_LINE3,E_ELEM_BOX1,E_ELEM_BOX2,E_ELEM_BTN11
      ,E_ELEM_BTN2,E_ELEM_BTN3,E_ELEM_BTN4,E_ELEM_BTN6,E_ELEM_BTN7
      ,E_ELEM_BTN8,E_ELEM_BTN9,E_ELEM_CHECK1,E_ELEM_CLOCK_TXT
      ,E_ELEM_HEATER_TXT,E_ELEM_NEXT_TXT,E_ELEM_PROGRESS1
      ,E_ELEM_PROGRESS2,E_ELEM_PROGRESS3,E_ELEM_PROGRESS4
      ,E_ELEM_PROGRESS5,E_ELEM_PROGRESS6,E_ELEM_PROGRESS7
      ,E_ELEM_RINGGAUGE1,E_ELEM_RINGGAUGE2,E_ELEM_RINGGAUGE3
      ,E_ELEM_TEAMNAME_TXT,E_ELEM_TEXT10,E_ELEM_TEXT11,E_ELEM_TEXT13
      ,E_ELEM_TEXT14,E_ELEM_TEXT15,E_ELEM_TEXT16,E_ELEM_TEXT17
      ,E_ELEM_TEXT2,E_ELEM_TEXT23,E_ELEM_TEXT3,E_ELEM_TITLE_TXT
      ,E_ELEM_TOGGLE1};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN15X24,E_BUILTIN5X8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                5

#define MAX_ELEM_PG_BASE 5 // # Elems total on page
#define MAX_ELEM_PG_BASE_RAM MAX_ELEM_PG_BASE // # Elems in RAM
// Define the maximum number of elements per page
// - To enable the same code to run on devices that support storing
//   data into Flash (PROGMEM) and those that don't, we can make the
//   number of elements in Flash dependent upon GSLC_USE_PROGMEM
// - This should allow both Arduino and ARM Cortex to use the same code.

#define MAX_ELEM_PG_MAIN 12 // # Elems total on page
#if (GSLC_USE_PROGMEM)
  #define MAX_ELEM_PG_MAIN_PROG 3 // # Elems in Flash
#else
  #define MAX_ELEM_PG_MAIN_PROG 0 // No Elems in Flash
#endif
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN - MAX_ELEM_PG_MAIN_PROG 

#define MAX_ELEM_PG_POPUP1 11 // # Elems total on page
#define MAX_ELEM_PG_POPUP1_RAM MAX_ELEM_PG_POPUP1 // # Elems in RAM

#define MAX_ELEM_PG_POPUP2 3 // # Elems total on page
#define MAX_ELEM_PG_POPUP2_RAM MAX_ELEM_PG_POPUP2 // # Elems in RAM

#define MAX_ELEM_PG2 8 // # Elems total on page
#define MAX_ELEM_PG2_RAM MAX_ELEM_PG2 // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asBasePage1Elem[MAX_ELEM_PG_BASE_RAM];
gslc_tsElemRef                  m_asBasePage1ElemRef[MAX_ELEM_PG_BASE];
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_PG_POPUP1_RAM];
gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_PG_POPUP1];
gslc_tsElem                     m_asPopup2Elem[MAX_ELEM_PG_POPUP2_RAM];
gslc_tsElemRef                  m_asPopup2ElemRef[MAX_ELEM_PG_POPUP2];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG2_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG2];
gslc_tsXRingGauge               m_sXRingGauge1;
gslc_tsXRingGauge               m_sXRingGauge2;
gslc_tsXRingGauge               m_sXRingGauge3;
gslc_tsXTogglebtn               m_asXToggle1;
gslc_tsXCheckbox                m_asXCheck1;
gslc_tsXProgress                m_sXBarGauge1;
gslc_tsXProgress                m_sXBarGauge2;
gslc_tsXProgress                m_sXBarGauge3;
gslc_tsXProgress                m_sXBarGauge4;
gslc_tsXProgress                m_sXBarGauge5;
gslc_tsXProgress                m_sXBarGauge6;
gslc_tsXProgress                m_sXBarGauge7;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* btnOther;
extern gslc_tsElemRef* btnSettings;
extern gslc_tsElemRef* btnStngNext;
extern gslc_tsElemRef* btnStngPrev;
extern gslc_tsElemRef* btnSummary;
extern gslc_tsElemRef* clockTxt;
extern gslc_tsElemRef* heaterTxt;
extern gslc_tsElemRef* m_pElemProgress1;
extern gslc_tsElemRef* m_pElemProgress1_2;
extern gslc_tsElemRef* m_pElemProgress1_3;
extern gslc_tsElemRef* m_pElemProgress1_4;
extern gslc_tsElemRef* m_pElemProgress1_5;
extern gslc_tsElemRef* m_pElemProgress1_6;
extern gslc_tsElemRef* m_pElemProgress1_7;
extern gslc_tsElemRef* nxtTxt;
extern gslc_tsElemRef* phGauge;
extern gslc_tsElemRef* phLoHiTxt;
extern gslc_tsElemRef* phUnitTxt;
extern gslc_tsElemRef* tdsGauge;
extern gslc_tsElemRef* tdsLoHiTxt;
extern gslc_tsElemRef* tdsUnitTxt;
extern gslc_tsElemRef* tempGauge;
extern gslc_tsElemRef* tempLoHiTxt;
extern gslc_tsElemRef* tempUnitCB;
extern gslc_tsElemRef* tempUnitToggle;
extern gslc_tsElemRef* tempUnitTxt;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN15X24,GSLC_FONTREF_PTR,NULL,3)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_BASE,m_asBasePage1Elem,MAX_ELEM_PG_BASE_RAM,m_asBasePage1ElemRef,MAX_ELEM_PG_BASE);
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_POPUP1,m_asPopup1Elem,MAX_ELEM_PG_POPUP1_RAM,m_asPopup1ElemRef,MAX_ELEM_PG_POPUP1);
  gslc_PageAdd(&m_gui,E_PG_POPUP2,m_asPopup2Elem,MAX_ELEM_PG_POPUP2_RAM,m_asPopup2ElemRef,MAX_ELEM_PG_POPUP2);
  gslc_PageAdd(&m_gui,E_PG2,m_asPage2Elem,MAX_ELEM_PG2_RAM,m_asPage2ElemRef,MAX_ELEM_PG2);

  // Now mark E_PG_BASE as a "base" page which means that it's elements
  // are always visible. This is useful for common page elements.
  gslc_SetPageBase(&m_gui, E_PG_BASE);


  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_BASE
  
  
  // Create E_ELEM_CLOCK_TXT runtime modifiable text
  static char m_sDisplayText18[41] = "Clock";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_CLOCK_TXT,E_PG_BASE,(gslc_tsRect){119,10,241,10},
    (char*)m_sDisplayText18,41,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  clockTxt = pElemRef;
  
  // Create E_ELEM_TITLE_TXT text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TITLE_TXT,E_PG_BASE,(gslc_tsRect){10,10,85,10},
    (char*)"Fish Tank v0.1",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEAMNAME_TXT text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEAMNAME_TXT,E_PG_BASE,(gslc_tsRect){373,10,97,10},
    (char*)"Electric Ox Corp",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_HEATER_TXT runtime modifiable text
  static char m_sDisplayText21[16] = "Heater: OFF";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_HEATER_TXT,E_PG_BASE,(gslc_tsRect){379,300,91,10},
    (char*)m_sDisplayText21,16,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  heaterTxt = pElemRef;
  
  // Create E_ELEM_NEXT_TXT text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NEXT_TXT,E_PG_BASE,(gslc_tsRect){10,300,139,10},
    (char*)"Next test in 10 minutes",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  nxtTxt = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_MAIN
  

  // Create ring gauge E_ELEM_RINGGAUGE1 
  static char m_sRingText1[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE1,E_PG_MAIN,&m_sXRingGauge1,
          (gslc_tsRect){170,44,140,140},
          (char*)m_sRingText1,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 80); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 15);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, -135, 270, true);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE_LT4, GSLC_COL_RED_LT4);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){20,20,20}));
  tempGauge = pElemRef;
  
  // Create E_ELEM_TEXT2 modifiable text using flash API
  static char m_sDisplayText2[6] = "F";
  gslc_ElemCreateTxt_P_R_ext(&m_gui,E_ELEM_TEXT2,E_PG_MAIN,224,138,31,10,
    m_sDisplayText2,6,&m_asFont[E_BUILTIN5X8],
    GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_ALIGN_MID_MID,0,0,
    false,true,false,false,NULL,NULL,NULL,NULL);
  tempUnitTxt = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TEXT2);
  
  // Create E_ELEM_TEXT3 runtime modifiable text
  static char m_sDisplayText3[16] = "100 / 103";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT3,E_PG_MAIN,(gslc_tsRect){194,83,91,10},
    (char*)m_sDisplayText3,16,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT2);
  tempLoHiTxt = pElemRef;
  
  // Create E_ELEM_BTN2 button with modifiable text label
  static char m_strbtn2[11] = "Summary";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN2,E_PG_MAIN,
    (gslc_tsRect){190,220,100,40},
    (char*)m_strbtn2,11,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,10);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  btnSummary = pElemRef;
  
  // Create E_ELEM_BTN3 button with modifiable text label
  static char m_strbtn3[11] = "Options";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN3,E_PG_MAIN,
    (gslc_tsRect){310,220,100,40},
    (char*)m_strbtn3,11,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,10);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  btnSettings = pElemRef;
  
  // Create E_ELEM_BTN4 button with modifiable text label
  static char m_strbtn4[11] = "Test Now";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN4,E_PG_MAIN,
    (gslc_tsRect){70,220,100,40},
    (char*)m_strbtn4,11,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,10);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  btnOther = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE2 
  static char m_sRingText2[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE2,E_PG_MAIN,&m_sXRingGauge2,
          (gslc_tsRect){320,45,140,140},
          (char*)m_sRingText2,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 80); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 15);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, -135, 270, true);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){20,20,20}));
  phGauge = pElemRef;
  
  // Create E_ELEM_TEXT10 modifiable text using flash API
  static char m_sDisplayText10[6] = "pH";
  gslc_ElemCreateTxt_P_R_ext(&m_gui,E_ELEM_TEXT10,E_PG_MAIN,374,138,31,10,
    m_sDisplayText10,6,&m_asFont[E_BUILTIN5X8],
    GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_ALIGN_MID_MID,0,0,
    false,true,false,false,NULL,NULL,NULL,NULL);
  phUnitTxt = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TEXT10);
  
  // Create E_ELEM_TEXT11 runtime modifiable text
  static char m_sDisplayText11[16] = "100 / 103";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT11,E_PG_MAIN,(gslc_tsRect){344,83,91,10},
    (char*)m_sDisplayText11,16,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT2);
  phLoHiTxt = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE3 
  static char m_sRingText3[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE3,E_PG_MAIN,&m_sXRingGauge3,
          (gslc_tsRect){20,44,140,140},
          (char*)m_sRingText3,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 80); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 15);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, -135, 270, true);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){20,20,15}));
  tdsGauge = pElemRef;
  
  // Create E_ELEM_TEXT13 modifiable text using flash API
  static char m_sDisplayText13[6] = "ppm";
  gslc_ElemCreateTxt_P_R_ext(&m_gui,E_ELEM_TEXT13,E_PG_MAIN,75,138,31,10,
    m_sDisplayText13,6,&m_asFont[E_BUILTIN5X8],
    GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_ALIGN_MID_MID,0,0,
    false,true,false,false,NULL,NULL,NULL,NULL);
  tdsUnitTxt = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TEXT13);
  
  // Create E_ELEM_TEXT14 runtime modifiable text
  static char m_sDisplayText14[16] = "100 / 103";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT14,E_PG_MAIN,(gslc_tsRect){45,83,91,10},
    (char*)m_sDisplayText14,16,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT2);
  tdsLoHiTxt = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_POPUP1
  
   
  // Create E_ELEM_BOX1 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX1,E_PG_POPUP1,(gslc_tsRect){40,21,400,280});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,((gslc_tsColor){5,5,5}),GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT15,E_PG_POPUP1,(gslc_tsRect){155,40,169,18},
    (char*)"Settings (1/?)",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT16 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT16,E_PG_POPUP1,(gslc_tsRect){90,80,199,10},
    (char*)"Use Celsius Instead of Fahrenheit",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create toggle button E_ELEM_TOGGLE1
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,E_ELEM_TOGGLE1,E_PG_POPUP1,&m_asXToggle1,
    (gslc_tsRect){340,75,49,25},GSLC_COL_WHITE,GSLC_COL_BLUE_LT4,GSLC_COL_GRAY_DK3,
    true,false,&CbBtnCommon);
  tempUnitToggle = pElemRef;
  
  // create E_ELEM_BTN6 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN6,E_PG_POPUP1,
    (gslc_tsRect){190,240,100,40},(char*)"Home",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
   
  // create checkbox E_ELEM_CHECK1
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK1,E_PG_POPUP1,&m_asXCheck1,
    (gslc_tsRect){350,123,30,30},false,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_BLUE_LT4,false);
  tempUnitCB = pElemRef;
  
  // Create E_ELEM_TEXT23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT23,E_PG_POPUP1,(gslc_tsRect){90,135,199,10},
    (char*)"Use Celsius Instead of Fahrenheit",0,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  // Create E_DRAW_LINE2 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE2,E_PG_POPUP1,80,110,400,110);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK2);

  // Create E_DRAW_LINE3 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE3,E_PG_POPUP1,80,165,400,165);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK2);
  
  // create E_ELEM_BTN8 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN8,E_PG_POPUP1,
    (gslc_tsRect){310,240,80,40},(char*)">",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  btnStngNext = pElemRef;
  
  // create E_ELEM_BTN9 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN9,E_PG_POPUP1,
    (gslc_tsRect){90,240,80,40},(char*)"<",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  btnStngPrev = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_POPUP2
  
   
  // Create E_ELEM_BOX2 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX2,E_PG_POPUP2,(gslc_tsRect){40,210,400,70});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  // Set the callback function to update content automatically
  gslc_ElemSetTickFunc(&m_gui,pElemRef,&CbTickScanner);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4);
  
  // Create E_ELEM_TEXT17 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT17,E_PG_POPUP2,(gslc_tsRect){173,240,133,10},
    (char*)"Testing In-Progress...",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLUE_LT4,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN7,E_PG_POPUP2,
    (gslc_tsRect){400,230,30,30},(char*)"x",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_PG2
  
  
  // create E_ELEM_BTN11 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN11,E_PG2,
    (gslc_tsRect){190,230,100,40},(char*)"Home",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // Create progress bar E_ELEM_PROGRESS1 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS1,E_PG2,&m_sXBarGauge1,
    (gslc_tsRect){23,50,12,50},0,100,50,GSLC_COL_GREEN,true);
  m_pElemProgress1 = pElemRef;

  // Create progress bar E_ELEM_PROGRESS2 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS2,E_PG2,&m_sXBarGauge2,
    (gslc_tsRect){143,50,12,50},0,100,0,GSLC_COL_GREEN,true);
  m_pElemProgress1_2 = pElemRef;

  // Create progress bar E_ELEM_PROGRESS3 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS3,E_PG2,&m_sXBarGauge3,
    (gslc_tsRect){123,50,12,50},0,100,70,GSLC_COL_GREEN,true);
  m_pElemProgress1_3 = pElemRef;

  // Create progress bar E_ELEM_PROGRESS4 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS4,E_PG2,&m_sXBarGauge4,
    (gslc_tsRect){103,50,12,50},0,100,0,GSLC_COL_GREEN,true);
  m_pElemProgress1_4 = pElemRef;

  // Create progress bar E_ELEM_PROGRESS5 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS5,E_PG2,&m_sXBarGauge5,
    (gslc_tsRect){83,50,12,50},0,100,0,GSLC_COL_GREEN,true);
  m_pElemProgress1_5 = pElemRef;

  // Create progress bar E_ELEM_PROGRESS6 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS6,E_PG2,&m_sXBarGauge6,
    (gslc_tsRect){63,50,12,50},0,100,30,GSLC_COL_GREEN,true);
  m_pElemProgress1_6 = pElemRef;

  // Create progress bar E_ELEM_PROGRESS7 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS7,E_PG2,&m_sXBarGauge7,
    (gslc_tsRect){43,50,12,50},0,100,90,GSLC_COL_GREEN,true);
  m_pElemProgress1_7 = pElemRef;
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
