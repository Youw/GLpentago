#ifndef MENU_H
#define MENU_H

#include "renderobject.h"
#include "textures.h"
#include "GLRectangleCoord.h"

#include <utility>
#include <list>
#include <vector>
#include <memory>

class Menu: public RenderObject
{
public:
  Menu(int x_left_top = 0,
       int y_left_top = 0,
       int width = 0,
       int height = 0,
       const Texture2D& texture = Texture2D());

  Menu& setSize(int width, int height);
  Menu& setTexture(const Texture2D& texture);

  int getActiveIndex() const { return active_index; }
  Menu& setActiveIndex(int index);

  template<typename ObjectType>
  Menu& addObject(const ObjectType& object);

  virtual void draw() const override;

  virtual void setActive(bool active) override { this->active=active; }
  virtual bool isActive() const override { return active; }
  virtual bool canBeActive() const override { return true; }

  virtual void click(int x, int y) override;
  virtual void mouseDown(int x, int y) override;
  virtual void mouseUp(int x, int y) override;
  virtual void hover(int x, int y) override;
  virtual void unHover() override;
  virtual bool underMouse(int x, int y) const override;

  //position of left top corner of menu
  virtual void setPos(int x, int y) override;
  virtual int posX() const override { return pos.posX(); }
  virtual int posY() const override { return pos.posY(); }

  virtual int height() const override { return pos.height(); }
  virtual int width() const override { return pos.width(); }


  virtual void keyPress(int key, bool repeat, KeyboardModifier mod) override;
  virtual void keyRelease(int key, KeyboardModifier mod) override;
  virtual void charInput(int unicode_key) override;

private:
  Texture2D texture;
  GLRectangleCoord<GLint> pos;

  size_t active_index;
  std::vector<std::shared_ptr<RenderObject>> menu_objects;

  bool active;
};


template<typename RenderObjectType>
Menu& Menu::addObject(const RenderObjectType& object) {
  static_assert(std::is_base_of<RenderObject,RenderObjectType>::value,"RenderObject must be a base of \"object\"");
  menu_objects.push_back(std::shared_ptr<RenderObject>(new RenderObjectType(object)));
  if(menu_objects.size()) {
    if(!menu_objects[active_index]->isActive()) {
        setActiveIndex(menu_objects.size()-1);
    }
  }
  if (object.posX()==0)
    menu_objects.back()->setPos(pos.posXcenter()-object.width()/2,object.posY());
  return *this;
}

#endif // MENU_H
