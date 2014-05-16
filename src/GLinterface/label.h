#ifndef LABEL_H
#define LABEL_H

#include "renderobject.h"
#include "textures.h"
#include "GLfontutils.h"

#include "memory"

class QGLWidget;

class Label: RenderObject
{
public:

  //x_pos and y_pos - coordinates of base line of first character
  Label(const string& text = "label",
        int x_pos = 0,
        int y_pos = 0,
        const QFont& font = QFont());

  void setText(const string& text);
  const string& getText() const { return text; }

  //
  int width() const { return text_width; }
  int strikeOutPos() const { return strike_out_pos; }

  void setPos(int x, int y);
  int posX() const { return x; }
  int posY() const { return y; }

  void setFont(const QFont& font);
  const QFont& getFont() const { return text_font->font(); }

  const GLint* getFontColor() const { return color; }

  void setFontColor(const GLint* rgba);
  void setFontColor(GLint red,
                    GLint green,
                    GLint blue,
                    GLint alpha);
  void setFontColor(GLdouble red,
                    GLdouble green,
                    GLdouble blue,
                    GLdouble alpha);

  virtual void draw();
  virtual void click();
  virtual void mouseDown(int x, int y);
  virtual void mouseUp(int x, int y);
  virtual void hover(int x, int y);
  virtual void unHover();
  virtual bool underMouse(int x, int y);
private:
  std::unique_ptr<glutils::GLfont> text_font;
  string text;
  int text_width;
  int strike_out_pos;
  int x, y;
  GLint color[4];
};

#endif // LABEL_H
