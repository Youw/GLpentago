#include "label.h"
#include <limits>

Label::Label(
      const string& text,
      int x,
      int y,
      const QFont& font) {

  setPos(x,y);
  setFont(font);
  setText(text);
}

Label& Label::setText(const string& text) {
  this->text = text;
  this->text_width = text_font->fontMetrics().width(text);
  this->strike_out_pos = text_font->fontMetrics().strikeOutPos();
  return *this;
}

void Label::setPos(int x, int y) {
  this->pos_x = x;
  this->pos_y = y;
}

Label& Label::setFont(const QFont& font) {
  this->text_font.reset(new glutils::GLfont(QFont(font)));
  this->text_width = text_font->fontMetrics().width(text);
  this->strike_out_pos = text_font->fontMetrics().strikeOutPos();
  return *this;
}

Label& Label::setFontColor4iv(const GLint* rgba) {
  color[0] = rgba[0];
  color[1] = rgba[1];
  color[2] = rgba[2];
  color[3] = rgba[3];
  return *this;
}

Label& Label::setFontColor4i(GLint red,
                          GLint green,
                          GLint blue,
                          GLint alpha) {
  color[0] = red;
  color[1] = green;
  color[2] = blue;
  color[3] = alpha;
  return *this;
}

Label& Label::setFontColor4d(GLdouble red,
                           GLdouble green,
                           GLdouble blue,
                           GLdouble alpha) {

  GLint int_max = std::numeric_limits<GLint>::max();
  setFontColor4i(
        GLint(int_max*red),
        GLint(int_max*green),
        GLint(int_max*blue),
        GLint(int_max*alpha));
  return *this;
}

void Label::draw() const {
//  GLint cur_color[4];
//  glGetIntegerv(GL_CURRENT_COLOR,cur_color);
  glColor4iv(color);
  text_font->renderText(pos_x,pos_y,text);
//  glColor4iv(cur_color);
}
