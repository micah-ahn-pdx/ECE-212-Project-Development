//<App !Start!>
// FILE: [fishTank.ino]
// Created by GUIslice Builder version: [0.17.b02]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// Fish Tank
// - Team Electric Ox [4]
// By: Meshal, Micah, Kenny, Gene

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "fishTank_GSLC.h"
#include <WiFi.h>
#include "time.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// * 
#define TEMP_SENSOR 4			// Temp sensor pin
#define TDS_SENSOR 25			// TDS Sensor pin
#define VREF 3.3          // [TDS] analog reference voltage(Volt) of the ADC
#define SCOUNT 30         // [TDS] sum of sample point
#define FIFTEEN_MINS 15*60*1000L	// 15 minutes
#define LOOP_UPDATE_DELAY 5*1000L // 5 seconds

// * Starting Variables
// loop update variable
unsigned long loopTime = 0L ;
// WiFi Setup
const char* ssid = "01001101";
const char* pwd = "0x01001101";
// Getting Time
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -28800;   //Replace with your GMT offset (seconds)
const int   daylightOffset_sec = 3600;  //Replace with your daylight offset (seconds)
struct tm timeinfo;
// Temp
char tempUnit[3] = "F";
OneWire oneWire(TEMP_SENSOR);
DallasTemperature tempSensor(&oneWire);
// TDS
int analogBuffer[SCOUNT]; 			// store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 0;


// **************** BELOW IS GENERATED AUTOMATICALLY BY THE GUISLICE BUILDER **************** //
// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* btnOther          = NULL;
gslc_tsElemRef* btnSettings       = NULL;
gslc_tsElemRef* btnStngNext13     = NULL;
gslc_tsElemRef* btnStngPrev14     = NULL;
gslc_tsElemRef* btnSummary        = NULL;
gslc_tsElemRef* clockTxt          = NULL;
gslc_tsElemRef* desiredTemp       = NULL;
gslc_tsElemRef* phGauge           = NULL;
gslc_tsElemRef* phLoHiTxt         = NULL;
gslc_tsElemRef* phUnitTxt         = NULL;
gslc_tsElemRef* statusbarText     = NULL;
gslc_tsElemRef* tdsGauge          = NULL;
gslc_tsElemRef* tdsLoHiTxt        = NULL;
gslc_tsElemRef* tdsUnitTxt        = NULL;
gslc_tsElemRef* tempGauge         = NULL;
gslc_tsElemRef* tempLoHiTxt       = NULL;
gslc_tsElemRef* tempUnitCB        = NULL;
gslc_tsElemRef* tempUnitToggle2   = NULL;
gslc_tsElemRef* tempUnitTxt       = NULL;
gslc_tsElemRef* useHeaterCB       = NULL;
gslc_tsElemRef* m_pElemKeyPadNum  = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_ELEM_BTN2:
        gslc_SetPageCur(&m_gui, E_PG_SUM);
        break;
      case E_ELEM_BTN3:
        gslc_SetPageCur(&m_gui, E_PG_STNG);
        break;
      case E_ELEM_BTN4:
        break;
      case E_ELEM_BTN7:
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_BTN11:
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_TOGGLE2:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, tempUnitToggle2)) {
          ;
        }
        break;
      case E_ELEM_BTN12:
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_BTN13:
        break;
      case E_ELEM_BTN14:
        break;
      case E_ELEM_NUMINPUT1:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, desiredTemp);
        break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
// KeyPad Input Ready callback
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)pvGui;
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  // From the pvData we can get the ID element that is ready.
  int16_t nTargetElemId = gslc_ElemXKeyPadDataTargetIdGet(pGui, pvData);
  if (nState == XKEYPAD_CB_STATE_DONE) {
    // User clicked on Enter to leave popup
    // - If we have a popup active, pass the return value directly to
    //   the corresponding value field
    switch (nTargetElemId) {
//<Keypad Enums !Start!>
      case E_ELEM_NUMINPUT1:
        gslc_ElemXKeyPadInputGet(pGui, desiredTemp, pvData);
	    gslc_PopupHide(&m_gui);
        break;

//<Keypad Enums !End!>
      default:
        break;
    }
  } else if (nState == XKEYPAD_CB_STATE_CANCEL) {
    // User escaped from popup, so don't update values
    gslc_PopupHide(&m_gui);
  }
  return true;
}
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>

//<Slider Enums !End!>
    default:
      break;
  }

  return true;
}

bool CbTickScanner(void* pvGui,void* pvScope)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvScope);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);

  //TODO add your custom code here 

  return true;
}
// **************** ABOVE IS GENERATED AUTOMATICALLY BY THE GUISLICE BUILDER **************** //


