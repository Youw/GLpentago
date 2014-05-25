#include "pentagoboard.h"
#include "GLRectangleCoord.h"
#include "stone.h"


#define STONE_SIZE_TO_QUADRANT  0.2031
#define STONE_SPASE_TO_QUADRANT 0.1415
#define STONE_SPACE_BEGIN       0.0537
#define QUADRANTS_SPACE         0.0340



#include <array>
#include <vector>

using std::array;
using std::vector;

class BoardQuadrant: public RenderObject {
  GLRectangleCoord<GLint> pos;
  GLdouble angle;
  GLint dx,dy;
  PentagoBoard* parent;
  int my_pos_x, my_pos_y;
  int active_x, active_y;
  array<array<Stone,3>,3> stones;
public:

  BoardQuadrant(GLint x_left_top = 0,
                GLint y_left_top = 0,
                GLint width = 0,
                GLint height = 0,
                int my_pos_x = 0,
                int my_pos_y = 0,
                const Texture2D& texture = Texture2D()):
      pos(x_left_top, y_left_top, width, height),
      angle(0), dx(0), dy(0),
      my_pos_x(my_pos_x), my_pos_y(my_pos_y),
      active_x(-1), active_y(-1) {
    (void)texture;
    reposStones();
    for (auto& i: stones) {
        for (auto& o: i) {
            o.setTexture(Texture2D(":/graphics/stone.png"));
          }
      }
  }

  void setSize(int width, int height) {
    pos.setSize(width, height);
    reposStones();
  }

  void draw() const {
    glColor4f(1,0,0,1);
    glBindTexture(GL_TEXTURE_2D,0);
    glVertexPointer(pos.dimension, GL_INT, 0, pos.glCoords());
    glDrawArrays(GL_TRIANGLE_FAN,0,4);
    for (auto& i: stones) {
        for (auto& o: i) {
            o.draw();
          }
      }
  }

  virtual void setActive(bool active) override {
    if(!active) {
        unHover();
      }
  }

  void setActive(int stone_x, int stone_y) {
    stones[stone_x][stone_y].setActive(true);
    active_x = stone_x;
    active_y = stone_y;
  }

  virtual bool isActive() const override {
    return (active_x!=-1)&(active_y!=0);
  }

  virtual bool canBeActive() const override {
    return true;
  }

  void mouseDown(int x, int y) override {
    for (auto& i: stones) {
        for (auto& o: i) {
            if(o.underMouse(x,y)) {
                o.mouseDown(x,y);
              }
          }
      }
  }

  void mouseUp(int x, int y) override {
    for (auto& i: stones) {
        for (auto& o: i) {
            o.mouseUp(x,y);
          }
      }
  }

  void hover(int x, int y) override {
    for (unsigned i=0; i< stones.size(); i++) {
        for(unsigned j=0; j< stones[i].size(); j++) {
            if (stones[i][j].underMouse(x,y)) {
                stones[i][j].hover(x,y);
                if(isActive()) {
                    stones[active_x][active_y].unHover();
                  }
                active_x = i;
                active_y = j;
                return;
              }
          }
      }
  }

  void unHover() override {
    stones[active_x][active_y].unHover();
    active_x = -1;
    active_y = -1;
  }

  bool underMouse(int x, int y) const override {
    return pos.posInRect(x,y);
  }

  void setPos(int x, int y) override {
    pos.setPos(x,y);
    reposStones();
  }

  int posX() const override {
    return pos.posX();
  }

  int posY() const override {
    return pos.posY();
  }

  int height() const override {
    return pos.height();
  }

  int width() const override {
    return pos.width();
  }

  void keyPress(int key, bool repeat, KeyboardModifier mod) override {
    (void)repeat;
    if (mod == MD_NONE) {
        (void)key;
      }
  }

  void keyRelease(int key, KeyboardModifier mod) override {
    if (mod == MD_NONE) {
        (void)key;
      }
  }

private:
  void reposStones() {
    static const float H = STONE_SIZE_TO_QUADRANT;
    static const float h = STONE_SPASE_TO_QUADRANT;
    static const float hh = STONE_SPACE_BEGIN;

    for (unsigned i=0; i< stones.size(); i++) {
        for(unsigned j=0; j< stones[i].size(); j++) {
            stones[i][j].setPos(pos.posX()+pos.width()*(hh+i*(H+h)),pos.posY()+pos.height()*(hh+j*(H+h)));
            stones[i][j].setSize(pos.width()*H,pos.height()*H);
          }
      }
  }
}; //board quadrant

class PentagoBoardImpl: public RenderObject {
  GLRectangleCoord<GLint> pos;
  bool active;
  std::function<StoneSetCallBack> set_call_back;
  std::function<RotateCallBack> rotate_call_back;
  vector<vector<BoardQuadrant>> quadrants;

public:
  PentagoBoardImpl(GLint x_left_top = 0,
        GLint y_left_top = 0,
        GLint width = 0,
        GLint height = 0,
        int board_size = 2):
      pos(x_left_top, y_left_top, width, height),
      active(false),
      quadrants(board_size,vector<BoardQuadrant>(board_size)){
        reposQuadrants();
  }

  void setSize(int width, int height) {
    pos.setSize(width,height);
    reposQuadrants();
  }

