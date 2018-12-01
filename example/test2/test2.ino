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
 *         *  ┌────────┬───   ...   ───┐
 *         ---│(0,0)      (7,0)│(8,0)          (31,0)│
 *         ---│                │                     │
 * Arduino ---│       1        │     2   ...   4     │
 *         ---│                │                     │
 *         ---│(0,7)      (7,7)│(8,7)          (31,7)│
 *         *  └────────┴───   ...     ──┘
 *
 * created at 2018-11-18
 */

#include<MAX7219_DotMatrix_charSet.h>

#define MATRIX_ROW 1
#define MATRIX_COL 4
#define MATRIX_DOT 8

// create instance, args:(row, column)
MAX7219_DotMatrix_charSet dm = MAX7219_DotMatrix_charSet(MATRIX_ROW, MATRIX_COL);

void setup() {

  // initialize method, you must call.
  Serial.begin(115200);
  Serial.println("init start");
  dm.begin();
  Serial.println("init end");

}

void loop() {

  Serial.println("loop");

  dm.setCharDirect(0, 0, 0);
  dm.draw();

  while(1) ;
  
}
