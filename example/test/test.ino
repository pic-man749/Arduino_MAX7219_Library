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
  Serial.begin(115200);
  Serial.println("init start");
  dm.begin();
  Serial.println("init end");

}

void loop() {

  Serial.println("loop");
//  dm.line(0,0,23,0);
//  dm.line(0,0,0,7);
//  dm.line(31,7,24,0);
//  dm.line(31,0,24,7);
//  dm.line(5,3,5,7);
//  dm.line(0,3,7,3);
//  dm.triangle(12,0,8,7,15,8);
//  dm.rect(17, 1, 6, 6);
//  dm.quad(24, 1, 24, 6, 30, 6, 30, 1);

//  dm.ellipse(25,3,2,2);
//
//  dm.ellipse(8,7,16,16);
  
//  bool hoge = dm.triangle(16,0,16,7,23,4);
//  dm.fill();
//  hoge = dm.triangle(0,0,0,7,7,4);
//  
//  Serial.print("lp end, ");
//  Serial.println(hoge);
  dm.allOn();
  dm.setDrawMode(false);
  dm.fill();
  dm.quad(0,0, 0,8, 8,8, 8,0);
  dm.noFill();
  dm.quad(16,0, 23,7, 16,7, 23,0);

  dm.draw();

  for(int i=0; i<8; i++){
    for(int j=0; j<32; j++) Serial.print(dm.getPoint(j,i));
    Serial.println();
  }

  int matrix_byte = 16;
  bool draw_mode = 1;
  uint8_t* matrix_tmp = (uint8_t *)calloc(matrix_byte, sizeof(uint8_t));
  if (matrix_tmp == NULL) return false;    // if it could not reserve memory
  //memset(matrix_tmp, (draw_mode)? 0b11111111 : 0b00000000, matrix_byte);
  if(draw_mode) memset(matrix_tmp, 0b11111111, matrix_byte);
  else if(draw_mode) memset(matrix_tmp, 0b00000000, matrix_byte);
  Serial.print("InLoop:");
  Serial.print(dm.getPoint(1,1,matrix_tmp));
  free(matrix_tmp);

  while(1) ;
  
}
