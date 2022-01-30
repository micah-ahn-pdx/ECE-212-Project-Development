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
#include <Arduino.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include "time.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// * 
#define RELAY_PIN   13	  	// Relay pin
#define TEMP_SENSOR 4			  // Temp sensor pin
#define TDS_SENSOR  25			// TDS Sensor pin

#define VREF        3.3     // [TDS] analog reference voltage(Volt) of the ADC
#define SCOUNT      30      // [TDS] sum of sample point
#define ONE_HOUR            60*60*1000L	    // 1 Hour
#define LOOP_UPDATE_DELAY   5*1000L         // 5 Seconds

#define SMTP_HOST "smtp.gmail.com"                      // Mail Server name
#define SMTP_PORT 465                                   // Use Port 465 for Gmail
#define AUTHOR_EMAIL "PSU.FishTankMonitor@gmail.com"    // Email sender credentials
#define AUTHOR_PASSWORD "PortlandState"                 // Sending email password

/* Recipient's email*/
#define RECIPIENT_EMAIL "enter email here"

/* The SMTP Session object used for Email sending */
SMTPSession smtp;

// * Starting Variables
// loop update variable
unsigned long loopTime = 0L ;
// WiFi Setup
const char* ssid = "01001101";
const char* pwd = "0x01001101";
// Getting Time
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -28800;   // GMT offset (seconds)
const int   daylightOffset_sec = 3600;  // daylight offset (seconds)
struct tm timeinfo;
// Temp
OneWire oneWire(TEMP_SENSOR);
DallasTemperature tempSensor(&oneWire);
float tempC = 0, tempLo = 999, tempHi = -999; // Where to store current temperature
// TDS
int analogBuffer[SCOUNT]; 			// store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, tdsLo = 999, tdsHi = -999;

// these are the only external variables used by the graph function
// it's a flag to draw the coordinate system only on the first call to the Graph() function
// and will mimize flicker
// also create some variables to store the old x and y, if you draw 2 graphs on the same display
// you will need to store ox and oy per each display
boolean redrawGraph = true;
double ox , oy ;


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
gslc_tsElemRef* noHeaterCB        = NULL;
gslc_tsElemRef* phGauge           = NULL;
gslc_tsElemRef* phLoHiTxt         = NULL;
gslc_tsElemRef* phUnitTxt         = NULL;
gslc_tsElemRef* settingsTempUnitTxt= NULL;
gslc_tsElemRef* statusbarText     = NULL;
gslc_tsElemRef* tdsGauge          = NULL;
gslc_tsElemRef* tdsLoHiTxt        = NULL;
gslc_tsElemRef* tdsUnitTxt        = NULL;
gslc_tsElemRef* tempGauge         = NULL;
gslc_tsElemRef* tempLoHiTxt       = NULL;
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
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Summary");
        redrawGraph = true;
        gslc_SetPageCur(&m_gui, E_PG_SUM);
        break;
      case E_ELEM_BTN_STNGS:
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Settings");
        gslc_SetPageCur(&m_gui, E_PG_STNG);
        break;
      case E_ELEM_BTN4:
        break;
      case E_ELEM_BTN7:
        gslc_PopupHide(&m_gui);
        break;
      case E_ELEM_BTN_HOME1:
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Home");
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_TOGGLE2:
        handleTempUnitToggle();
        break;
      case E_ELEM_BTN_HOME2:
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Home");
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
  initSetup();

	// Initialize Relay pin as an output
	pinMode(RELAY_PIN, OUTPUT);
}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

	if (millis() - loopTime >= LOOP_UPDATE_DELAY) // Update what's inside every 5 seconds (without interrupting the GUI from updating).
	{
		loopTime += LOOP_UPDATE_DELAY; // Update loopTime

    // main sensors func
    testSensors();


    // * Debug stuff: 
		// Get temp
		tempSensor.requestTemperatures();
		tempC = tempSensor.getTempCByIndex(0);
		getTDSVal();
		// Print Results to Serial Monitor
		Serial.print("TDS:");
		Serial.print(tdsValue, 0);
		Serial.print("ppm // ");
		Serial.print("Temperature: ");
		Serial.print(tempC);
		Serial.println("ºC");
		
	} // End of 5sec update delay

	// Get current time and print it on screen
	getLocalTime(&timeinfo); // Update time
	char clock[26];
	strftime(clock, 26, "%H:%M:%S %m/%d/%y", &timeinfo); // Format time
	gslc_ElemSetTxtStr(&m_gui, clockTxt, clock);				 // Update sreen text		

	// ------------------------------------------------
	// Periodically call GUIslice update function
	// ------------------------------------------------
	gslc_Update(&m_gui);

  if (gslc_GetPageCur(&m_gui) == E_PG_SUM) {
    // Testing graph
    double x, y;
    for (x = 0; x <= 23; x += .1) {
      y = sin(x);
      Graph(x, y, 60, 230, 350, 180, 0, 23, 2, -1, 1, .25, "Graph Title", "x", "y", GSLC_COL_GRAY_DK3, GSLC_COL_GRAY_DK2, GSLC_COL_BLUE_LT4, GSLC_COL_WHITE, GSLC_COL_BLACK, redrawGraph);
   // Graph(x, y, 60, 290, 390, 260, 0, 6.5, 1, -1, 1, .25, "Sin Function", "x", "sin(x)", GSLC_COL_BLUE_LT1, GSLC_COL_RED_LT1, GSLC_COL_YELLOW, GSLC_COL_WHITE, GSLC_COL_BLACK, display1);
    }

  }
    

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

  if (tempC < tempLo) tempLo = tempC; // TODO: Clear all lo/hi values every 24hours. (or at 12:00AM everyday)
  if (tempC > tempHi) tempHi = tempC;
  
  if (gslc_ElemXTogglebtnGetState(&m_gui, tempUnitToggle))
  { // display temp in F
    updateGauge(tempGauge, tempLoHiTxt, tempSensor.toFahrenheit(tempC), tempSensor.toFahrenheit(tempLo), tempSensor.toFahrenheit(tempHi));
  } else 
  { // display temp in C
    updateGauge(tempGauge, tempLoHiTxt, tempC, tempLo, tempHi);
  }


  // * TDS
  getTDSVal(); // Updates 'tdsValue' variable
  if (tdsValue < tdsLo && tdsValue >= 0) tdsLo = tdsValue;
  if (tdsValue > tdsHi) tdsHi = tdsValue;
  
  if (tdsValue <= 0) updateGauge(tdsGauge, tdsLoHiTxt, -1, tdsLo, tdsHi);
  else updateGauge(tdsGauge, tdsLoHiTxt, tdsValue, tdsLo, tdsHi);
  


  // * pH
  // TODO: implement pH update function & display results on screen
  updateGauge(phGauge, phLoHiTxt, 23, 20, 24);
  

}

