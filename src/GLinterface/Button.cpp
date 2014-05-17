#include "button.h"

#include <QGLWidget>

Button::Button(
               int x_left_top,
               int y_left_top,
               int width,
               int height,
               const string& caption,
               const Texture2D& texture):
  left_top(x_left_top,y_left_top) {

  QFont font = QFont("Snap ITC", height/2, 40, false);
  setFont(font);
  setFontColor(0.0,0.0,0.0,1.0);
  resize(width,height);
  setTexture(texture);
  setCaption(caption);
}

void Button::setTexture(const Texture2D& texture) {
  this->texture = texture;
}

void Button::setCaption(const string& text) {
  this->text.setText(text);
  resetTextPos();
}

void Button::setClickCallBack(const std::function<void()>& call_back) {
  click_call_back = call_back;
}

void Button::resize(int width, int height) {
  right_bottom.first = left_top.first+width;
  right_bottom.second = left_top.second+height;
  QFont font = text.getFont();
  font.setPointSize(height==0?1:height<0?-height/2:height/2);
  text.setFont(font);
  resetTextPos();
}

void Button::setFont(const QFont& font) {
  text.setFont(font);
}

void Button::resetTextPos() {
  //allign center:
  text.setPos((left_top.first+right_bottom.first-text.width())/2,
              (left_top.second+right_bottom.second)/2+text.strikeOutPos());
}

void Button::setFontColor(const GLint* rgba) {
  text.setFontColor(rgba);
}

void Button::setFontColor(GLint red,
                         GLint green,
                         GLint blue,
                         GLint alpha) {
  text.setFontColor(red,green,blue,alpha);
}

void Button::setFontColor(GLdouble red,
                         GLdouble green,
                         GLdouble blue,
                         GLdouble alpha) {
  text.setFontColor(red,green,blue,alpha);
}

void Button::draw() {
  texture.draw({left_top.first,left_top.second},
               {right_bottom.first,left_top.second},
               {right_bottom.first,right_bottom.second},
               {left_top.first,right_bottom.second});
  text.draw();
}

void Button::click() {
  if(click_call_back)
    click_call_back();
}

void Button::mouseDown(int x, int y) {
  x=y=x;
}

void Button::mouseUp(int x, int y) {
  x=y=x;
}

void Button::hover(int x, int y) {
  x=y=x;
}

void Button::unHover() {

}

bool Button::underMouse(int x, int y) {
  return (left_top.first < x) && (left_top.second < y) &&
      (right_bottom.first > x) && (right_bottom.second > y);
}
