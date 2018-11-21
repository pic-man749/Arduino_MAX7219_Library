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
 *  │(0,0)      (7,0)│(8,0)          (31,0)│---
 *  │                │                     │---
 *  │       1        │     2   ...   4     │--- Arduino 
 *  │                │                     │---
 *  │(0,7)      (7,7)│(8,7)          (31,7)│---
 *  └────────┴───   ...     ──┘
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
  Serial.begin(9600);
  Serial.println("init start");
  dm.begin();
  Serial.println("init end");

}

void loop() {

  Serial.println("loop");
  dm.line(0,0,7,7);
  dm.triangle(12,0,8,7,15,8);
  dm.rect(17, 1, 6, 6);
  dm.quad(24, 0, 24, 6, 30, 6, 30, 1);
  dm.draw();
  delay(3000);
  dm.allOff();
}
