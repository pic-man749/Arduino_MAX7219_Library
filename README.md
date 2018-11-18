# Arduino_MAX7219_Library

Arduino library for MAX7219 Dot Matrix Module 4 in 1 Display.

This library aims to control Dot Matrix Display using MAX7219 module like Processing.

Hardware example:

* [MAX7219 Dot Matrix Module 4 in One Display - COLORMIX](https://www.gearbest.com/other-accessories/pp_1257191.html?wid=1433363)
* [ＭＡＸ７２１９使用赤色ドットマトリクスＬＥＤモジュール](http://akizukidenshi.com/catalog/g/gM-09984/)

###

## Support function

**Only implemented these functions now**
* point()
* allOn()
* allOff()
* setDrawMode()
* toggle()
* draw()

***

### Draw functions

* point(x, y)
* line(x1, y1, x2, y2)
* triangle(x1, y1, x2, y2, x3, y3)
* rect(x, y, w, h)
* quad(x1, y1, x2, y2, x3, y3, x4, y4)
* ellipse(x, y, w, h)
* fill()
    * only support LED status "ON" or "OFF"
* noFill()

### Coordinate manipulation functions

* translate(x, y)
* resetMatrix()

### Original functions

* allOn()
* allOff()
* setDrawMode(mode)
* draw()
* toggle(x, y)
* getPoint(x, y)

`allOn()` and `allOff()` functions works literally.

`setDrawMode()` specifies the lighting state of the LED when "Draw functions" are called. Default status of `setDrawMode()` is `true`. `setDrawMode()` needs to be called before calling "Draw functions". For example:

``` C++
dotMatrix.setDrawMode(true);
dotMatrix.point(0, 0);
dotMatrix.draw();
// -> point (0, 0) LED will turn ON

dotMatrix.setDrawMode(false);
dotMatrix.point(0, 0);
dotMatrix.draw();
// -> point (0, 0) LED will turn OFF


```

`draw()` function transfer data to MAX7219. So, you must call `draw()` if you want to show anything in Dot Matrix.

`toggle()` function change the LED status of `(x, y)`. If `(x, y)` LED is on, it will be turn off.

`getPoint()` function gets LED status of `(x, y)`. Return type is `bool`. **Attention**, the status of LED is NOT necessarily correct before call `draw()`.