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
  Serial.begin(9600);
  Serial.println("init start");
  dm.begin();
  Serial.println("init end");

//  dm.setDrawMode(false);
//  dm.allOn();
  //dm.setScrollSpeed(10);

  String tmp = "AORUNA KASU";
  dm.setScrollStr(tmp);
  dm.setBlink(true);

  String a = "ｱ";
  char c = a.charAt(0);
  Serial.print("c = ");
  Serial.print(c);
  Serial.print(", c[BIN]");
  Serial.print(c, BIN);
  Serial.print(", 'ｱ' == 0b10110001");
  Serial.print(c == 0b10110001);
  Serial.print(", c[uint32_t]");
  Serial.println((uint32_t)c, BIN);

}
float fps = 0.0;

void loop() {
  
//  static uint8_t i = 0;
//
//  if (Serial.available() > 0) {
//
//    char c = Serial.read();
//    if(c == '\r'){
//      i++;
//    }else if(c == '\b'){
//      i--;
//    }
//    if(i >= dm.SIZE_OF_CHARSET) i = 0;
//    Serial.print("i = ");
//    Serial.println(i);
//    if(i%5 == 0){
//      dm.allOff();
//      dm.setCursor(0, 0);
//    }
//    dm.printCharDirect(i);
//    dm.draw();
//  }
 

//  for(int i = 0; i < 255; i++){
//    uint64_t c = 'ｱ';
//    Serial.print(char(c+i));
//    Serial.print(" is ");
//    Serial.println(c+i, BIN);
//  }


  dm.draw();
//  fps++;
//  if(millis() > 10000){
//    Serial.print("framerate = ");
//    Serial.print(fps / millis() * 1000.0);
//    while(1) ;
//  }
  
}
