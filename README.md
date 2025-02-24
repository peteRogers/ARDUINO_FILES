# ARDUINO_FILES
### Bounce code
```Arduino

#include <Bounce2.h>
bool ledState = false; //state of LED on or off
Bounce bounceA = Bounce();

void setup() {
  pinMode(13, OUTPUT);
  //create bounce button
  bounceA.attach(8, INPUT_PULLUP ); 
  bounceA.interval(2); 
}//end setup

void loop() {
  bounceA.update();
  if(bounceA.fell()){
    ledState = !ledState;
  }
  digitalWrite(13, ledState);
}//end loop

```