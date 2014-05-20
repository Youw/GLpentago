#include "menu.h"
#include <type_traits>

Menu::Menu(int x_left_top,
           int y_left_top,
           int width,
           int height,
           const Texture2D& texture): active_index(0), active(true) {
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
    menu_objects[active_index]->setActive(false);
    menu_objects[index]->setActive(true);
    active_index = index;
  }
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
      if(active_index!=i && menu_objects[i]->isActive()) {
        menu_objects[active_index]->setActive(false);
        active_index = i;
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

static bool isActive(const std::shared_ptr<RenderObject>& o) {
    return o->isActive();
}

void Menu::keyPress(int key, bool repeat, KeyboardModifier mod) {
  if (key==Qt::Key_Tab) key = Qt::Key_Down; else
  //Shift+Tab
  if (key==Qt::Key_Backtab) key = Qt::Key_Up;
  unsigned find_count = menu_objects.size();
  if(!find_count) return;
  switch (key) {
    unsigned index;
    case Qt::Key_Down:
      index = active_index;
      do {
        if (index==menu_objects.size()-1)
          index=0;
        else
          index++;
        find_count--;
      } while(find_count && !(menu_objects[index]->canBeActive()));
      setActiveIndex(index);
      break;
    case Qt::Key_Up:
      find_count = menu_objects.size();
      index = active_index;
      do {
        if (index==0)
          index=menu_objects.size()-1;
        else
          index--;
        find_count--;
      } while(find_count && !(menu_objects[index]->canBeActive()));
      setActiveIndex(index);
      break;
    case Qt::Key_Escape: {
      auto o = menu_objects.back();
      o->click(o->posX()+o->width()/2,o->posY()+o->height()/2);
      break;
    }
    default:
      auto it = std::find_if(menu_objects.begin(),menu_objects.end(),::isActive);
      if (it!=menu_objects.end()) (*it)->keyPress(key,repeat,mod);
  }
}

void Menu::keyRelease(int key, KeyboardModifier mod) {
  auto it = std::find_if(menu_objects.begin(),menu_objects.end(),::isActive);
  if (it!=menu_objects.end()) (*it)->keyRelease(key,mod);
}

void Menu::charInput(int unicode_key) {
    auto it = std::find_if(menu_objects.begin(),menu_objects.end(),::isActive);
    if (it!=menu_objects.end()) (*it)->charInput(unicode_key);
}

