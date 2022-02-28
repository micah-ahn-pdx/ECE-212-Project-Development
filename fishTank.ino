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
#include <ESP_Mail_Client.h>
#include "time.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "ph_grav.h"
#include <AsyncDelay.h>

// *** VARIABLES *** //
#define RELAY_PIN   5	  	// Relay pin
#define TEMP_SENSOR 23      // Temp sensor pin
#define TDS_SENSOR  36			// TDS Sensor pin
#define PH_SENSOR   34      // pH sensor pin

#define VREF        3.3     // [TDS] analog reference voltage(Volt) of the ADC
#define SCOUNT      30      // [TDS] sum of sample point

// WiFi Setup
#define SSID "M XI"
#define SSID_PWD "01001101!"
#define SMTP_HOST "smtp.gmail.com"                      // Mail Server name
#define SMTP_PORT 465                                   // Use Port 465 for Gmail
#define AUTHOR_EMAIL "PSU.FishTankMonitor@gmail.com"    // Email sender credentials
#define AUTHOR_PASSWORD "PortlandState"                 // Sending email password
/* Recipient's email*/
#define RECIPIENT_EMAIL "enter email here"
/* The SMTP Session object used for Email sending */
SMTPSession smtp;

// loop update variable
unsigned long loopTime = 0L;
AsyncDelay mainDelay(15000, AsyncDelay::MILLIS);    // main loop delay (15 seconds)
AsyncDelay graphDelay(100, AsyncDelay::MILLIS);     // very small delay before drawing the graph (so it won't overlap with the home page)
AsyncDelay alertDelay(30000, AsyncDelay::MILLIS);   // Delay between showing alerts

// Getting Time
#define NTP_SERVER      "pool.ntp.org"  // time protocol server
#define GMT_OFFSET      -28800          // GMT offset (seconds)
#define DAYLIGHT_OFFSET 3600            // daylight offset (seconds)
struct tm timeinfo;
int curHr = -1, prevHr = -1;

// Temp
OneWire oneWire(TEMP_SENSOR);
DallasTemperature tempSensor(&oneWire);
double tempC = 0, tempLo = 9999, tempHi = -9999; // Where to store current temperature
int desiredTemp = 75;
bool heaterOn = false;

// TDS
int analogBuffer[SCOUNT]; 			// store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
double averageVoltage = 0, tdsValue = 0, tdsLo = 9999, tdsHi = -9999;

// pH
Gravity_pH pH = Gravity_pH(PH_SENSOR);
double phVal, phLo = 9999, phHi = -9999;

// Graph variables
boolean redrawGraph = true;
double ox , oy;

// Logging data
typedef struct logNode // struct that holds all the logging stuff
{
  double tempVal[24] = {25, 26, 21, 23, 20, 25, 23, 21, 18, 27, 29, 30, 26, 32, 22, 19, 23, 20, 28, 22, 26, 28, 24, 29}; // dummy temps for testing
  double tdsVal[24], phVal[24];
  char logTime[24][5] = {"12AM", "1AM", "2AM", "3AM", "4AM", "5AM", "6AM", "7AM", "8AM", "9AM", "10AM", "11AM", "12PM", "1PM", "2PM", "3PM", "4PM", "5PM", "6PM", "7PM", "8PM", "9PM", "10PM", "11PM"};
  int curIndex = -1, startIndex = -1, selectedSum = 0;
  boolean isFull = false;
} logNode;
// Initiate dataLog where we'll store the past 24hrs readings
logNode dataLog; 



