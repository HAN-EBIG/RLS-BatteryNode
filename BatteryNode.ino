/// EBIG MySensors battery level sketch
/// This sketch will only work with 1MΩ (R1) and 470KΩ (R2) resistor in series 
/// Version 1.0
/// This sketch can be used for a SensorNode and will sent the current battery level

/// _________________________________________-- Only configure this part of the sketch -- ______________________________________________ ///

/// The time a node will sleep for sending its next message
#define SLEEP_TIME 3000  

/// Node ID of the sensornode
#define MY_NODE_ID 50     

const float   INPUT_VOLTAGE_MC = 5.0; /// Usually 5v for Arduino mega, uno and nano; 3(.3)v for arduino mini/nano
int     BATTERY_SENSE_PIN = A0; /// The analog port that gets the voltage
const uint8_t BATTERY_OUTPUT_VOLTAGE  = 9; /// Typically a 9 volt battery will be used to power the Sensor node
const float   PERCENTAGE_TOP_MARGE = 110;
const float   PERCENTAGE_MIN_MARGE = 0.5;

/// _________________________________________--         End of configuration          -- ______________________________________________ ///

#define MY_RADIO_NRF24 /// Enable and select radio type attached
#include <MySensors.h> /// MySensors Sensornode



float batteryPercentage = 0;

void setup() 
{
  Serial.begin(115200);
}

void presentation()
{
    // Send the sketch version information to the gateway and Controller
    sendSketchInfo("Battery Meter", "1.0");
}

void loop() 
{
  int16_t sensorValue = analogRead(BATTERY_SENSE_PIN);
  float voltage = sensorValue * calculateVoltsPerBit();
  batteryPercentage = calculateBatteryPercentage(voltage);
  
  if (sanityCheck(batteryPercentage) == true)
  {
    sendBatteryLevel(batteryPercentage);
  }
  sleep(SLEEP_TIME);
}

float calculateVoltsPerBit()
{ 
  float vMax = 3.1276595744680851063829787234043; //((1e6+470e3)/470e3)
  float newVMax = vMax * INPUT_VOLTAGE_MC;
  float voltageBit = newVMax/1023;
  
  return voltageBit;
}

float calculateBatteryPercentage(float voltage)
{
  return (voltage/BATTERY_OUTPUT_VOLTAGE*100);
}

bool sanityCheck(float percentage)
{
  if (percentage > 100.0 && percentage < PERCENTAGE_TOP_MARGE)
  {
    batteryPercentage = 100.0;
    return true;
  }
    if (percentage > PERCENTAGE_TOP_MARGE || percentage < PERCENTAGE_MIN_MARGE)
  {
    return false;
  }
  return true;
}

