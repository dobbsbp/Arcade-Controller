/*  This file has been modified by Ben Dobbs. If you're interested in the
original file, please take a look at examples from the Arduino IDE
File --> Examples --> Keypad --> MultiKey

What's different from the original Multikey program?

The original MultiKey program would only send messages of what buttons were
being pressed via serial monitor, not actually send commands telling your
computer via USB that a button has been pressed.

Limitations?

10 keys can be pressed at the same time.
*/

#include <Keypad.h>
#include <Keyboard.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};            // These keys can be replaced with whatever key you'd like.
              // For ones you can't type like up arrow, please visit
              // https://www.arduino.cc/en/Reference/KeyboardModifiers
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {14, 16, 10}; //connect to the column pinouts of the kpd

// You can create a larger grid, just be sure to update the ROWS and COLS values
// and also what pinouts you're using above.

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;


void setup() {
    Serial.begin(9600);  // Useful for debuging, otherwise not neccisary.
    kpd.setDebounceTime(10); // Default 10. If number is too high, there will be lag.
    loopCount = 0;
    startTime = millis();
    msg = "";
    Keyboard.begin(); // Begin up Keyboard emulation
    }


void loop() {

    loopCount++;
    if ( (millis()-startTime)>5000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                    Keyboard.press(kpd.key[i].kchar); // Send keyboard press
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                    Keyboard.release(kpd.key[i].kchar); // Send keyboard release
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.println(msg);

            }
        }
    }
}  // End loop
