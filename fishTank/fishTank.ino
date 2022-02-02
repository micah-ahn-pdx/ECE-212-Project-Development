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

// * 
#define RELAY_PIN   13	  	// Relay pin
#define TEMP_SENSOR 4			  // Temp sensor pin
#define TDS_SENSOR  39			// TDS Sensor pin

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

Gravity_pH pH = Gravity_pH(A2);   // pH sensor pin assign

// * Starting Variables
// loop update variable
unsigned long loopTime = 0L;

// WiFi Setup
const char* ssid = "01001101";
const char* pwd = "0x01001101";

// Getting Time
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -28800;   // GMT offset (seconds)
const int   daylightOffset_sec = 3600;  // daylight offset (seconds)
struct tm timeinfo;
int curHr = -1, prevHr = -1;

// Temp
OneWire oneWire(TEMP_SENSOR);
DallasTemperature tempSensor(&oneWire);
float tempC = 0, tempLo = 999, tempHi = -999; // Where to store current temperature

// TDS
int analogBuffer[SCOUNT]; 			// store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, tdsLo = 999, tdsHi = -999;

// pH
uint8_t user_bytes_received = 0;                
const uint8_t bufferlen = 32;                   
char user_data[bufferlen]; 

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

logNode dataLog; // Initiate dataLog where we'll store the past 24hrs readings



// **************** BELOW IS GENERATED AUTOMATICALLY BY THE GUISLICE BUILDER **************** //
// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* btnOther          = NULL;
gslc_tsElemRef* btnSettings       = NULL;
gslc_tsElemRef* btnSummary        = NULL;
gslc_tsElemRef* clockTxt          = NULL;
gslc_tsElemRef* desiredTemp       = NULL;
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
        handleGraphUpdate();
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
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
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
  Serial.begin(void parse_cmd(char* string) {                   
  strupr(string);                                
  if (strcmp(string, "CAL,7") == 0) {       
    pH.cal_mid();                                
    Serial.println("MID CALIBRATED");
  }
  else if (strcmp(string, "CAL,4") == 0) {            
    pH.cal_low();                                
    Serial.println("LOW CALIBRATED");
  }
  else if (strcmp(string, "CAL,10") == 0) {      
    pH.cal_high();                               
    Serial.println("HIGH CALIBRATED");
  }
  else if (strcmp(string, "CAL,CLEAR") == 0) { 
    pH.cal_clear();                              
    Serial.println("CALIBRATION CLEARED");
  }
}

void calibrate() {
  Serial.begin(115200);                            
  delay(200);
  Serial.println(F("Use commands \"CAL,7\", \"CAL,4\", and \"CAL,10\" to calibrate the circuit to those respective values"));
  Serial.println(F("Use command \"CAL,CLEAR\" to clear the calibration"));
  if (pH.begin()) {                                     
    Serial.println("Loaded EEPROM");
  }
}

void loop() {
  if (Serial.available() > 0) {                                                      
    user_bytes_received = Serial.readBytesUntil(13, user_data, sizeof(user_data));   
  }

  if (user_bytes_received) {                                                      
    parse_cmd(user_data);                                                          
    user_bytes_received = 0;                                                        
    memset(user_data, 0, sizeof(user_data));                                         
  }
  
  Serial.println(pH.read_ph());                                                      
  delay(1000);
});

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
  dataLog.startIndex = timeinfo.tm_min%24; // Get the current hour (when the device is first turned on)

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
	strftime(clock, 26, "%I:%M:%S%p %m/%d/%y", &timeinfo); // Format time
	gslc_ElemSetTxtStr(&m_gui, clockTxt, clock);				 // Update sreen text		

	gslc_Update(&m_gui); // Periodically call GUIslice update function

  logData(); // Logs data every 1hr

  // Draws the graph when the user is in the summary page
  handleGraphUpdate();
    

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
    gslc_DrawFillRect(&m_gui, (gslc_tsRect){gx,gy-h,w+10,h+20}, bcolor);

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

  if (curHr != prevHr) // Update what's inside every 1 hour.
	{
		// Log the temperature value
    // dataLog.tempVal[curHr] = tempC;
    // TODO: Log TDS & pH values

    dataLog.curIndex = curHr; // Update the log current index to the current hour

    if ((dataLog.curIndex+1)%24 == dataLog.startIndex) dataLog.isFull = true; // Mark the log full recording the first 24hr worth of data

    if (curHr == 0)
    {
      // Reset lo/hi values every day at 12AM
      tempLo = tdsLo = 999;
      tempHi = tdsHi = -999; 
    }
    
    redrawGraph = true;
		prevHr = curHr;
	}
}