// **************** BELOW IS GENERATED AUTOMATICALLY BY THE GUISLICE BUILDER **************** //
// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* alertMsgTxt       = NULL;
gslc_tsElemRef* btnSettings       = NULL;
gslc_tsElemRef* btnSettings25_26  = NULL;
gslc_tsElemRef* btnSummary        = NULL;
gslc_tsElemRef* calpHStatTxt      = NULL;
gslc_tsElemRef* clockTxt          = NULL;
gslc_tsElemRef* desiredTempElem   = NULL;
gslc_tsElemRef* heaterStatTxt     = NULL;
gslc_tsElemRef* noHeaterCB        = NULL;
gslc_tsElemRef* phGauge           = NULL;
gslc_tsElemRef* phLoHiTxt         = NULL;
gslc_tsElemRef* phSumBtn          = NULL;
gslc_tsElemRef* phUnitTxt         = NULL;
gslc_tsElemRef* settingsTempUnitTxt= NULL;
gslc_tsElemRef* statusbarText     = NULL;
gslc_tsElemRef* tdsGauge          = NULL;
gslc_tsElemRef* tdsLoHiTxt        = NULL;
gslc_tsElemRef* tdsSumBtn         = NULL;
gslc_tsElemRef* tdsUnitTxt        = NULL;
gslc_tsElemRef* tempGauge         = NULL;
gslc_tsElemRef* tempLoHiTxt       = NULL;
gslc_tsElemRef* tempSumBtn        = NULL;
gslc_tsElemRef* tempUnitToggle    = NULL;
gslc_tsElemRef* tempUnitTxt       = NULL;
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
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Summary");
        redrawGraph = true;
        graphDelay.restart();
        break;
      case E_ELEM_BTN_STNGS:
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Settings");
        gslc_SetPageCur(&m_gui, E_PG_STNG);
        break;
      case E_ELEM_BTN7:
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_BTN_HOME1:
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Home");
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_BTN_TEMPSUM:
        dataLog.selectedSum = 0;
        redrawGraph = true;
        handleGraphUpdate();
        break;
      case E_ELEM_BTN_TDSSUM:
        dataLog.selectedSum = 1;
        redrawGraph = true;
        handleGraphUpdate();
        break;
      case E_ELEM_BTN_PHSUM:
        dataLog.selectedSum = 2;
        redrawGraph = true;
        handleGraphUpdate();
        break;
      case E_ELEM_TOGGLE2:
        handleTempUnitToggle();
        break;
      case E_ELEM_BTN_HOME2:
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Home");
        controlHeater(); // Just to update the heater label to reflect changes to override setting
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_NUMINPUT_TEMP:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, desiredTempElem);
        break;
      case E_ELEM_BTN_STNG_CALPH:
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Calibrating pH");
        gslc_ElemSetTxtStr(&m_gui, calpHStatTxt, " ");
        gslc_SetPageCur(&m_gui, E_PG_CALPH);
        break;
      case E_ELEM_BTN_CALPH_LO:
        gslc_ElemSetTxtStr(&m_gui, calpHStatTxt, "Successfully Calibrated Low (4.00)");
        pH.cal_low();
        break;
      case E_ELEM_BTN_CALPH_MD:
        gslc_ElemSetTxtStr(&m_gui, calpHStatTxt, "Successfully Calibrated Medium (7.00)");
        pH.cal_mid();
        break;
      case E_ELEM_BTN_CALPH_HI:
        gslc_ElemSetTxtStr(&m_gui, calpHStatTxt, "Successfully Calibrated High (10.00)");
        pH.cal_high();
        break;
      case E_ELEM_BTN_HOME3:
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Home");
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_BTN_CALPH_CLR:
        gslc_ElemSetTxtStr(&m_gui, calpHStatTxt, "Successfully Cleared Calibration");
        pH.cal_clear();
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

      case E_ELEM_NUMINPUT_TEMP:
        gslc_ElemXKeyPadInputGet(pGui, desiredTempElem, pvData);
	      gslc_PopupHide(&m_gui);
        handleDesiredTemp();
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
//<Slider Enums !Start!>
//<Slider Enums !End!>


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
  // * SETUP
  Serial.begin(115200);

  //connect to WiFi
  Serial.printf("Connecting to %s ", SSID);
  WiFi.begin(SSID, SSID_PWD);
  while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
  }
  Serial.println("CONNECTED to WIFI");

  // Get local time from ntp server via WiFi
  configTime(GMT_OFFSET, DAYLIGHT_OFFSET, NTP_SERVER);
	getLocalTime(&timeinfo);
  dataLog.startIndex = timeinfo.tm_min%24; // Get the current hour (when the device is first turned on)

  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

	pinMode(TDS_SENSOR, INPUT); // set TDS sensor
  tempSensor.begin();         // start temp sensor
  pH.begin();                 // start pH sensor

	// Initialize Relay pin as an output
	pinMode(RELAY_PIN, OUTPUT);

  // Create graphic elements
  InitGUIslice_gen();
  gslc_InitDebug(&DebugOut);

	// Initial Setup
  initSetup();

  // Disconnect WiFi
   WiFi.disconnect(true);
   WiFi.mode(WIFI_OFF);

}