/**
 * @brief Initial setup for the device.
 * 
 */
void initSetup()
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
	gslc_ElemSetTxtStr(&m_gui, tempUnitTxt, (char*)"\xf7""F");
  gslc_ElemSetTxtStr(&m_gui, settingsTempUnitTxt, (char*)"\xf7""F");

  testSensors();

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
 */
void updateGauge(gslc_tsElemRef *pElemRef, gslc_tsElemRef *pSubElemRef, int n, int lo, int hi)
{
	char nStr[25], loHi[25];
	sprintf(nStr, "%d", n);
	sprintf(loHi, "%c%d %c%d", 25, lo, 24, hi);

	gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, n);
	gslc_ElemSetTxtStr(&m_gui, pElemRef, nStr);
	gslc_ElemSetTxtStr(&m_gui, pSubElemRef, loHi);

  if (n <= 0) gslc_ElemSetTxtStr(&m_gui, pElemRef, "-");
}


/**
 * Heater element function
 * 
 */
void controlHeater(int temperature, int userTemp)
{
	int lowerLimit = userTemp -2;
	int upperLimit = userTemp +2;
		// Set pin to HIGH to turn on - Set pin to LOW to turn off
	if (upperLimit > 26.66)
	{
    // Turn heater off
		digitalWrite(RELAY_PIN, LOW);
		//alert the user
		//display visual alarm   *maybe make a function for alarms, either together or seperate
		//initiate speaker alarm
	}
	if (temperature <= lowerLimit)
	{
    // Turn heater on
		digitalWrite(RELAY_PIN, HIGH);
	}
	if (temperature >= upperLimit)
	{
    // Turn heater off
		digitalWrite(RELAY_PIN, LOW);
	}
	if (temperature < 18.33)
	{
    // Turn heater on
		digitalWrite(RELAY_PIN, HIGH);
		//alert user
		//display visual alarm
		//initiate speaker alarm
	}
}