  void setStone(int x_pos, int y_pos) {

  }

  void setStoneColor(int x_pos, int y_pos, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {

  }

  void unsetStone(int x_pos, int y_pos) {

  }

  void rotate(int board_x, int board_y, bool  right_direction) {

  }

  void setRotateCallBack(std::function<RotateCallBack> rotate_call_back) {
    this->rotate_call_back = rotate_call_back;
  }

  void callRotateCallBack(int quadrant_x, int quadrant_y, bool rotate_right) const {
    if(rotate_call_back)
      rotate_call_back(quadrant_x,quadrant_y,rotate_right);
  }

  void setStoneSetCallBack(std::function<StoneSetCallBack> stone_set_call_back) {
    this->set_call_back = stone_set_call_back;
  }

  void callStoneSetCallBack(int pos_x, int pos_y) const {
    if(set_call_back) {
        set_call_back(pos_y,pos_y);
      }
  }

  virtual void draw() const override {
    glColor4f(0.7,0.7,0.7,1);
    glBindTexture(GL_TEXTURE_2D,0);
    glVertexPointer(pos.dimension, GL_INT, 0, pos.glCoords());
    glDrawArrays(GL_TRIANGLE_FAN,0,4);
    for(auto& i: quadrants) {
        for(auto& o: i) {
            o.draw();
          }
      }
  }

  virtual void setActive(bool active) override {
    this->active = active;
  }

  virtual bool isActive() const override {
    return active;
  }

  virtual bool canBeActive() const override {
    return true;
  }

  virtual void click(int x, int y) override {
    for(auto& i: quadrants) {
        for(auto& o: i) {
            if(o.underMouse(x,y)) {
                o.click(x,y);
              }
          }
      }
  }

  virtual void mouseDown(int x, int y) override {
    for(auto& i: quadrants) {
        for(auto& o: i) {
            if(o.underMouse(x,y)) {
                o.mouseDown(x,y);
              }
          }
      }
  }

  virtual void mouseUp(int x, int y) override {
    for(auto& i: quadrants) {
        for(auto& o: i) {
            o.mouseUp(x,y);
          }
      }
  }

  virtual void hover(int x, int y) override {
    for(auto& i: quadrants) {
        for(auto& o: i) {
            if(o.underMouse(x,y)) {
                o.hover(x,y);
              }
          }
      }
  }

  virtual void unHover() override {
    for(auto& i: quadrants) {
        for(auto& o: i) {
              o.unHover();
          }
      }

  }

  virtual bool underMouse(int x, int y) const override {
    return pos.posInRect(x,y);
  }

  virtual void setPos(int x, int y) override {
    pos.setPos(x,y);
    reposQuadrants();
  }

  virtual int posX() const override {
    return pos.posY();
  }

  virtual int posY() const override {
    return pos.posY();
  }

  virtual int height() const override {
    return pos.height();
  }

  virtual int width() const override {
    return pos.width();
  }

  virtual void keyPress(int key, bool repeat, KeyboardModifier mod) override {
    (void)repeat;
    if(mod == MD_NONE) {
        (void)key;
      }
  }

  virtual void keyRelease(int key, KeyboardModifier mod) override {
    (void)key;
    (void)mod;
  }
private:
  void reposQuadrants() {
    double dx = pos.width()/(1/QUADRANTS_SPACE+(quadrants.size()-1)*(1+1/QUADRANTS_SPACE));
    double w = (pos.width()-dx*(quadrants.size()-1))/quadrants.size();
    double x = pos.posX();
    for(unsigned int i = 0; i<quadrants.size(); i++) {
        double y = pos.posY();
        double dy = pos.height()/(1/QUADRANTS_SPACE+(quadrants[0].size()-1)*(1+1/QUADRANTS_SPACE));
        double h = (pos.height()-dy*(quadrants[i].size()-1))/quadrants[i].size();
        for(unsigned int j = 0; j<quadrants[i].size(); j++) {
            quadrants[i][j].setPos(x,y);
            quadrants[i][j].setSize(std::round(w),std::round(h));
            y+=h+dy;
          }
        x+=w+dx;
      }
  }

};//class PentagoBoardImpl

PentagoBoard::PentagoBoard(GLint x_left_top, GLint y_left_top, GLint width, GLint height, int board_size):
    impl(new PentagoBoardImpl(x_left_top,y_left_top,width, height,board_size)) { }

PentagoBoard::~PentagoBoard() {
  delete impl;
}

PentagoBoard::PentagoBoard(const PentagoBoard& rigth) {
  delete impl;
  impl = new PentagoBoardImpl(*rigth.impl);
}

PentagoBoard& PentagoBoard::operator=(const PentagoBoard& rigth) {
  delete impl;
  impl = new PentagoBoardImpl(*rigth.impl);
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

PentagoBoard& PentagoBoard::setRotateCallBack(std::function<RotateCallBack> rotate_call_back) {

}

PentagoBoard& PentagoBoard::callRotateCallBack(int quadrant_x, int quadrant_y, bool rotate_right) const {

}

PentagoBoard& PentagoBoard::setStoneSetCallBack(std::function<StoneSetCallBack> stone_set_call_back) {

}

PentagoBoard& PentagoBoard::callStoneSetCallBack(int pos_x, int pos_y) const {

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