// * Main program loop
void loop()
{
  getLocalTime(&timeinfo); // Update time

	if (mainDelay.isExpired()) // Update what's inside every 15 seconds (without interrupting the GUI from updating).
	{
    mainDelay.repeat();

    // main sensors func
    testSensors();

    controlHeater(); // Check whether to turn the heater on/off

    logData(); // Logs data every 1hr

    // Draws the graph when the user is in the summary page
    handleGraphUpdate();

    // * Debug stuff: 
		// Get temp
		tempSensor.requestTemperatures();
		tempC = tempSensor.getTempCByIndex(0);
		getTDSVal();
		// Print Results to Serial Monitor
		Serial.print("TDS: ");
		Serial.print(tdsValue, 0);
		Serial.print("ppm  //  ");
		Serial.print("Temperature: ");
		Serial.print(tempSensor.getTempCByIndex(0));
		Serial.print("ºC  //  pH: ");
    Serial.println(pH.read_ph());
		
	} // End of 5sec update delay

  // Trigger drawing graph (when summary button is pressed)
  if (redrawGraph && graphDelay.isExpired()) handleGraphUpdate();

	// Get current time and print it on screen
  char clock[26];
	strftime(clock, 26, "%I:%M:%S%p %m/%d/%y", &timeinfo);  // Format time
	gslc_ElemSetTxtStr(&m_gui, clockTxt, clock);				    // Update sreen text

  // Periodically call GUIslice update function
	gslc_Update(&m_gui);   

} // End of loop


/**
 * @brief Reads the data from the sensors and updates the GUI accordingly
 * 
 */
void testSensors() 
{
  // * Temperature
  tempSensor.requestTemperatures();
	tempC = tempSensor.getTempCByIndex(0);

  if (tempC < tempLo) tempLo = tempC;
  if (tempC > tempHi) tempHi = tempC;
  
  if (gslc_ElemXTogglebtnGetState(&m_gui, tempUnitToggle))
  { // display temp in F
    updateGauge(tempGauge, tempLoHiTxt, tempSensor.toFahrenheit(tempC), tempSensor.toFahrenheit(tempLo), tempSensor.toFahrenheit(tempHi), 0);
  } else 
  { // display temp in C
    updateGauge(tempGauge, tempLoHiTxt, tempC, tempLo, tempHi, 0);
  }


  // * TDS
  getTDSVal(); // Updates 'tdsValue' variable
  if (tdsValue < tdsLo && tdsValue >= 0) tdsLo = tdsValue;
  if (tdsValue > tdsHi) tdsHi = tdsValue;
  
  if (tdsValue <= 0) updateGauge(tdsGauge, tdsLoHiTxt, -1, tdsLo, tdsHi, 0);
  else updateGauge(tdsGauge, tdsLoHiTxt, tdsValue, tdsLo, tdsHi, 0);


  // * pH
  phVal = pH.read_ph();
  if (phVal < phLo && phVal >= 0) phLo = phVal;
  if (phVal > phHi) phHi = phVal;
  
  if (phVal <= 0) updateGauge(phGauge, phLoHiTxt, -1, phLo, phHi, 1);
  else updateGauge(phGauge, phLoHiTxt, phVal, phLo, phHi, 1);

  
}

/**
 * @brief Initial setup for the device.
 * 
 */
