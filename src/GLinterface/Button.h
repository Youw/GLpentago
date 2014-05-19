#ifndef BUTTON_H
#define BUTTON_H

#include "renderobject.h"
#include "textures.h"
#include "fontkeeperbase.h"
#include "label.h"

#include <utility>
#include <functional>

class QGLWidget;

class Button: public RenderObject, public FontKeeperBase<Button>
{
public:
  Button(int x_left_top = 0,
         int y_left_top = 0,
         int width = 0,
         int height = 0,
         const string& caption = "Button",
         const Texture2D& texture = Texture2D());

  Button& setTexture(const Texture2D& texture);
  Button& setCaption(const string& caption);
  Button& setClickCallBack(const std::function<void()>& call_back);
  Button& setSize(int width, int height);

  virtual Button& setFont(const QFont& font) override;
  virtual const QFont& getFont() const override;

  virtual Button& setFontColor4i(GLint red, GLint green, GLint blue, GLint alpha) override;

  virtual const GLint* getFontColor() const override;

  bool isPressed() const { return pressed; }
protected:
  Button& setPressed(bool pressed);
public:

  virtual void draw() const override;

  virtual void setActive(bool active) override;
  virtual bool isActive() const override { return active; }
  virtual bool canBeActive() const override { return true; }

  virtual void click(int x, int y) override;
  virtual void mouseDown(int x, int y) override;
  virtual void mouseUp(int x, int y) override;
  virtual void hover(int x, int y) override;
  virtual void unHover() override;
  virtual bool underMouse(int x, int y) const override;

  //position of left top corner
  virtual void setPos(int x, int y) override;
  virtual int posX() const override { return left_top.first; }
  virtual int posY() const override { return left_top.second; }

  virtual int height() const override { return right_bottom.second-left_top.second; }
  virtual int width() const override { return right_bottom.first-left_top.first; }


  static Texture2D texture_blurr;

private:
  //calculate and set position of text
  void resetTextPos();
  Texture2D texture;
  std::pair<int,int> left_top;
  std::pair<int,int> right_bottom;

  Label text;

  std::function<void()> click_call_back;

  bool active;
  bool pressed;
  //for some little effect
  GLint alpha_color_bak;
};

#endif // BUTTON_H
