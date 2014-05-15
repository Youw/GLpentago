#ifndef LABEL_H
#define LABEL_H

#include "renderobject.h"
#include "textures.h"
#include <cstdint>

class QGLWidget;

class Label: RenderObject
{
public:

  Label(QGLWidget* paint_context = nullptr,
      const string& text = "label",
        int x_pos = 0,
        int y_pos = 0,
        const QFont& font = QFont());

  void setText(const string& text);
  const string& getText() const { return text; }

  int getTextWidth() const { return width; }
  int getTextHeight() const { return height; }

  void setPos(int x, int y);
  int posX() const { return x; }
  int posY() const { return y; }

  void setFont(const QFont& font);
  const QFont& getFont() { return text_font; }

  virtual void draw();
  virtual void click();
  virtual void mouseDown(int x, int y);
  virtual void mouseUp(int x, int y);
  virtual void hover(int x, int y);
  virtual void unHover();
  virtual bool underMouse(int x, int y);
private:
  QGLWidget* paint_context;
  string text;
  QFont text_font;
  QFontMetrics metric;
  int width;
  int height;
  int x, y;
};

#endif // LABEL_H
