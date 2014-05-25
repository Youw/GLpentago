#include "stone.h"

Stone::Stone(GLint x_left_top,
             GLint y_left_top,
             GLint radius,
             const Texture2D& texture):
    active(false),
    setted(false),
    pressed(false),
    color{1,1,1,1},
    pos(x_left_top,y_left_top,radius*2,radius*2),
    texture(texture) {

}

Stone& Stone::setSize(int width, int height) {
  pos.setSize(width,height);
  return *this;
}

Stone& Stone::setSetted(bool set) {
  if(setted!=set) {
      pos = decltype(pos) (pos.posX()+pos.width(),pos.posY()+pos.height(),-pos.width(),-pos.height());
    }
  setted=set;
  return *this;
}

Stone& Stone::setTexture(const Texture2D& txtr) {
  texture = txtr;
  return *this;
}

void Stone::draw() const {
  float alpha_index = active&!setted?0.75:active&setted?1:setted?1:0.9;
  float color_index = active&setted?0.9:1;
  glColor4f(
      color[0]*color_index,
      color[1]*color_index,
      color[2]*color_index,
      color[3]*alpha_index*(pressed?0.9:1));

  texture.draw(pos.glCoords(),pos.dimension);
}

void Stone::mouseDown(int x, int y) {
  (void)x;
  (void)y;
  pressed = true;
}

void Stone::mouseUp(int x, int y) {
  (void)x;
  (void)y;
  pressed = false;
}

void Stone::hover(int x, int y) {
  (void)x;
  (void)y;
  active = true;
}

void Stone::unHover() {
  active = false;
}

#define SQR(x) (x)*(x)

bool Stone::underMouse(int x, int y) const {
  return std::sqrt(SQR(pos.posXcenter()-x)+SQR(pos.posYcenter()-y))<std::sqrt(pos.width()*pos.height())/2.0;
}

void Stone::setPos(int x, int y) {
  pos.setPos(x,y);
}

int Stone::posX() const {
  return pos.posX();
}

int Stone::posY() const {
  return pos.posY();
}

int Stone::height() const {
  return pos.height();
}

int Stone::width() const {
  return pos.width();
}