void initSetup()
{  

	// Set the ring's value text color, font and the ring's min and max values for each ring.
	setTxtStyle(tempGauge, GSLC_COL_WHITE, E_BUILTIN15X24);
	gslc_ElemXRingGaugeSetValRange(&m_gui, tempGauge, 32, 90);
	setTxtStyle(phGauge, GSLC_COL_WHITE, E_BUILTIN15X24);
	gslc_ElemXRingGaugeSetValRange(&m_gui, phGauge, 0, 15);
	setTxtStyle(tdsGauge, GSLC_COL_WHITE, E_BUILTIN15X24);
	gslc_ElemXRingGaugeSetValRange(&m_gui, tdsGauge, 0, 1000);

	// Set each ring's unit text
	gslc_ElemSetTxtStr(&m_gui, tdsUnitTxt, "ppm");
	gslc_ElemSetTxtStr(&m_gui, phUnitTxt, "pH");
	gslc_ElemSetTxtStr(&m_gui, tempUnitTxt, (char*)"\xf7""F");
  gslc_ElemSetTxtStr(&m_gui, settingsTempUnitTxt, (char*)"\xf7""F");
  

  testSensors();
  mainDelay.expire(); // When the app first starts, expire the main loop timer so the code executes immediately
  alertDelay.restart();

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
		float compensationCoefficient = 1.0 + 0.02 * (tempSensor.getTempCByIndex(0) - 25.0);																																																							 //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
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
 * @param dbl: Whether to show the values as floating number (true) or integer (false)
 */
void updateGauge(gslc_tsElemRef *pElemRef, gslc_tsElemRef *pSubElemRef, double n, double lo, double hi, bool dbl)
{
	char nStr[25], loHi[25];
  if (dbl)
  {
    sprintf(nStr, "%.2lf", n);
	  sprintf(loHi, "%c%.2lf %c%.2lf", 25, lo, 24, hi);
  } 
  else 
  {
    sprintf(nStr, "%.0lf", n);
	  sprintf(loHi, "%c%.0lf %c%.0lf", 25, lo, 24, hi);
  }
  

	gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, n);
	gslc_ElemSetTxtStr(&m_gui, pElemRef, nStr);
	gslc_ElemSetTxtStr(&m_gui, pSubElemRef, loHi);

  if (n <= 0) gslc_ElemSetTxtStr(&m_gui, pElemRef, "-");
}


/**
 * Heater element function
 * 
 */
void controlHeater()
{
  digitalWrite(RELAY_PIN, HIGH);
  // Update heater status label
  if (gslc_ElemXCheckboxGetState(&m_gui, noHeaterCB))
  {
    gslc_ElemSetTxtStr(&m_gui, heaterStatTxt, "Heater is Disabled");
    digitalWrite(RELAY_PIN, LOW);
  }
  else if (heaterOn) gslc_ElemSetTxtStr(&m_gui, heaterStatTxt, "Heater is Currently On");
  else gslc_ElemSetTxtStr(&m_gui, heaterStatTxt, "Heater is Currently Off");
  

	int lowerLimit = desiredTemp - 2;
	int upperLimit = desiredTemp + 2;
  // Set pin to HIGH to turn on - Set pin to LOW to turn off

	if (tempC > 26.66) // if temperature is too high
	{
    // Turn heater off
		digitalWrite(RELAY_PIN, LOW);
    heaterOn = false;
		showAlert("Temperature is critically high");
		//display visual alarm   *maybe make a function for alarms, either together or seperate
		//initiate speaker alarm
	}
	else if (tempC < 18.33) // if temperature is too low
	{
    // Turn heater on (first check if override not checked)
    if (!gslc_ElemXCheckboxGetState(&m_gui, noHeaterCB))
    {
      digitalWrite(RELAY_PIN, HIGH);
      heaterOn = true;
    }
		showAlert("Temperature is critically low");
		//display visual alarm
		//initiate speaker alarm
	}
	else if (tempC <= lowerLimit) // if temperature is less than desired temp
	{
    // Turn heater on (first check if override not checked)
    if (!gslc_ElemXCheckboxGetState(&m_gui, noHeaterCB))
    {
      digitalWrite(RELAY_PIN, HIGH);
      heaterOn = true;
    }
    
	}
	else if (tempC >= upperLimit) // if temperature is more than desired temp
	{
    // Turn heater off
		digitalWrite(RELAY_PIN, LOW);
    heaterOn = false;
	} else { // Perfect Temperature, turn off
    // Turn heater off
		digitalWrite(RELAY_PIN, LOW);
    heaterOn = false;
  }
  
}


/**
 * @brief Handles switching between temperature units
 * 
 */
