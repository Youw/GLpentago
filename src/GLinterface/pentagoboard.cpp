#include "pentagoboard.h"

class PentagoBoardImpl: public RenderObject {
public:
  PentagoBoardImpl(GLint x_left_top = 0,
        GLint y_left_top = 0,
        GLint width = 0,
        GLint height = 0,
        int board_size = 2) {

  }

  void setSize(int width, int height) {

  }

  void setStone(int x_pos, int y_pos) {

  }

  void setStoneColor(int x_pos, int y_pos, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {

  }

  void unsetStone(int x_pos, int y_pos) {

  }

  void rotate(int board_x, int board_y, bool  right_direction) {

  }


  virtual void draw() const override {

  }

  virtual void setActive(bool active) override {

  }

  virtual bool isActive() const override {
    return true;
  }

  virtual bool canBeActive() const override {
    return true;
  }

  virtual void click(int x, int y) override {

  }

  virtual void mouseDown(int x, int y) override {

  }

  virtual void mouseUp(int x, int y) override {

  }

  virtual void hover(int x, int y) override {

  }

  virtual void unHover() override {

  }

  virtual bool underMouse(int x, int y) const override {
    return false;
  }

  virtual void setPos(int x, int y) override {

  }

  virtual int posX() const override {
    return 0;
  }

  virtual int posY() const override {
    return 0;
  }

  virtual int height() const override {
    return 0;
  }

  virtual int width() const override {
    return 0;
  }

  virtual void keyPress(int key, bool repeat, KeyboardModifier mod) override {

  }

  virtual void keyRelease(int key, KeyboardModifier mod) override {

  }

  virtual void charInput(int unicode_key) override {

  }

private:
};

PentagoBoard::PentagoBoard(GLint x_left_top, GLint y_left_top, GLint width, GLint height, int board_size):
    impl(new PentagoBoardImpl(x_left_top,y_left_top,width, height,board_size)) { }

PentagoBoard::PentagoBoard(const PentagoBoard& rigth) {
  this->impl.reset(new PentagoBoardImpl(*rigth.impl));
}

PentagoBoard& PentagoBoard::operator=(const PentagoBoard& rigth) {
  this->impl.reset(new PentagoBoardImpl(*rigth.impl));
  return *this;
}


PentagoBoard& PentagoBoard::setSize(int width, int height) {
  impl->setSize(width, height);
  return *this;
}

PentagoBoard& PentagoBoard::setStone(int x_pos, int y_pos) {
  impl->setStone(x_pos, y_pos);
  return *this;
}

PentagoBoard& PentagoBoard::setStoneColor(int x_pos, int y_pos, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
  impl->setStoneColor(x_pos, y_pos,red, green, blue, alpha);
  return *this;
}

PentagoBoard& PentagoBoard::unsetStone(int x_pos, int y_pos) {
  impl->unsetStone(x_pos, y_pos);
  return *this;
}

PentagoBoard& PentagoBoard::rotate(int board_x, int board_y, bool  right_direction) {
  impl->rotate(board_x, board_y, right_direction);
  return *this;
}


void PentagoBoard::draw() const {
  impl->draw();
}

void PentagoBoard::setActive(bool active) {
  impl->setActive(active);
}

bool PentagoBoard::isActive() const {
  return impl->isActive();
}

bool PentagoBoard::canBeActive() const {
  return impl->canBeActive();
}

void PentagoBoard::click(int x, int y) {
  impl->click(x,y);
}

void PentagoBoard::mouseDown(int x, int y) {
  impl->mouseDown(x,y);
}

void PentagoBoard::mouseUp(int x, int y) {
  impl->mouseUp(x,y);
}

void PentagoBoard::hover(int x, int y) {
  impl->hover(x,y);
}

void PentagoBoard::unHover() {
  impl->unHover();
}

bool PentagoBoard::underMouse(int x, int y) const {
  return impl->underMouse(x,y);
}

void PentagoBoard::setPos(int x, int y) {
  impl->setPos(x,y);
}

int  PentagoBoard::posX() const {
  return impl->posX();
}

int  PentagoBoard::posY() const {
  return impl->posY();
}

int  PentagoBoard::height() const {
  return impl->height();
}

int  PentagoBoard::width() const {
  return impl->width();
}

void PentagoBoard::keyPress(int key, bool repeat, KeyboardModifier mod) {
  impl->keyPress(key,repeat,mod);
}

void PentagoBoard::keyRelease(int key, KeyboardModifier mod) {
  impl->keyRelease(key,mod);
}

void PentagoBoard::charInput(int unicode_key) {
  impl->charInput(unicode_key);
}
