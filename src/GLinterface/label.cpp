#include "label.h"

Label::Label(
      QGLWidget* paint_context,
      const string& text,
      int x_pos,
      int y_pos,
      const QFont& font):
  text_font(font),
  metric(text_font),
  x(x_pos), y(y_pos){

  this->paint_context = paint_context;
  setText(text);
}

void Label::setText(const string& text) {
  this->text = text;
  auto&& sss = metric.boundingRect(text);
  width = sss.width();
  height = sss.height();
}

void Label::setPos(int x, int y) {
  this->x = x;
  this->y = y;
}

void Label::setFont(const QFont& font) {
  text_font = font;
  metric = QFontMetrics(text_font);
  auto&& sss = metric.boundingRect(text);
  width = sss.width();
  height = sss.height();
}

void Label::draw() {
  if (paint_context)
    paint_context->renderText(x,y,0.0,text,text_font);
}

void Label::click() {
  //donothing
}

void Label::mouseDown(int x, int y) {
  x=y=x;
  //TODO: later
}

void Label::mouseUp(int x, int y) {
  x=y=x;
  //TODO: later
}

void Label::hover(int x, int y) {
  x=y=x;
  //TODO: later
}

void Label::unHover() {
  //TODO: later
}

bool Label::underMouse(int x, int y) {
  //TODO: later
  x=y=x;
  return false;
}
