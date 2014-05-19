#ifndef MENU_H
#define MENU_H

#include "renderobject.h"
#include "textures.h"
#include "button.h"
#include "label.h"

#include <utility>
#include <list>
#include <vector>

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

  int activeIndex() const { return now_active; }
  Menu& setActiveIndex(int index);

  Menu& addButton(const Button& button);
  Menu& addLabel(const Label& label);

  virtual void draw() const override;

  virtual void click(int x, int y) override;
  virtual void mouseDown(int x, int y) override;
  virtual void mouseUp(int x, int y) override;
  virtual void hover(int x, int y) override;
  virtual void unHover() override;
  virtual bool underMouse(int x, int y) const override;

  //position of left top corner of menu
  virtual void setPos(int x, int y) override;
  virtual int posX() const override { return left_top.first; }
  virtual int posY() const override { return left_top.second; }

  virtual int height() const override { return right_bottom.second-left_top.first; }
  virtual int width() const override { return right_bottom.second-left_top.second; }


  virtual void keyPress(int key, bool repeat, KeyboardModifier mod) override;
//  virtual void keyRelease(int key, KeyboardModifier mod) override;

private:
  Texture2D texture;
  std::pair<int,int> left_top;
  std::pair<int,int> right_bottom;

  size_t now_active;
  std::vector<RenderObject*> menu_objects;

  std::list<Button> buttons;
  std::list<Label> labels;

};

#endif // MENU_H
