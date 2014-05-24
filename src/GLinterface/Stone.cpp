#include "stone.h"

Stone::Stone(GLint x_left_top,
             GLint y_left_top,
             GLint radius,
             const Texture2D& texture):
    active(false),
    setted(false),
    pressed(false),
    color{1,1,1,0.5},
    pos(x_left_top,y_left_top,radius*2,radius*2),
    texture(texture) {

}

Stone& Stone::setSetted(bool set) {
  setted=set;
  return *this;
}

Stone& Stone::setTexture(const Texture2D& txtr) {
  texture = txtr;
  return *this;
}

void Stone::draw() const {
  glColor4f(color[0],color[1],color[2],color[3]);
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
  return std::sqrt(SQR(pos.posXcenter()-x)+SQR(pos.posYcenter()-y))<pos.width()/2.0;
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