void handleTempUnitToggle()
{
  char tempstr[2];
  int temp;

  if (gslc_ElemXTogglebtnGetState(&m_gui, tempUnitToggle))
  { // use F
    gslc_ElemSetTxtStr(&m_gui, tempUnitTxt, (char *)"\xf7""F");
    gslc_ElemSetTxtStr(&m_gui, settingsTempUnitTxt, (char *)"\xf7""F");
    gslc_ElemXRingGaugeSetValRange(&m_gui, tempGauge, 32, 90);

    sscanf(gslc_ElemGetTxtStr(&m_gui, desiredTempElem), "%d", &temp);
    sprintf(tempstr, "%.0lf", tempSensor.toFahrenheit(temp));
    gslc_ElemSetTxtStr(&m_gui, desiredTempElem, tempstr);
  }
  else
  { // use C
    gslc_ElemSetTxtStr(&m_gui, tempUnitTxt, (char *)"\xf7""C");
    gslc_ElemSetTxtStr(&m_gui, settingsTempUnitTxt, (char *)"\xf7""C");
    gslc_ElemXRingGaugeSetValRange(&m_gui, tempGauge, 0, 35);

    sscanf(gslc_ElemGetTxtStr(&m_gui, desiredTempElem), "%d", &temp);
    sprintf(tempstr, "%.0lf", tempSensor.toCelsius(temp));
    gslc_ElemSetTxtStr(&m_gui, desiredTempElem, tempstr);
  }
  testSensors();
}


/**
 * @brief getTDSVal helper function
 * 
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


/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);

/* Function to send email to user */ 
void SendEmail(int tdsValue, int temperature){
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to AP");
  WiFi.begin(SSID, SSID_PWD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /** Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1
  */
  smtp.debug(1);

  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);

  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;

  /* Set the message headers */
  message.sender.name = "Fish Tank Status";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Update";
  // message.addRecipient("Sara", RECIPIENT_EMAIL);

  /*Send HTML message*/
  String htmlMsg = "<div style=\"color:#2f4468;\"><h1>Enter text here</h1><p>- Sent from Fish Tank Monitor</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());

  // Disconnect WiFi
   WiFi.disconnect(true);
   WiFi.mode(WIFI_OFF);
}

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status){
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success()){
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++){
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients);
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject);
    }
    Serial.println("----------------\n");
  }

}


// * PORTED & MODIFIED FROM SRC: https://forum.arduino.cc/t/another-free-graph-function-for-plotting-in-cartesian-space/354751 *
/**
 * function to draw a cartesian coordinate system and plot whatever data you want
 * just pass x and y and the graph will be drawn
 * 
 * @param dx: x data point (For current hour) | This is used to set at what time does the x axis start from.
 * @param x: x data point
 * @param y: y datapont
 * @param gx: x graph location (lower left)
 * @param gy: y graph location (lower left)
 * @param w: width of graph
 * @param h: height of graph
 * @param xlo: lower bound of x axis
 * @param xhi: upper bound of x asis
 * @param xinc: division of x axis (distance not count)
 * @param ylo: lower bound of y axis
 * @param yhi: upper bound of y asis
 * @param yinc: division of y axis (distance not count)
 * @param xlabel: x asis label
 * @param ylabel: y asis label
 * @param gcolor: graph line colors
 * @param acolor: axi ine colors
 * @param pcolor: color of your plotted data
 * @param tcolor: text color
 * @param bcolor: background color
 * @param redraw: flag to redraw graph on fist call only
 */
