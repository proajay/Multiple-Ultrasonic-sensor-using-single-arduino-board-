
#include <NewPing.h>

#define SONAR_NUM     5 // Number of sensors.
#define MAX_DISTANCE 100 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 35 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).
int dis =80;
//initialize LESs state to LOW
int led1State = LOW;
int led2State = LOW;
int led3State = LOW;
int led4State = LOW;
int led5State = LOW;
int period = 15000; //led ON time  
unsigned long time_now = 0;

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.
unsigned int  sensors[SONAR_NUM];

NewPing sonar[SONAR_NUM] = {     // Sensor object array.

  NewPing(8, 8, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(9, 9, MAX_DISTANCE),
  NewPing(10, 10, MAX_DISTANCE),
  NewPing(11, 11, MAX_DISTANCE),
NewPing(12, 12, MAX_DISTANCE),

};


void setup() {

DDRD |=B11111000;

  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) 
      
      oneSensorCycle(); // Sensor ping cycle complete, do something with the results.
      led (); //Turn ON the LEDs according to State.

    
    if((millis() >= time_now + period) && (led1State == HIGH || led2State == HIGH || led3State == HIGH || led4State == HIGH || led5State == HIGH ) ){//15s delay using millis function and it only starts when any one LED is ON.
        time_now = millis();

        /*after 15s set, all LEDs state to LOW.*/
        led1State = LOW;
        led2State = LOW;
        led3State = LOW;
        led4State = LOW;
        led5State = LOW;
         
    }
    
      
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    
    }
  }
  
}

void echoCheck() 
{ // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.

/*Store sensor data in Array*/
  for (uint8_t i = 0; i < SONAR_NUM; i++) 
  {
    sensors[i] = cm[i];
   }

/*LED Logic Start Using if Statemet*/
if (sensors[0] > 0 && sensors[0] <= dis)
{
led1State = HIGH;

  }
if (sensors[1] > 0 && sensors[1] <= dis)
{

led2State = HIGH;
  }
if (sensors[2] > 0 && sensors[2] <= dis)
{
 led3State = HIGH;
  }
if (sensors[3] > 0 && sensors[3] <= dis)
{
 led4State = HIGH;  
 }
if (sensors[4] > 0 && sensors[4] <= dis)
{
 led5State = HIGH;  
 }
if ((sensors[0] > 0 && sensors[0] <= dis) && (sensors[1] > 0 && sensors[1] <= dis))
{
led1State = HIGH;
led2State = HIGH;
  }
if ((sensors[1] > 0 && sensors[1] <= dis) && (sensors[2] > 0 && sensors[2] <= dis))
{
 led2State = HIGH;
 led3State = HIGH;
  }
if ((sensors[2] > 0 && sensors[2] <= dis) && (sensors[3] > 0 && sensors[3] <= dis))
{
  led3State = HIGH;
  led4State = HIGH;
   }
if ((sensors[3] > 0 && sensors[3] <= dis) && (sensors[4] > 0 && sensors[4] <= dis))
{
  led4State = HIGH;
  led5State = HIGH;
  }
if ((sensors[4] > 0 && sensors[4] <= dis) && (sensors[0] > 0 && sensors[0] <= dis))
{
  led1State = HIGH;
  led5State = HIGH;
  }
}
void led() //LED Write Function 
{

digitalWrite(3,led1State);
digitalWrite(4,led2State);
digitalWrite(5,led3State);
digitalWrite(6,led4State);
digitalWrite(7,led5State);

  }