void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
  }
  Serial.println("CONNECTED to WIFI");

  // Get local time from ntp server via WiFi
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
	getLocalTime(&timeinfo);

  // Disconnect WiFi
   WiFi.disconnect(true);
   WiFi.mode(WIFI_OFF);

	pinMode(TDS_SENSOR, INPUT); // set TDS sensor
  tempSensor.begin(); // start temp sensor

  // Create graphic elements
  InitGUIslice_gen();
  gslc_InitDebug(&DebugOut);

	// Initial Setup
  initialSetup();

}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

	if (millis() - loopTime >= LOOP_UPDATE_DELAY) // Update what's inside every 5 seconds without interrupting the GUI from updating
	{
		loopTime += LOOP_UPDATE_DELAY; // Update loopTime

		// Get temp from temp sensor
		tempSensor.requestTemperatures();
		float temperature = tempSensor.getTempCByIndex(0);

		// Get TDS value from sensor
		getTDSVal();

		// Print Results to Serial Monitor
		Serial.print("TDS:");
		Serial.print(tdsValue, 0);
		Serial.print("ppm // ");

		Serial.print("Temperature: ");
		Serial.print(temperature);
		Serial.print("ºC / ");
		Serial.print(tempSensor.getTempFByIndex(0));
		Serial.print("ºF");
		
		Serial.println();

		} // End of update delay

		// Get current time and print it on screen
		getLocalTime(&timeinfo); // Update time
		char clock[26];
		strftime(clock, 26, "%H:%M:%S %m/%d/%y", &timeinfo); // Format time
		gslc_ElemSetTxtStr(&m_gui, clockTxt, clock);				 // Update sreen text

		// Set the ring meter's values (TODO: change to get the values from the sensors)
		updateGauge(tempGauge, tempLoHiTxt, 80, 77, 81);
		updateGauge(tdsGauge, tdsLoHiTxt, 302, 299, 304);
		updateGauge(phGauge, phLoHiTxt, 62.2, 59, 64);

		// ------------------------------------------------
		// Periodically call GUIslice update function
		// ------------------------------------------------
		gslc_Update(&m_gui);

} // End of loop




void testSensors() 
{

}

/**
 * @brief Initial setup for the device.
 * 
 */
void initialSetup()
{

	// Set the ring's value text color, font and the ring's min and max values for each ring.
	setTxtStyle(tempGauge, GSLC_COL_WHITE, E_BUILTIN15X24);
	gslc_ElemXRingGaugeSetValRange(&m_gui, tempGauge, 0, 80);
	setTxtStyle(phGauge, GSLC_COL_WHITE, E_BUILTIN15X24);
	gslc_ElemXRingGaugeSetValRange(&m_gui, phGauge, 0, 100);
	setTxtStyle(tdsGauge, GSLC_COL_WHITE, E_BUILTIN15X24);
	gslc_ElemXRingGaugeSetValRange(&m_gui, tdsGauge, 0, 1000);

	// Set each ring's unit text
	gslc_ElemSetTxtStr(&m_gui, tdsUnitTxt, "ppm");
	gslc_ElemSetTxtStr(&m_gui, phUnitTxt, "pH");
	snprintf(tempUnit, 10, "%cF", 247);
	gslc_ElemSetTxtStr(&m_gui, tempUnitTxt, tempUnit);


}

/**
 * @brief Reads data from the TDS sensor and calculates the TDS value 
 *        and stores it in 'tdsValue' variable
 * 
 */
void getTDSVal()
{
	static unsigned long analogSampleTimepoint = millis();
	if (millis() - analogSampleTimepoint > 40U) //every 40 milliseconds,read the analog value from the ADC
	{
		analogSampleTimepoint = millis();
		analogBuffer[analogBufferIndex] = analogRead(TDS_SENSOR); //read the analog value and store into the buffer
		analogBufferIndex++;
		if (analogBufferIndex == SCOUNT)
			analogBufferIndex = 0;
	}
	static unsigned long printTimepoint = millis();
	if (millis() - printTimepoint > 800U)
	{
		printTimepoint = millis();
		for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
			analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
		averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0;																																																	 // read the analog value more stable by the median filtering algorithm, and convert to voltage value
		float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);																																																							 //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
		float compensationVolatge = averageVoltage / compensationCoefficient;																																																						 //temperature compensation
		tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; //convert voltage value to tds value
	}
}

/**
 * @brief Set the element's text color and font
 * 
 * @param pElemRef: Pointer to element reference
 * @param colVal: RGB color to change to
 * @param nFontId: Font id to use
 */
void setTxtStyle(gslc_tsElemRef *pElemRef, gslc_tsColor colVal, int nFontId)
{

	gslc_ElemSetTxtCol(&m_gui, pElemRef, colVal);
	gslc_ElemUpdateFont(&m_gui, pElemRef, nFontId);
}

/**
 * @brief Updates ring meter's value (along with low/high values) and update the GUI
 * 
 * @param pElemRef: Ring meter to update
 * @param pSubElemRef: The ring meter's Low/High text element
 * @param n: Value to set ring meter to
 * @param lo: Low value
 * @param hi: High value
 */
void updateGauge(gslc_tsElemRef *pElemRef, gslc_tsElemRef *pSubElemRef, int n, int lo, int hi)
{

	char nStr[5], loHi[10];
	sprintf(nStr, "%d", n);
	sprintf(loHi, "%c%d %c%d", 25, lo, 24, hi);

	gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, n);
	gslc_ElemSetTxtStr(&m_gui, pElemRef, nStr);
	gslc_ElemSetTxtStr(&m_gui, pSubElemRef, loHi);
}

/**
 * @brief getTDSVal helper function
 */
int getMedianNum(int bArray[], int iFilterLen)
{
	int bTab[iFilterLen];
	for (byte i = 0; i < iFilterLen; i++)
		bTab[i] = bArray[i];
	int i, j, bTemp;
	for (j = 0; j < iFilterLen - 1; j++)
	{
		for (i = 0; i < iFilterLen - j - 1; i++)
		{
			if (bTab[i] > bTab[i + 1])
			{
				bTemp = bTab[i];
				bTab[i] = bTab[i + 1];
				bTab[i + 1] = bTemp;
			}
		}
	}
	if ((iFilterLen & 1) > 0)
		bTemp = bTab[(iFilterLen - 1) / 2];
	else
		bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;

	return bTemp;
}