void Graph(int dx, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, char* xlabel, char* ylabel, gslc_tsColor gcolor, gslc_tsColor acolor, gslc_tsColor pcolor, gslc_tsColor tcolor, gslc_tsColor bcolor, boolean &redraw) {

  double i;
  double temp;
  static char bufstr[15];

  if (redraw == true) {

    redraw = false;
    gslc_DrawFillRect(&m_gui, (gslc_tsRect){gx-30,gy-h-10,w+40,h+30}, bcolor);

    // initialize old x and old y in order to draw the first point of the graph
    // but save the transformed value
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        gslc_DrawLine(&m_gui, gx, temp, gx + w, temp, acolor);
      }
      else {
        gslc_DrawLine(&m_gui, gx, temp, gx + w, temp, gcolor);
      }
      // draw the axis labels
	    sprintf(bufstr, "%.0lf", i);
      gslc_DrawTxtBase(&m_gui, bufstr, (gslc_tsRect){gx - 40, temp,30,10}, &m_asFont[E_BUILTIN5X8], GSLC_TXT_ALLOC_INT, GSLC_ALIGN_BOT_RIGHT, tcolor, bcolor, 0, 0);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform
      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        gslc_DrawLine(&m_gui, temp, gy, temp, gy - h, acolor);
      }
      else {
        gslc_DrawLine(&m_gui, temp, gy, temp, gy - h, gcolor);
      }
      // draw the axis labels on every other axis
      if ((int)i%2 == 0) 
        gslc_DrawTxtBase(&m_gui, dataLog.logTime[(int)(dx+i)%24], (gslc_tsRect){temp, gy + 10,30,10}, &m_asFont[E_BUILTIN5X8], GSLC_TXT_ALLOC_INT, GSLC_ALIGN_TOP_LEFT, tcolor, bcolor, 0, 0);
    }

    // draw the graph labels
    // gslc_DrawTxtBase(&m_gui, title, (gslc_tsRect){gx, gy - h - 30, 250,18}, &m_asFont[E_BUILTIN10X16], GSLC_TXT_ALLOC_INT, GSLC_ALIGN_MID_MID, tcolor, bcolor, 0, 0);
    gslc_DrawTxtBase(&m_gui, xlabel, (gslc_tsRect){gx, gy + 20, 100,10}, &m_asFont[E_BUILTIN5X8], GSLC_TXT_ALLOC_INT, GSLC_ALIGN_MID_LEFT, pcolor, bcolor, 0, 0);
    gslc_DrawTxtBase(&m_gui, ylabel, (gslc_tsRect){gx - 30, gy - h - 10, 100,10}, &m_asFont[E_BUILTIN5X8], GSLC_TXT_ALLOC_INT, GSLC_ALIGN_MID_LEFT, pcolor, bcolor, 0, 0);
    
  }

  // the coordinates are now drawn, plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  if (ox <= x)
  {
    gslc_DrawLine(&m_gui, ox, oy, x, y, pcolor);
    // it's up to you but drawing 2 more lines to give the graph some thickness
    gslc_DrawLine(&m_gui, ox, oy + 1, x, y + 1, pcolor);
    gslc_DrawLine(&m_gui, ox, oy - 1, x, y - 1, pcolor);
    ox = x;
    oy = y;
  }

}


void logData()
{
  curHr = timeinfo.tm_min%24; // DEBUG: for now it logs every minute (for testing purposes) need to change to 'tm_hour' in final build

  if (curHr != prevHr) // Update what's inside every 1 hour
	{
		// Log the temperature value
    dataLog.tempVal[curHr] = tempC;
    dataLog.phVal[curHr] = phVal;
    dataLog.tdsVal[curHr] = tdsValue;

    dataLog.curIndex = curHr; // Update the log current index to the current hour

    if ((dataLog.curIndex+1)%24 == dataLog.startIndex) dataLog.isFull = true; // Mark the log full recording the first 24hr worth of data

    if (curHr == 0)
    {
      // Reset lo/hi values every day at 12AM
      tempLo = tdsLo = phLo = 9999;
      tempHi = tdsHi = phHi = -9999;
    }
    
    redrawGraph = true;
		prevHr = curHr;
	}
}


/**
 * @brief Handles drawing and updating the graph in the summary page
 * 
 */
