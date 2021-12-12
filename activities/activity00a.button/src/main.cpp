#include <Arduino.h>
#include <wpi-32u4-lib.h>

// declare the pin for the LED
const int LED_PIN = 13;

// Create a button object for the built-in Button A on the Romi
Romi32U4ButtonA buttonA;

// Define two basic states. For this program, they will correspond to an LED state (on or off).
// "enum" stands for "enumerate". Basically, we define a new variable type called ROBOT_STATE.
// We prepend "ROBOT_" to avoid conflicts with other macros that may be defined elsewhere.
enum ROBOT_STATE {ROBOT_IDLE, ROBOT_ACTIVE};

// Declare a variable, robotState, of our new type, ROBOT_STATE. Initialize it to ROBOT_IDLE.
ROBOT_STATE robotState = ROBOT_IDLE;

int count = 0;

void handleButtonPress(void)
{
  // Go through the state machine
  if(robotState == ROBOT_IDLE)
  {
      // Notify us that we're switching to ACTIVE
      Serial.print("Button press -> ACTIVE: ");
      Serial.println(++count);

      // TODO: Turn the LED on
      digitalWrite(LED_PIN, HIGH);

      // Finally, update the state
      robotState = ROBOT_ACTIVE;
  }

  //note that we use else..if for each additional state, so it doesn't get confused
  else if(robotState == ROBOT_ACTIVE)
  {
      // Notify us that we're switching to IDLE
      Serial.println("Button press -> IDLE");

      // TODO: Turn the LED off
      digitalWrite(LED_PIN, LOW);

      // Finally, update the state
      robotState = ROBOT_IDLE;
  }
}

/*
 * This is the standard setup function that is called when the Romi is rebooted.
 * It is used to initialize anything that needs to be done once.
 */
void setup() 
{
  // This will initialize the Serial at a baud rate of 115200 for prints
  // Be sure to set your Serial Monitor appropriately in platformio.ini
  Serial.begin(115200);

  // TODO: Set the LED pin to be an OUTPUT
  pinMode(LED_PIN, OUTPUT);
}

/* Here is where all the fun happens. For each state, check for and respond to a button press.
 */ 
void loop()
{
  if(buttonA.getSingleDebouncedPress()) handleButtonPress();
}