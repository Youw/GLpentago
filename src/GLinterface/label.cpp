#include "label.h"
#include <limits>

Label::Label(const string& m_text,int x,int y,const QFont& font):
    FontKeeper(font), text(m_text), x_pos(x), y_pos(y) {
    fontChanged();
}

Label& Label::setText(const string& text) {
  this->text = text;
  fontChanged();
  return *this;
}

Label& Label::setBackground(const Texture2D& texture) {
    backgound = texture;
    fontChanged();
    return *this;
}

int Label::posX() const {
    return x_pos-(backgound?getFontMetrics().averageCharWidth():0);
}

int Label::posY() const {
    return y_pos;
}

void Label::setPos(int x, int y) {
  x_pos = x+(backgound?getFontMetrics().averageCharWidth():0);
  y_pos = y;
}

int Label::width() const {
    return text_width+(backgound?2*getFontMetrics().averageCharWidth():0);
}

int Label::height() const {
    return getFontMetrics().height();
}


void Label::draw() const {
//    glColor4f(1,0,0,0.5);
//    int dy = text_font->fontMetrics().ascent();
//   // int dy2 = text_font->fontMetrics().descent();
//  //  int dy2 = text_font->fontMetrics().leading();
//    int dy2 = -text_font->fontMetrics().height();
//    glBegin(GL_QUADS);
//      glVertex2f(x_pos,y_pos);
//      glVertex2f(x_pos+width(),y_pos);
//      glVertex2f(x_pos+width(),y_pos-dy);
//      glVertex2f(x_pos,y_pos-dy);
//    glEnd();
//    glColor4f(0,1,0,0.5);
//    glBegin(GL_QUADS);
//      glVertex2f(x_pos,y_pos);
//      glVertex2f(x_pos+width(),y_pos);
//      glVertex2f(x_pos+width(),y_pos-dy2);
//      glVertex2f(x_pos,y_pos-dy2);
//    glEnd();
  if(backgound) {
      glColor4f(1,1,1,1);
      int a = getFontMetrics().averageCharWidth();
      backgound.draw({x_pos-a,y_pos},
                     {x_pos+text_width+a,y_pos},
                     {x_pos+text_width+a,y_pos+height()},
                     {x_pos-a,y_pos+height()});
  }
  glColor4iv(font_color);
  text_font->renderText(x_pos,y_pos,text);
}

void Label::fontChanged() {
  this->text_width = text_font->fontMetrics().width(text);
//  this->strike_out_pos = text_font->fontMetrics().strikeOutPos();
}