void handleGraphUpdate() {
  if (gslc_GetPageCur(&m_gui) == E_PG_SUM) // Only draw/update if the user is in the summary page & every 1s
  { 

    double gx = 40, gy = 210, gw = 420, gh = 170;
    int x, y; // needed variables for the plot
    int iCap = (dataLog.isFull) ? 23 : dataLog.curIndex - dataLog.startIndex; // How many x data to plot is determined by how many hours passed if the log isn't full yet, and if it's full it's always 24(with the 0).

    if (dataLog.selectedSum == 0) 
    {
      gslc_ElemSetTxtStr(&m_gui, statusbarText, "Temperature Summary");
      // Highlight selected tab/btn
      if (redrawGraph) {
        gslc_ElemSetCol(&m_gui, tempSumBtn,GSLC_COL_WHITE,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT3);
        gslc_ElemSetCol(&m_gui, tdsSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
        gslc_ElemSetCol(&m_gui, phSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
      }

    } else if (dataLog.selectedSum == 1)
    {
      gslc_ElemSetTxtStr(&m_gui, statusbarText, "TDS Summary");
      // Highlight selected tab/btn
      if (redrawGraph) {
        gslc_ElemSetCol(&m_gui, tdsSumBtn,GSLC_COL_WHITE,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT3);
        gslc_ElemSetCol(&m_gui, tempSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
        gslc_ElemSetCol(&m_gui, phSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
      }

    } else 
    {
      gslc_ElemSetTxtStr(&m_gui, statusbarText, "pH Summary");
      // Highlight selected tab/btn
      if (redrawGraph) {
        gslc_ElemSetCol(&m_gui, phSumBtn,GSLC_COL_WHITE,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT3);
        gslc_ElemSetCol(&m_gui, tdsSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
        gslc_ElemSetCol(&m_gui, tempSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
      }
    }

    for (int i = 0; i <= iCap; i++) 
    {
      // Check if there is a 24hrs worth of data logged or not
      if (dataLog.isFull)
      {
        x = (i+dataLog.curIndex+1) % 24; // If there is, start the x axis from the next hour (so plot ends with the current hour value).
      } else {
        x = (i+dataLog.startIndex) % 24; // If not, start the x axis from the first hour when the device was turned on.
      }

      if (dataLog.selectedSum == 0)
      {
        // Draw the temperature plot (Shows values in C or F depending on user's preference)
        if (gslc_ElemXTogglebtnGetState(&m_gui, tempUnitToggle)) 
        {
          y = tempSensor.toFahrenheit(dataLog.tempVal[x]);
          Graph(x, i, y, gx, gy, gw, gh, 0, 23, 1, 50, 90, 10, "time of day", "temperature (\xf7""F)", GSLC_COL_GRAY_DK3, GSLC_COL_GRAY_DK3, GSLC_COL_BLUE_LT4, GSLC_COL_WHITE, GSLC_COL_BLACK, redrawGraph);
        } else 
        {
          y = dataLog.tempVal[x];
          Graph(x, i, y, gx, gy, gw, gh, 0, 23, 1, 10, 35, 5, "time of day", "temperature (\xf7""C)", GSLC_COL_GRAY_DK3, GSLC_COL_GRAY_DK3, GSLC_COL_BLUE_LT4, GSLC_COL_WHITE, GSLC_COL_BLACK, redrawGraph);
        }
      
      } else if (dataLog.selectedSum == 1)
      {
        // graph TDS
        Graph(x, i, dataLog.tdsVal[x], gx, gy, gw, gh, 0, 23, 1, 10, 35, 5, "time of day", "TDS (ppm)", GSLC_COL_GRAY_DK3, GSLC_COL_GRAY_DK3, GSLC_COL_BLUE_LT4, GSLC_COL_WHITE, GSLC_COL_BLACK, redrawGraph);
      }
      else
      {
        // graph pH
        Graph(x, i, dataLog.phVal[x], gx, gy, gw, gh, 0, 23, 1, 0, 15, 3, "time of day", "pH Level (pH)", GSLC_COL_GRAY_DK3, GSLC_COL_GRAY_DK3, GSLC_COL_BLUE_LT4, GSLC_COL_WHITE, GSLC_COL_BLACK, redrawGraph);
      }
      

    }

  }
}

/**
 * @brief Handles the desired temperature option in the settings (checks edge cases, etc)
 * 
 */
void handleDesiredTemp()
{
  
  double usrTemp;
  sscanf(gslc_ElemGetTxtStr(&m_gui, desiredTempElem), "%lf", &usrTemp);

  if (gslc_ElemXTogglebtnGetState(&m_gui, tempUnitToggle))
  { // use F
    if (usrTemp > 80)
    {
      gslc_ElemSetTxtStr(&m_gui, desiredTempElem, "80");
      usrTemp = 80;
    } 
    else if (usrTemp < 65) 
    {
      gslc_ElemSetTxtStr(&m_gui, desiredTempElem, "65");
      usrTemp = 65;
    }

    usrTemp = tempSensor.toCelsius(usrTemp);
    
  }
  else
  { // use C
    if (usrTemp > 27)
    {
      gslc_ElemSetTxtStr(&m_gui, desiredTempElem, "27");
      usrTemp = 27;
    } 
    else if (usrTemp < 18) 
    {
      gslc_ElemSetTxtStr(&m_gui, desiredTempElem, "18");
      usrTemp = 18;
    }
  }

  desiredTemp = usrTemp;
}


/**
 * @brief Shows a warning alert popup with a custom message
 * 
 * @param msg: custom message
 */
void showAlert(char *msg)
{
  if (alertDelay.isExpired())
  {
    alertDelay.restart();
    gslc_ElemSetTxtStr(&m_gui, alertMsgTxt, msg);
    gslc_PopupShow(&m_gui, E_PG_POPUP_NOTIFY, true);
    redrawGraph = true;
  }
  
}
