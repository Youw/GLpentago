#include "button.h"

#include <QGLWidget>

#include <limits>

Texture2D Button::texture_blurr;

Button::Button(
               int x_left_top,
               int y_left_top,
               int width,
               int height,
               const string& caption,
               const Texture2D& texture): active(false), pressed(false) {

  setPos(x_left_top, y_left_top);
  QFont font = QFont("Snap ITC", height/2, 40, false);
  setFont(font);
  setFontColor4d(0.0,0.0,0.0,1.0);
  setSize(width,height);
  setTexture(texture);
  setCaption(caption);
}

Button& Button::setTexture(const Texture2D& texture) {
  this->texture = texture;
  return *this;
}

Button& Button::setCaption(const string& text) {
  this->text.setText(text);
  resetTextPos();
  return *this;
}

Button& Button::setClickCallBack(const std::function<void()>& call_back) {
  click_call_back = call_back;
  return *this;
}

Button& Button::setSize(int width, int height) {
  right_bottom.first = left_top.first+width;
  right_bottom.second = left_top.second+height;
  QFont font = text.getFont();
  font.setPointSize(height==0?1:height<0?-height/2:height/2);
  text.setFont(font);
  resetTextPos();
  return *this;
}

Button& Button::setFont(const QFont& font) {
  text.setFont(font);
  return *this;
}

Button& Button::resetTextPos() {
  //allign center:
  text.setPos((left_top.first+right_bottom.first-text.width())/2,
              (left_top.second+right_bottom.second)/2+text.strikeOutPos());
  return *this;
}

Button& Button::setFontColor4iv(const GLint* rgba) {
  font_color[0] = rgba[0];
  font_color[1] = rgba[1];
  font_color[2] = rgba[2];
  font_color[3] = rgba[3];
  text.setFontColor4iv(font_color);
  return *this;
}

Button& Button::setFontColor4i(GLint red,
                         GLint green,
                         GLint blue,
                         GLint alpha) {
  font_color[0] = red;
  font_color[1] = green;
  font_color[2] = blue;
  font_color[3] = alpha;
  text.setFontColor4iv(font_color);
  return *this;
}

Button& Button::setFontColor4d(GLdouble red,
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

void Button::setActive(bool active) {
  this->active = active;
}

Button& Button::setPressed(bool pressed) {
  this->pressed = pressed;
  if (pressed)
    text.setFontColor4d(font_color[0],font_color[1],font_color[2],0.7);
  else
    text.setFontColor4iv(font_color);
  return *this;
}



void Button::draw() const {
  int dx = 0;
  int dy = 0;
  if (active && pressed) {
    glColor4b(50,50,50,70);
    texture.draw({left_top.first,left_top.second},
                       {right_bottom.first,left_top.second},
                       {right_bottom.first,right_bottom.second},
                       {left_top.first,right_bottom.second});
    dx = 2;//(right_bottom.first-left_top.first)*0.03;
    dy = 1;//(right_bottom.second-left_top.second)*0.05;
  }
  glColor4b(127,127,127,127);//black
  texture.draw({left_top.first+dx,left_top.second+dy},
               {right_bottom.first-dx,left_top.second+dy},
               {right_bottom.first-dx,right_bottom.second-dy},
               {left_top.first+dx,right_bottom.second-dy});
  if(active | pressed) {
    dx += (right_bottom.first-left_top.first)*0.03;

    glColor4b(127,127,127,30);//transparent
    texture_blurr.draw({left_top.first+dx,left_top.second+dy},
                       {right_bottom.first-dx,left_top.second+dy},
                       {right_bottom.first-dx,right_bottom.second-dy},
                       {left_top.first+dx,right_bottom.second-dy});
  }
  text.draw();
}

void Button::click(int x, int y) {
  if(click_call_back)
    click_call_back();
  (void)x;
  (void)y;
}

void Button::mouseDown(int x, int y) {
  setPressed(true);
  (void)x;
  (void)y;
}

void Button::mouseUp(int x, int y) {
  if (pressed && underMouse(x,y)) {
    setPressed(false);//order is important
    click(x,y);//
  }
  setPressed(false);
}

void Button::hover(int x, int y) {
  setActive(true);
  (void)x;
  (void)y;
}

void Button::unHover() {
  setActive(false);
}

bool Button::underMouse(int x, int y) const {
  return (left_top.first <= x) && (left_top.second <= y) &&
      (right_bottom.first >= x) && (right_bottom.second >= y);
}

void Button::setPos(int x, int y) {
  left_top.first = x;
  left_top.second = y;
}
