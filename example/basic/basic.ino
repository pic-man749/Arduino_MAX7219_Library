/*
 * Basic usage of MAX7219_DotMatrix by PIC MAN
 *
 * Circuit:
 *   Arduino      MAX7219
 *     5V  -------- VCC
 *     GND -------- GND
 *     11  -------- DIN
 *     10  -------- CS
 *     13  -------- CLK
 *
 * This example use 1*4 Dot Matrix. The coordinates are...
 *   ─────┐        ┌────────┬───   ...   ───┐
 *           5V│ --> VCC│(0,0)      (7,0)│(8,0)          (31,0)│
 *          GND│ --> GND│                │                     │
 *  Arduino  11│ --> DIN│       1        │     2   ...   4     │
 *           10│ --> CS │                │                     │
 *           13│ --> CLK│(0,7)      (7,7)│(8,7)          (31,7)│
 *   ─────┘        └────────┴───   ...     ──┘
 *
 * created at 2018-11-18
 */

#include<MAX7219_DotMatrix.h>

#define MATRIX_ROW 1
#define MATRIX_COL 4
#define MATRIX_DOT 8

// create instance, args:(row, column)
MAX7219_DotMatrix dm = MAX7219_DotMatrix(MATRIX_ROW, MATRIX_COL);

void setup() {

  // initialize method, you must call.
  dm.begin();

}

void loop() {

  for(int i=0; i<MATRIX_DOT*MATRIX_ROW; i+=1){
    for(int j=0; j<MATRIX_DOT*MATRIX_COL; j+=1 ){
      dm.point(j, i); // draw a dot at(j, i)
      dm.draw();      // draw. No change is made to the LED until this method is called.
      delay(100);
    }
  }

  // All LEDs turn off
  dm.allOff();
}