/**
 * @brief Handles switching between temperature units
 * 
 */
void handleTempUnitToggle()
{
  if (gslc_ElemXTogglebtnGetState(&m_gui, tempUnitToggle))
  { // use F
    gslc_ElemSetTxtStr(&m_gui, tempUnitTxt, (char *)"\xf7""F");
    gslc_ElemSetTxtStr(&m_gui, settingsTempUnitTxt, (char *)"\xf7""F");
  }
  else
  { // use C
    gslc_ElemSetTxtStr(&m_gui, tempUnitTxt, (char *)"\xf7""C");
    gslc_ElemSetTxtStr(&m_gui, settingsTempUnitTxt, (char *)"\xf7""C");
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
  WiFi.begin(ssid, pwd);
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
 * @param title: title of graph
 * @param xlabel: x asis label
 * @param ylabel: y asis label
 * @param gcolor: graph line colors
 * @param acolor: axi ine colors
 * @param pcolor: color of your plotted data
 * @param tcolor: text color
 * @param bcolor: background color
 * @param redraw: flag to redraw graph on fist call only
 */
void Graph(double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, char* title, char* xlabel, char* ylabel, gslc_tsColor gcolor, gslc_tsColor acolor, gslc_tsColor pcolor, gslc_tsColor tcolor, gslc_tsColor bcolor, boolean &redraw) {

  // double ydiv, xdiv;
  double i;
  double temp;
  static char bufstr[15];

  if (redraw == true) {

    redraw = false;
    // initialize old x and old y in order to draw the first point of the graph
    // but save the transformed value
    // note my transform funcition is the same as the map function, except the map uses long and we need doubles
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
      // d.setTextSize(1);
      // d.setTextColor(tcolor, bcolor);
      // gslc_ElemSetTxtCol(&m_gui, )
      // d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      // d.println(i);
	    sprintf(bufstr, "%.2lf", i);
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
      // draw the axis labels
      // d.setTextSize(1);
      // d.setTextColor(tcolor, bcolor);
      // d.setCursor(temp, gy + 10);
      // // precision is default Arduino--this could really use some format control
      // d.println(i);
      sprintf(bufstr, "%.0lf", i);
      gslc_DrawTxtBase(&m_gui, bufstr, (gslc_tsRect){temp, gy + 10,30,10}, &m_asFont[E_BUILTIN5X8], GSLC_TXT_ALLOC_INT, GSLC_ALIGN_TOP_LEFT, tcolor, bcolor, 0, 0);
    }

    //now draw the graph labels
    // d.setTextSize(2);
    // d.setTextColor(tcolor, bcolor);
    // d.setCursor(gx , gy - h - 30);
    // d.println(title);
    // sprintf(bufStr, "%s", title);
    // pElemRef = gslc_ElemCreateTxt(&m_gui, GSLC_ID_AUTO, E_PG_SUM, (gslc_tsRect){gx, gy - h - 30, 250,18}, title, 50, E_BUILTIN5X8);
    gslc_DrawTxtBase(&m_gui, title, (gslc_tsRect){gx, gy - h - 30, 250,18}, &m_asFont[E_BUILTIN5X8], GSLC_TXT_ALLOC_INT, GSLC_ALIGN_MID_MID, tcolor, bcolor, 0, 0);

    // d.setTextSize(1);
    // d.setTextColor(acolor, bcolor);
    // d.setCursor(gx , gy + 20);
    // d.println(xlabel);
    gslc_DrawTxtBase(&m_gui, xlabel, (gslc_tsRect){gx, gy + 20, 100,10}, &m_asFont[E_BUILTIN5X8], GSLC_TXT_ALLOC_INT, GSLC_ALIGN_MID_LEFT, tcolor, bcolor, 0, 0);

    // d.setTextSize(1);
    // d.setTextColor(acolor, bcolor);
    // d.setCursor(gx - 30, gy - h - 10);
    // d.println(ylabel);
    gslc_DrawTxtBase(&m_gui, ylabel, (gslc_tsRect){gx - 30, gy - h - 10, 100,10}, &m_asFont[E_BUILTIN5X8], GSLC_TXT_ALLOC_INT, GSLC_ALIGN_MID_LEFT, tcolor, bcolor, 0, 0);

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
    delay(10);
  }
  

}
