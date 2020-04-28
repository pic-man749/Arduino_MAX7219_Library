# Arduino_MAX7219_Library

Arduino library for MAX7219 Dot Matrix Module 4 in 1 Display.

This library aims to control Dot Matrix Display using MAX7219 module like Processing.

You can use more than 4 Dot Matrix Module(Up to 255 * 255 or as far as memory permits).

Furthermore, you can freely decide the arrangement of modules.
For example, if you have 4 Dot Matrix module, any of these arrangements can be used : 1 * 4, 2 * 2, 4 * 1.

Hardware example:

* [MAX7219 Dot Matrix Module 4 in One Display - COLORMIX](https://www.gearbest.com/other-accessories/pp_1257191.html?wid=1433363)
* [ＭＡＸ７２１９使用赤色ドットマトリクスＬＥＤモジュール](http://akizukidenshi.com/catalog/g/gM-09984/)

An explanation in Japanese is [here](https://picman.dev/blog/2018/11/30/max7219%e3%82%92%e4%bd%bf%e3%81%a3%e3%81%9f8x8%e3%83%89%e3%83%83%e3%83%88%e3%83%9e%e3%83%88%e3%83%aa%e3%83%83%e3%82%af%e3%82%b9%e3%81%aearduino%e3%83%a9%e3%82%a4%e3%83%96%e3%83%a9%e3%83%aa/).

## Sample code

``` C++:basic.ino
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

  // turn off all LEDs
  dm.allOff();
}

```
For more information about method, please refer to [Wiki](https://github.com/pic-man749/Arduino_MAX7219_Library/wiki/Welcome-to-the-Arduino_MAX7219_Library-wiki!).

