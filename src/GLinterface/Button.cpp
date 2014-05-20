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
               const Texture2D& texture):
    text(caption),
    active(false),
    pressed(false),
    alpha_color_bak(INT_MAX) {

  setPos(x_left_top, y_left_top);
  setFontColor4d(0.0,0.0,0.0,1.0);
  setSize(width,height);
  setTexture(texture);
  setFont(QFont("Snap ITC", height/2, 40, false));
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


//From FontFeeperBase<Button>
//
Button& Button::setFont(const QFont& font) {
    text.setFont(font);
    resetTextPos();
    return *this;
}

const QFont& Button::getFont() const {
    return text.getFont();
}

Button& Button::setFontColor4i(GLint red, GLint green, GLint blue, GLint alpha) {
    alpha_color_bak = alpha;
    text.setFontColor4i(red,green,blue,alpha);
    return *this;
}

const GLint* Button::getFontColor() const {
    return text.getFontColor();
}
//
//

void Button::resetTextPos() {
  //allign center:
  //TODO: make possible allign left or right
  text.setPos((left_top.first+right_bottom.first-text.width())/2,
              (left_top.second+right_bottom.second-text.height())/2);
//    text.setPos(left_top.first,right_bottom.second);

}

void Button::setActive(bool active) {
  this->active = active;
}

Button& Button::setPressed(bool pressed) {
  if(this->pressed!=pressed) {
    this->pressed = pressed;
    const GLint* color = text.getFontColor();
    if (pressed) {
      alpha_color_bak = color[3];
      text.setFontColor4d(color[0],color[1],color[2],0.7);
    }
    else
      text.setFontColor4i(color[0],color[1],color[2],alpha_color_bak);
  }
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
  right_bottom.first+=x-left_top.first;
  right_bottom.second+=y-left_top.second;
  left_top.first = x;
  left_top.second = y;
  resetTextPos();
}

void Button::keyPress(int key, bool repeat, KeyboardModifier mod) {
  (void)repeat;
  if((mod==MD_NONE) && (key==Qt::Key_Return)) {
    mouseDown((left_top.first+right_bottom.first)/2,
              (left_top.second+right_bottom.second)/2);
  }
}

void Button::keyRelease(int key, KeyboardModifier mod) {
  (void)mod;
  if(key==Qt::Key_Return) {
    mouseUp((left_top.first+right_bottom.first)/2,
            (left_top.second+right_bottom.second)/2);
  }
}
