# Arduino_MAX7219_Library

Arduino library for MAX7219 Dot Matrix Module 4 in 1 Display.

This library aims to control Dot Matrix Display using MAX7219 module like Processing.

You can use more than 4 Dot Matrix Module(Up to 255 * 255 or as far as memory permits).

Furthermore, you can freely decide the arrangement of modules.
For example, if you have 4 Dot Matrix module, any of these arrangements can be used : 1 * 4, 2 * 2, 4 * 1.

Hardware example:

* [MAX7219 Dot Matrix Module 4 in One Display - COLORMIX](https://www.gearbest.com/other-accessories/pp_1257191.html?wid=1433363)
* [ＭＡＸ７２１９使用赤色ドットマトリクスＬＥＤモジュール](http://akizukidenshi.com/catalog/g/gM-09984/)

**This is a beta version. Several methods are not yet implemented**

## Sample code:basic.ino

``` C++
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
      dm.point(j, i); // draw a dot at(i, j)
      dm.draw();      // draw. No change is made to the LED until this method is called.
      delay(100);
    }
  }

  // All LEDs turn off
  dm.allOff();
}

```

**Only implemented these methods now**

* point()
* allOn()
* allOff()
* setDrawMode()
* toggle()
* draw()
* setBrightness()
