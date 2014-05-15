#include "button.h"

#include <QGLWidget>

Button::Button(QGLWidget* parent,
               int x_left_top,
               int y_left_top,
               int width,
               int height,
               const string& caption,
               const Texture2D& texture):
  left_top(x_left_top,y_left_top),
  right_bottom(x_left_top+width, y_left_top+height),
  text(parent) {

  setTexture(texture);
  setCaption(caption);
  QFont font = QFont("Arial", 16, 65, true);
  text.setFont(font);
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
  resetTextPos();
}

void Button::resetTextPos() {
  //allign center:
  text.setPos((left_top.first+right_bottom.first-text.getTextWidth())/2,
              (left_top.second+right_bottom.second+text.getTextHeight())/2);
}

void Button::draw() {
  GLint color[4];
  texture.draw({left_top.first,left_top.second},
               {right_bottom.first,left_top.second},
               {right_bottom.first,right_bottom.second},
               {left_top.first,right_bottom.second});
  glGetIntegerv(GL_CURRENT_COLOR,color);
  glColor4f(0,0,0,1);
  text.draw();
  glColor4iv(color);
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
