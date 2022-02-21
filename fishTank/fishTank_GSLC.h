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
#include "elem/XKeyPad_Num.h"
#include "elem/XRingGauge.h"
#include "elem/XTogglebtn.h"

// Ensure optional features are enabled in the configuration
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
enum {E_PG_BASE,E_PG_MAIN,E_PG_POPUP_NOTIFY,E_PG_SUM,E_PG_STNG
      ,E_PG_CALPH,E_POP_KEYPAD_NUM};
enum {E_DRAW_LINE_STNG1,E_DRAW_LINE_STNG2,E_ELEM_BOX2,E_ELEM_BOX3
      ,E_ELEM_BTN2,E_ELEM_BTN7,E_ELEM_BTN_CALPH_CLR,E_ELEM_BTN_CALPH_HI
      ,E_ELEM_BTN_CALPH_LO,E_ELEM_BTN_CALPH_MD,E_ELEM_BTN_HOME1
      ,E_ELEM_BTN_HOME2,E_ELEM_BTN_HOME3,E_ELEM_BTN_PHSUM
      ,E_ELEM_BTN_STNGS,E_ELEM_BTN_STNG_CALPH,E_ELEM_BTN_TDSSUM
      ,E_ELEM_BTN_TEMPSUM,E_ELEM_CHECK_NOHEATER,E_ELEM_CLOCK_TXT
      ,E_ELEM_NUMINPUT_TEMP,E_ELEM_PHGAUGE,E_ELEM_PHUNIT_TEXT
      ,E_ELEM_TDSGAUGE,E_ELEM_TDSUNIT_TEXT,E_ELEM_TEAMNAME_TXT
      ,E_ELEM_TEMPGAUGE,E_ELEM_TEMPUNIT_TEXT,E_ELEM_TEXT11
      ,E_ELEM_TEXT14,E_ELEM_TEXT26,E_ELEM_TEXT27,E_ELEM_TEXT28
      ,E_ELEM_TEXT29,E_ELEM_TEXT3,E_ELEM_TEXT30,E_ELEM_TEXT32
      ,E_ELEM_TEXT33,E_ELEM_TEXT34,E_ELEM_TEXT35,E_ELEM_TEXT36
      ,E_ELEM_TEXT38,E_ELEM_TEXT39,E_ELEM_TEXT40,E_ELEM_TEXT41
      ,E_ELEM_TEXT42,E_ELEM_TEXT_ALERT_MSG,E_ELEM_TEXT_STNG_DESTEMP
      ,E_ELEM_TITLE_TXT,E_ELEM_TOGGLE2,E_ELEM_KEYPAD_NUM};
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
#define MAX_PAGE                7

#define MAX_ELEM_PG_BASE 3 // # Elems total on page
#define MAX_ELEM_PG_BASE_RAM MAX_ELEM_PG_BASE // # Elems in RAM
// Define the maximum number of elements per page
// - To enable the same code to run on devices that support storing
//   data into Flash (PROGMEM) and those that don't, we can make the
//   number of elements in Flash dependent upon GSLC_USE_PROGMEM
// - This should allow both Arduino and ARM Cortex to use the same code.

#define MAX_ELEM_PG_MAIN 15 // # Elems total on page
#if (GSLC_USE_PROGMEM)
  #define MAX_ELEM_PG_MAIN_PROG 3 // # Elems in Flash
#else
  #define MAX_ELEM_PG_MAIN_PROG 0 // No Elems in Flash
#endif
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN - MAX_ELEM_PG_MAIN_PROG 

#define MAX_ELEM_PG_POPUP_NOTIFY 5 // # Elems total on page
#define MAX_ELEM_PG_POPUP_NOTIFY_RAM MAX_ELEM_PG_POPUP_NOTIFY // # Elems in RAM

#define MAX_ELEM_PG_SUM 5 // # Elems total on page
#define MAX_ELEM_PG_SUM_RAM MAX_ELEM_PG_SUM // # Elems in RAM

#define MAX_ELEM_PG_STNG 13 // # Elems total on page
#define MAX_ELEM_PG_STNG_RAM MAX_ELEM_PG_STNG // # Elems in RAM

