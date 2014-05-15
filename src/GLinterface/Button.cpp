#include "button.h"

#include <QGLWidget>

Button::Button(QGLWidget* parent,
               int x_left_top,
               int y_left_top,
               int width,
               int height,
               const string& text,
               const Texture2D& texture):
  left_top(x_left_top,y_left_top),
  right_bottom(x_left_top+width, y_left_top+height) {

  parent_device = parent;
  setTexture(texture);
  setText(text);
}

void Button::setTexture(const Texture2D& texture) {
  this->texture = texture;
}

void Button::setText(const string& text) {
  this->text = text;
}

void Button::setClickCallBack(const std::function<void()>& call_back) {
  click_call_back = call_back;
}

void Button::draw() {
  texture.draw({left_top.first,left_top.second},
               {right_bottom.first,left_top.second},
               {right_bottom.first,right_bottom.second},
               {left_top.first,right_bottom.second});
  if (parent_device)
    parent_device->renderText(left_top.first,right_bottom.second,0.0,text);
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
