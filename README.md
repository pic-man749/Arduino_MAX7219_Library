# Arduino_MAX7219_Library

Arduino library for MAX7219 Dot Matrix Module 4 in 1 Display.

This library aims to control Dot Matrix Display using MAX7219 module like Processing.

You can use more than 4 Dot Matrix Module(Up to 255 * 255 or as far as memory permits).

Furthermore, you can freely decide the arrangement of modules.
For example, if you have 4 Dot Matrix module, any of these arrangements can be used : 1 * 4, 2 * 2, 4 * 1.

Hardware example:

* [MAX7219 Dot Matrix Module 4 in One Display - COLORMIX](https://www.gearbest.com/other-accessories/pp_1257191.html?wid=1433363)
* [ＭＡＸ７２１９使用赤色ドットマトリクスＬＥＤモジュール](http://akizukidenshi.com/catalog/g/gM-09984/)

###

## Support method

**Only implemented these methods now**

* point()
* allOn()
* allOff()
* setDrawMode()
* toggle()
* draw()
* setBrightness()

---

### Draw methods

* point(x, y)
* line(x1, y1, x2, y2)
* triangle(x1, y1, x2, y2, x3, y3)
* rect(x, y, w, h)
* quad(x1, y1, x2, y2, x3, y3, x4, y4)
* ellipse(x, y, w, h)
* fill()
    * only support LED status "ON" or "OFF"
* noFill()

### Coordinate manipulation methods

* translate(x, y)
* resetMatrix()

### Original methods

* allOn()
* allOff()
* setDrawMode(bool)
* draw()
* toggle(x, y)
* getPoint(x, y)
* setBrightness({0x00-0x0f})
