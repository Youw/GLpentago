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
    x_pos-=(backgound?getFontMetrics().averageCharWidth():0);
    backgound = texture;
    x_pos+=(backgound?getFontMetrics().averageCharWidth():0);
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