void handleGraphUpdate() {
  if (gslc_GetPageCur(&m_gui) == E_PG_SUM) { // Only draw/update if the user is in the summary page

    double gx = 40, gy = 220, gw = 420, gh = 180;    
    int x, y; // needed variables for the plot
    int iCap = (dataLog.isFull) ? 23 : dataLog.curIndex - dataLog.startIndex; // How many x data to plot is determined by how many hours passed if the log isn't full yet, and if it's full it's always 24(with the 0).
    gslc_tsElemRef* pElemRef = NULL; // pointer reference to elements

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
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "Temperature Summary");
        // Highlight selected tab/btn
        if (redrawGraph) {
          gslc_ElemSetCol(&m_gui, tempSumBtn,GSLC_COL_WHITE,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT3);
          gslc_ElemSetCol(&m_gui, tdsSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
          gslc_ElemSetCol(&m_gui, phSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
        }
        
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
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "TDS Summary");
        // Highlight selected tab/btn
        if (redrawGraph) {
          gslc_ElemSetCol(&m_gui, tdsSumBtn,GSLC_COL_WHITE,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT3);
          gslc_ElemSetCol(&m_gui, tempSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
          gslc_ElemSetCol(&m_gui, phSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
        }
        // TODO graph TDS
      }
      else
      {
        gslc_ElemSetTxtStr(&m_gui, statusbarText, "pH Summary");
        // Highlight selected tab/btn
        if (redrawGraph) {
          gslc_ElemSetCol(&m_gui, phSumBtn,GSLC_COL_WHITE,GSLC_COL_BLUE_LT3,GSLC_COL_BLUE_LT3);
          gslc_ElemSetCol(&m_gui, tdsSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
          gslc_ElemSetCol(&m_gui, tempSumBtn,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT4,GSLC_COL_BLUE_LT3);
        }
        // TODO graph pH
      }
      

    }

  }
}

void parse_cmd(char* string) {                   
  strupr(string);                                
  if (strcmp(string, "CAL,7") == 0) {       
    pH.cal_mid();                                
    Serial.println("MID CALIBRATED");
  }
  else if (strcmp(string, "CAL,4") == 0) {            
    pH.cal_low();                                
    Serial.println("LOW CALIBRATED");
  }
  else if (strcmp(string, "CAL,10") == 0) {      
    pH.cal_high();                               
    Serial.println("HIGH CALIBRATED");
  }
  else if (strcmp(string, "CAL,CLEAR") == 0) { 
    pH.cal_clear();                              
    Serial.println("CALIBRATION CLEARED");
  }
}

void calibrate() {
  Serial.begin(115200);                            
  delay(200);
  Serial.println(F("Use commands \"CAL,7\", \"CAL,4\", and \"CAL,10\" to calibrate the circuit to those respective values"));
  Serial.println(F("Use command \"CAL,CLEAR\" to clear the calibration"));
  if (pH.begin()) {                                     
    Serial.println("Loaded EEPROM");
  }
}

void get_pH() {
  if (Serial.available() > 0) {                                                      
    user_bytes_received = Serial.readBytesUntil(13, user_data, sizeof(user_data));   
  }

  if (user_bytes_received) {                                                      
    parse_cmd(user_data);                                                          
    user_bytes_received = 0;                                                        
    memset(user_data, 0, sizeof(user_data));                                         
  }
  
  Serial.println(pH.read_ph());                                                      
  delay(1000);
}
