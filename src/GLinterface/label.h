#ifndef LABEL_H
#define LABEL_H

#include "renderobject.h"
#include "textures.h"
#include "GLfontutils.h"

#include "memory"

class QGLWidget;

class Label: public RenderObject
{
public:

  //x_pos and y_pos - coordinates of base line of first character
  Label(const string& text = "label",
        int x= 0,
        int y= 0,
        const QFont& font = QFont());

  void setText(const string& text);
  const string& getText() const { return text; }

  //width of text according to Font
  int width() const { return text_width; }
  //offset of strike out relative to baseline
  int strikeOutPos() const { return strike_out_pos; }

  void setFont(const QFont& font);
  const QFont& getFont() const { return text_font->font(); }

  const GLint* getFontColor() const { return color; }

  void setFontColor4iv(const GLint* rgba);
  void setFontColor4i(GLint red,
                    GLint green,
                    GLint blue,
                    GLint alpha);
  void setFontColor4d(GLdouble red,
                    GLdouble green,
                    GLdouble blue,
                    GLdouble alpha);

  virtual void draw() const override;
//  virtual void click() override;
//  virtual void mouseDown(int pos_x, int pos_y) override;
//  virtual void mouseUp(int pos_x, int pos_y) override;
//  virtual void hover(int pos_x, int pos_y) override;
//  virtual void unHover() override;
//  virtual bool underMouse(int pos_x, int pos_y) override;
  //set and get position of baseline
  virtual void setPos(int x, int y) override;
  virtual int posX() const override { return pos_x; }
  virtual int posY() const override { return pos_y; }
private:
  std::unique_ptr<glutils::GLfont> text_font;
  string text;
  int text_width;
  int strike_out_pos;
  int pos_x, pos_y;
  GLint color[4];
};

#endif // LABEL_H
