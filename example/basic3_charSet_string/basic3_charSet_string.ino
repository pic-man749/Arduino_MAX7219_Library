/*
 * Basic usage of MAX7219_DotMatrix_charSet by PIC MAN
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
 * How to control
 *    1. Open Serial console with Arduino(BaudRate = 9600)
 *    2. type 'return'    -> show next character
 *    3. type 'backSpace' -> show previous character
 * 
 * created at 2018-12-02
 */

// if you want to use ASCII characters, include this header
#include <MAX7219_DotMatrix_charSet.h>

#define MATRIX_ROW 1
#define MATRIX_COL 4

// create instance, args:(row, column)
MAX7219_DotMatrix_charSet dm = MAX7219_DotMatrix_charSet(MATRIX_ROW, MATRIX_COL);

void setup() {

  Serial.begin(9600);

  // initialize method, you must call.
  dm.begin();
}

void loop() {

  // printStr method upport a-Z ONLY now.

  // return to point (x,y) = (0,0)
  dm.setCursor(0,0);
  dm.printStr("foobar");
  dm.draw();
  delay(1000);

  dm.setCursor(0,0);
  dm.printStr("FOOBAR");
  dm.draw();
  delay(1000);

}
