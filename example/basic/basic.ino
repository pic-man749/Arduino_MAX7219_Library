/*
 * Basic usage of MAX7219_DotMatrix by PIC MAN
 *
 * Circuit:
 *   Arduino      MAX7219
 *     5V  -------- VCC
 *     GND -------- GND
 *     DIN -------- 11
 *     CS  -------- 10
 *     CLK -------- 13
 *
 * This example use 1*4 Dot Matrix. The coordinates are...
 *  ┌────────┬───   ...   ───┐
 *  │(0,0)      (7,0)│(8,0)          (31,0)│
 *  │                │                     │
 *  │       1        │     2   ...   4     │
 *  │                │                     │
 *  │(0,7)      (7,7)│(8,7)          (31,7)│
 *  └────────┴───   ...     ──┘
 *
 * created 18 November 2018
 */

#include<MAX7219_DotMatrix.h>

// create instance, arg:(row, column)
MAX7219_DotMatrix dm = MAX7219_DotMatrix(1, 4);

void setup() {

  // initialize method, you must call.
  dm.begin();

}

void loop() {

  for(int i=0; i<8; i+=1){
    for(int j=0; j<8*4; j+=1 ){
      dm.point(j, i); // draw a dot at(j, i)
      dm.draw();      // draw. No change is made to the LED until this method is called.
      delay(100);
    }
  }

  // All LEDs turn off
  dm.allOff();
}