#define MAX_ELEM_PG_CALPH 9 // # Elems total on page
#define MAX_ELEM_PG_CALPH_RAM MAX_ELEM_PG_CALPH // # Elems in RAM
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
gslc_tsElem                     m_asPopup2Elem[MAX_ELEM_PG_POPUP_NOTIFY_RAM];
gslc_tsElemRef                  m_asPopup2ElemRef[MAX_ELEM_PG_POPUP_NOTIFY];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_SUM_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_SUM];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_STNG_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_STNG];
gslc_tsElem                     m_asPage4Elem[MAX_ELEM_PG_CALPH_RAM];
gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_PG_CALPH];
gslc_tsElem                     m_asKeypadNumElem[1];
gslc_tsElemRef                  m_asKeypadNumElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadNum;
gslc_tsXRingGauge               m_sXRingGauge1;
gslc_tsXRingGauge               m_sXRingGauge2;
gslc_tsXRingGauge               m_sXRingGauge3;
gslc_tsXTogglebtn               m_asXToggle2;
gslc_tsXCheckbox                m_asXCheck2;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* alertMsgTxt;
extern gslc_tsElemRef* btnSettings;
extern gslc_tsElemRef* btnSettings25_26;
extern gslc_tsElemRef* btnSummary;
extern gslc_tsElemRef* calpHStatTxt;
extern gslc_tsElemRef* clockTxt;
extern gslc_tsElemRef* desiredTempElem;
extern gslc_tsElemRef* heaterStatTxt;
extern gslc_tsElemRef* noHeaterCB;
extern gslc_tsElemRef* phGauge;
extern gslc_tsElemRef* phLoHiTxt;
extern gslc_tsElemRef* phSumBtn;
extern gslc_tsElemRef* phUnitTxt;
extern gslc_tsElemRef* settingsTempUnitTxt;
extern gslc_tsElemRef* statusbarText;
extern gslc_tsElemRef* tdsGauge;
extern gslc_tsElemRef* tdsLoHiTxt;
extern gslc_tsElemRef* tdsSumBtn;
extern gslc_tsElemRef* tdsUnitTxt;
extern gslc_tsElemRef* tempGauge;
extern gslc_tsElemRef* tempLoHiTxt;
extern gslc_tsElemRef* tempSumBtn;
extern gslc_tsElemRef* tempUnitToggle;
extern gslc_tsElemRef* tempUnitTxt;
extern gslc_tsElemRef* m_pElemKeyPadNum;
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
  gslc_PageAdd(&m_gui,E_PG_POPUP_NOTIFY,m_asPopup2Elem,MAX_ELEM_PG_POPUP_NOTIFY_RAM,m_asPopup2ElemRef,MAX_ELEM_PG_POPUP_NOTIFY);
  gslc_PageAdd(&m_gui,E_PG_SUM,m_asPage2Elem,MAX_ELEM_PG_SUM_RAM,m_asPage2ElemRef,MAX_ELEM_PG_SUM);
  gslc_PageAdd(&m_gui,E_PG_STNG,m_asPage3Elem,MAX_ELEM_PG_STNG_RAM,m_asPage3ElemRef,MAX_ELEM_PG_STNG);
  gslc_PageAdd(&m_gui,E_PG_CALPH,m_asPage4Elem,MAX_ELEM_PG_CALPH_RAM,m_asPage4ElemRef,MAX_ELEM_PG_CALPH);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_NUM,m_asKeypadNumElem,1,m_asKeypadNumElemRef,1);  // KeyPad

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
  static char m_sDisplayText18[31] = "Clock";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_CLOCK_TXT,E_PG_BASE,(gslc_tsRect){149,10,181,10},
    (char*)m_sDisplayText18,31,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  clockTxt = pElemRef;
  
  // Create E_ELEM_TITLE_TXT runtime modifiable text
  static char m_sDisplayText19[21] = "Home";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TITLE_TXT,E_PG_BASE,(gslc_tsRect){10,10,121,10},
    (char*)m_sDisplayText19,21,E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  statusbarText = pElemRef;
  
  // Create E_ELEM_TEAMNAME_TXT text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEAMNAME_TXT,E_PG_BASE,(gslc_tsRect){385,10,85,10},
    (char*)"Fish Tank v0.4",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  

  // Create ring gauge E_ELEM_TEMPGAUGE 
  static char m_sRingText1[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_TEMPGAUGE,E_PG_MAIN,&m_sXRingGauge1,
          (gslc_tsRect){165,70,150,150},
          (char*)m_sRingText1,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 80); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 20);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, -135, 270, true);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE_LT4, GSLC_COL_RED_LT4);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){20,20,20}));
  tempGauge = pElemRef;
  
  // Create E_ELEM_TEMPUNIT_TEXT modifiable text using flash API
  static char m_sDisplayText2[6] = "F";
  gslc_ElemCreateTxt_P_R_ext(&m_gui,E_ELEM_TEMPUNIT_TEXT,E_PG_MAIN,224,169,31,10,
    m_sDisplayText2,6,&m_asFont[E_BUILTIN5X8],
    GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_ALIGN_MID_MID,0,0,
    false,true,false,false,NULL,NULL,NULL,NULL);
  tempUnitTxt = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TEMPUNIT_TEXT);
  
  // Create E_ELEM_TEXT3 runtime modifiable text
  static char m_sDisplayText3[16] = "lo/hi";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT3,E_PG_MAIN,(gslc_tsRect){194,114,91,10},
    (char*)m_sDisplayText3,16,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4);
  tempLoHiTxt = pElemRef;
  
  // create E_ELEM_BTN2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN2,E_PG_MAIN,
    (gslc_tsRect){10,250,225,60},(char*)"Summary",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,10);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  btnSummary = pElemRef;
  
  // create E_ELEM_BTN_STNGS button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_STNGS,E_PG_MAIN,
    (gslc_tsRect){245,250,225,60},(char*)"Options",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,10);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  btnSettings = pElemRef;

  // Create ring gauge E_ELEM_PHGAUGE 
  static char m_sRingText2[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_PHGAUGE,E_PG_MAIN,&m_sXRingGauge2,
          (gslc_tsRect){323,70,150,150},
          (char*)m_sRingText2,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 80); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 20);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, -135, 270, true);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE_LT4, GSLC_COL_RED_LT4);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){20,20,20}));
  phGauge = pElemRef;
  
  // Create E_ELEM_PHUNIT_TEXT modifiable text using flash API
  static char m_sDisplayText10[6] = "pH";
  gslc_ElemCreateTxt_P_R_ext(&m_gui,E_ELEM_PHUNIT_TEXT,E_PG_MAIN,382,169,31,10,
    m_sDisplayText10,6,&m_asFont[E_BUILTIN5X8],
    GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_ALIGN_MID_MID,0,0,
    false,true,false,false,NULL,NULL,NULL,NULL);
  phUnitTxt = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_PHUNIT_TEXT);
  
  // Create E_ELEM_TEXT11 runtime modifiable text
  static char m_sDisplayText11[16] = "lo/hi";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT11,E_PG_MAIN,(gslc_tsRect){352,114,91,10},
    (char*)m_sDisplayText11,16,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4);
  phLoHiTxt = pElemRef;

  // Create ring gauge E_ELEM_TDSGAUGE 
  static char m_sRingText3[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_TDSGAUGE,E_PG_MAIN,&m_sXRingGauge3,
          (gslc_tsRect){7,70,150,150},
          (char*)m_sRingText3,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 80); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 20);
  gslc_ElemXRingGaugeSetAngleRange(&m_gui,pElemRef, -135, 270, true);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE_LT4, GSLC_COL_RED_LT4);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, ((gslc_tsColor){20,20,20}));
  tdsGauge = pElemRef;
  
  // Create E_ELEM_TDSUNIT_TEXT modifiable text using flash API
  static char m_sDisplayText13[6] = "ppm";
  gslc_ElemCreateTxt_P_R_ext(&m_gui,E_ELEM_TDSUNIT_TEXT,E_PG_MAIN,66,169,31,10,
    m_sDisplayText13,6,&m_asFont[E_BUILTIN5X8],
    GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_ALIGN_MID_MID,0,0,
    false,true,false,false,NULL,NULL,NULL,NULL);
  tdsUnitTxt = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TDSUNIT_TEXT);
  
  // Create E_ELEM_TEXT14 runtime modifiable text
  static char m_sDisplayText14[16] = "lo/hi";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT14,E_PG_MAIN,(gslc_tsRect){36,114,91,10},
    (char*)m_sDisplayText14,16,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4);
  tdsLoHiTxt = pElemRef;
  
  // Create E_ELEM_TEXT33 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT33,E_PG_MAIN,(gslc_tsRect){206,45,67,10},
    (char*)"Temperature",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT34 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT34,E_PG_MAIN,(gslc_tsRect){72,45,19,10},
    (char*)"TDS",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT36 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT36,E_PG_MAIN,(gslc_tsRect){391,45,13,10},
    (char*)"pH",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT41 runtime modifiable text
  static char m_sDisplayText41[51] = "Heater is currently off";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT41,E_PG_MAIN,(gslc_tsRect){89,210,301,10},
    (char*)m_sDisplayText41,51,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT1);
  heaterStatTxt = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_POPUP_NOTIFY
  
   
  // Create E_ELEM_BOX2 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX2,E_PG_POPUP_NOTIFY,(gslc_tsRect){10,230,460,80});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  // Set the callback function to update content automatically
  gslc_ElemSetTickFunc(&m_gui,pElemRef,&CbTickScanner);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_LT4,GSLC_COL_RED_LT2,GSLC_COL_RED_LT4);
   
  // Create E_ELEM_BOX3 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX3,E_PG_POPUP_NOTIFY,(gslc_tsRect){20,205,150,40});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  // Set the callback function to update content automatically
  gslc_ElemSetTickFunc(&m_gui,pElemRef,&CbTickScanner);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_LT4,GSLC_COL_RED_LT2,GSLC_COL_RED_LT4);
  
  // Create E_ELEM_TEXT_ALERT_MSG runtime modifiable text
  static char m_sDisplayText17[31] = "Temperature is critically low";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_ALERT_MSG,E_PG_POPUP_NOTIFY,(gslc_tsRect){30,260,361,18},
    (char*)m_sDisplayText17,31,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_RED_LT2,GSLC_COL_BLACK);
  alertMsgTxt = pElemRef;
  
  // create E_ELEM_BTN7 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN7,E_PG_POPUP_NOTIFY,
    (gslc_tsRect){415,235,50,70},(char*)"x",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_LT4,GSLC_COL_RED_LT2,GSLC_COL_RED_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_ELEM_TEXT42 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT42,E_PG_POPUP_NOTIFY,(gslc_tsRect){40,215,109,18},
    (char*)"\x01 Warning",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_RED_LT2,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_SUM
  
  
  // create E_ELEM_BTN_HOME1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_HOME1,E_PG_SUM,
    (gslc_tsRect){358,250,110,60},(char*)"Home",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED_LT4,GSLC_COL_RED_LT4,GSLC_COL_RED_LT2);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN_TEMPSUM button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_TEMPSUM,E_PG_SUM,
    (gslc_tsRect){13,250,110,60},(char*)"Temp",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  tempSumBtn = pElemRef;
  
  // create E_ELEM_BTN_TDSSUM button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_TDSSUM,E_PG_SUM,
    (gslc_tsRect){128,250,110,60},(char*)"TDS",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  tdsSumBtn = pElemRef;
  
  // create E_ELEM_BTN_PHSUM button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PHSUM,E_PG_SUM,
    (gslc_tsRect){243,250,110,60},(char*)"pH",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  phSumBtn = pElemRef;
  
  // Create E_ELEM_TEXT32 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT32,E_PG_SUM,(gslc_tsRect){152,130,175,10},
    (char*)"Drawing graph, please wait...",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY);

  // -----------------------------------
  // PAGE: E_PG_STNG
  
  
  // Create E_ELEM_TEXT26 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT26,E_PG_STNG,(gslc_tsRect){20,50,277,18},
    (char*)"Set Desired Temperature",0,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create toggle button E_ELEM_TOGGLE2
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,E_ELEM_TOGGLE2,E_PG_STNG,&m_asXToggle2,
    (gslc_tsRect){364,185,50,30},GSLC_COL_WHITE,GSLC_COL_BLUE_LT4,GSLC_COL_GRAY_DK3,
    true,true,&CbBtnCommon);
  tempUnitToggle = pElemRef;
  
  // create E_ELEM_BTN_HOME2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_HOME2,E_PG_STNG,
    (gslc_tsRect){10,250,225,60},(char*)"Home",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,10);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
   
  // create checkbox E_ELEM_CHECK_NOHEATER
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK_NOHEATER,E_PG_STNG,&m_asXCheck2,
    (gslc_tsRect){370,110,40,40},false,GSLCX_CHECKBOX_STYLE_BOX,GSLC_COL_BLUE_LT4,false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK1,GSLC_COL_BLACK,GSLC_COL_BLACK);
  noHeaterCB = pElemRef;
  
  // Create E_ELEM_TEXT27 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT27,E_PG_STNG,(gslc_tsRect){20,120,253,18},
    (char*)"Override Heater (OFF)",0,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  // Create E_DRAW_LINE_STNG1 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE_STNG1,E_PG_STNG,15,90,465,90);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK2);

  // Create E_DRAW_LINE_STNG2 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE_STNG2,E_PG_STNG,15,170,465,170);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK2);
  
  // Create E_ELEM_NUMINPUT_TEMP numeric input field
  static char m_sInputNumber1[3] = "75";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT_TEMP,E_PG_STNG,(gslc_tsRect){365,40,50,40},
    (char*)m_sInputNumber1,3,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK1,GSLC_COL_BLACK,GSLC_COL_BLACK);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  desiredTempElem = pElemRef;
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT28 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT28,E_PG_STNG,(gslc_tsRect){20,190,241,18},
    (char*)"Set Temperature Unit",0,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT29 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT29,E_PG_STNG,(gslc_tsRect){423,190,37,18},
    (char*)"\xf7\F",0,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT30 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT30,E_PG_STNG,(gslc_tsRect){317,190,37,18},
    (char*)"\xf7\C",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT_STNG_DESTEMP runtime modifiable text
  static char m_sDisplayText31[4] = "\xf7F";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_STNG_DESTEMP,E_PG_STNG,(gslc_tsRect){425,50,37,18},
    (char*)m_sDisplayText31,4,E_BUILTIN10X16);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  settingsTempUnitTxt = pElemRef;
  
  // create E_ELEM_BTN_STNG_CALPH button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_STNG_CALPH,E_PG_STNG,
    (gslc_tsRect){245,250,225,60},(char*)"Calibrate pH",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,10);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  btnSettings25_26 = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_CALPH
  
  
  // create E_ELEM_BTN_CALPH_LO button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_CALPH_LO,E_PG_CALPH,
    (gslc_tsRect){10,185,150,60},(char*)"4.00",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN_CALPH_MD button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_CALPH_MD,E_PG_CALPH,
    (gslc_tsRect){165,185,150,60},(char*)"7.00",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN_CALPH_HI button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_CALPH_HI,E_PG_CALPH,
    (gslc_tsRect){320,185,150,60},(char*)"10.00",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT35 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT35,E_PG_CALPH,(gslc_tsRect){167,40,145,10},
    (char*)"Calibration Instructions",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // create E_ELEM_BTN_HOME3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_HOME3,E_PG_CALPH,
    (gslc_tsRect){10,250,305,60},(char*)"Home",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,10);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN_CALPH_CLR button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_CALPH_CLR,E_PG_CALPH,
    (gslc_tsRect){320,250,150,60},(char*)"Clear",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,10);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3,GSLC_COL_RED_LT4,GSLC_COL_BLUE_LT3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT38 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT38,E_PG_CALPH,(gslc_tsRect){20,80,349,10},
    (char*)"1. Ensure sensor is in the desired calibration pH solution",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT39 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT39,E_PG_CALPH,(gslc_tsRect){20,110,397,10},
    (char*)"2. Select the corresponding pH level or clear previous calibration",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT40 runtime modifiable text
  static char m_sDisplayText40[51] = " ";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT40,E_PG_CALPH,(gslc_tsRect){89,150,301,10},
    (char*)m_sDisplayText40,51,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN_LT4);
  calpHStatTxt = pElemRef;

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM
  
  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, true);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, true);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
    &m_sKeyPadNum, 65, 80, E_BUILTIN5X8, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
