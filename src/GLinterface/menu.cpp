#include "menu.h"

Menu::Menu(int x_left_top,
           int y_left_top,
           int width,
           int height,
           const Texture2D& texture): now_active(0) {
  setPos(x_left_top,y_left_top);
  setSize(width, height);
  setTexture(texture);
}

Menu& Menu::setSize(int width, int height) {
  right_bottom.first = left_top.first+width;
  right_bottom.second = left_top.second+height;
  return *this;
}

Menu& Menu::setTexture(const Texture2D &texture) {
  this->texture = texture;
  return *this;
}

Menu& Menu::setActiveIndex(int index) {
  if(menu_objects[index]->canBeActive()) {
    menu_objects[index]->setActive(true);
    now_active = index;
  }
  return *this;
}

Menu& Menu::addButton(const Button& button) {
  buttons.push_back(button);
  menu_objects.push_back(&buttons.back());
  if(menu_objects.size()==1) {
      setActiveIndex(0);
  }
  buttons.back().setPos((left_top.first+right_bottom.first-button.width())/2,button.posY());
  return *this;
}

Menu& Menu::addLabel(const Label& label) {
  labels.push_back(label);
  menu_objects.push_back(&labels.back());
  if(menu_objects.size()==1) {
      setActiveIndex(0);
  }
  labels.back().setPos((left_top.first+right_bottom.first-label.width())/2,label.posY());
  return *this;
}

void Menu::draw() const {

  float sx = right_bottom.first-left_top.first,sy = right_bottom.second-left_top.second;
  float crop = 0.01, cro2=4*crop;
  float bcr = crop*sx, bc2 = cro2*sy;
  sx/=90;
  sy/=90;

  glColor4d(0.7,0.6,0.6,0.3);
  glBegin(GL_POLYGON);
     glVertex2d(left_top.first        ,left_top.second    +bc2);
     glVertex2d(left_top.first    +bcr,left_top.second    +bcr);
     glVertex2d(left_top.first    +bc2,left_top.second        );

     glVertex2d(right_bottom.first-bc2,left_top.second        );
     glVertex2d(right_bottom.first-bcr,left_top.second    +bcr);
     glVertex2d(right_bottom.first    ,left_top.second    +bc2);

     glVertex2d(right_bottom.first    ,right_bottom.second-bc2);
     glVertex2d(right_bottom.first-bcr,right_bottom.second-bcr);
     glVertex2d(right_bottom.first-bc2,right_bottom.second    );

     glVertex2d(left_top.first    +bc2,right_bottom.second    );
     glVertex2d(left_top.first    +bcr,right_bottom.second-bcr);
     glVertex2d(left_top.first        ,right_bottom.second-bc2);
  glEnd();
  glColor4d(0.5,0.5,0.5,0.6);

  glBindTexture(GL_TEXTURE_2D,texture);
  glBegin(GL_POLYGON);
    glTexCoord2d((0.0     )*sx, (1.0-cro2)*sy); glVertex2d(left_top.first        ,left_top.second    +bc2);
    glTexCoord2d((0.0+crop)*sx, (1.0-crop)*sy); glVertex2d(left_top.first    +bcr,left_top.second    +bcr);
    glTexCoord2d((0.0+cro2)*sx, (1.0     )*sy); glVertex2d(left_top.first    +bc2,left_top.second        );

    glTexCoord2d((1.0-cro2)*sx, (1.0     )*sy); glVertex2d(right_bottom.first-bc2,left_top.second        );
    glTexCoord2d((1.0-crop)*sx, (1.0-crop)*sy); glVertex2d(right_bottom.first-bcr,left_top.second    +bcr);
    glTexCoord2d((1.0     )*sx, (1.0-cro2)*sy); glVertex2d(right_bottom.first    ,left_top.second    +bc2);

    glTexCoord2d((1.0     )*sx, (0.0+cro2)*sy); glVertex2d(right_bottom.first    ,right_bottom.second-bc2);
    glTexCoord2d((1.0-crop)*sx, (0.0+crop)*sy); glVertex2d(right_bottom.first-bcr,right_bottom.second-bcr);
    glTexCoord2d((1.0-cro2)*sx, (0.0     )*sy); glVertex2d(right_bottom.first-bc2,right_bottom.second    );

    glTexCoord2d((0.0+cro2)*sx, (0.0     )*sy); glVertex2d(left_top.first    +bc2,right_bottom.second    );
    glTexCoord2d((0.0+crop)*sx, (0.0+crop)*sy); glVertex2d(left_top.first    +bcr,right_bottom.second-bcr);
    glTexCoord2d((0.0     )*sx, (0.0+cro2)*sy); glVertex2d(left_top.first        ,right_bottom.second-bc2);
  glEnd();

  for(auto o: menu_objects) {
    o->draw();
  }
//  int xx = (left_top.first+right_bottom.first-labels.front().width())/2;
//  glColor4f(1,0,0,0.5);
//  glBegin(GL_QUADS);
//    glVertex2d(xx,left_top.second);
//    glVertex2d(xx+labels.front().width(),left_top.second);
//    glVertex2d(xx+labels.front().width(),left_top.second+50);
//    glVertex2d(xx,left_top.second+50);
//  glEnd();
}

void Menu::click(int x, int y) {
  for(auto o: menu_objects) {
    if (o->underMouse(x,y))
      o->click(x,y);
  }
}

void Menu::mouseDown(int x, int y) {
  for(auto o: menu_objects) {
    if(o->underMouse(x,y)) {
      o->mouseDown(x,y);
    }
  }
}

void Menu::mouseUp(int x, int y) {
  for(auto o: menu_objects) {
    o->mouseUp(x,y);
  }
}

void Menu::hover(int x, int y) {
  for(size_t i=0; i<menu_objects.size(); i++) {
    if (menu_objects[i]->underMouse(x,y)) {
      menu_objects[i]->hover(x,y);
      if(now_active!=i && menu_objects[i]->isActive()) {
        menu_objects[now_active]->setActive(false);
        now_active = i;
      }
    }
  }
}

void Menu::unHover() {

}

bool Menu::underMouse(int x, int y) const {
  return (left_top.first <= x) && (left_top.second <= y) &&
      (right_bottom.first >= x) && (right_bottom.second >= y);
}

void Menu::setPos(int x, int y) {
  left_top.first = x;
  left_top.second = y;
}

void Menu::keyPress(int key, bool repeat, KeyboardModifier mod) {
  repeat = key==mod && repeat;
}
