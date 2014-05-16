#ifndef BUTTON_H
#define BUTTON_H

#include "renderobject.h"
#include "textures.h"
#include "label.h"

#include <utility>
#include <string>
#include <functional>

class QGLWidget;

class Button: RenderObject
{
public:
  Button(int x_left_top = 0,
         int y_left_top = 0,
         int width = 0,
         int height = 0,
         const string& caption = "Button",
         const Texture2D& texture = Texture2D());

  void setTexture(const Texture2D& texture);
  void setCaption(const string& caption);
  void setClickCallBack(const std::function<void()>& call_back);
  void resize(int width, int height);
  void setFont(const QFont& font);
  const QFont& getFont() const { return text.getFont(); }


  const GLint* getFontColor() const { return text.getFontColor(); }

  void setFontColor(const GLint* rgba);
  void setFontColor(GLint red,
                    GLint green,
                    GLint blue,
                    GLint alpha);
  void setFontColor(GLdouble red,
                    GLdouble green,
                    GLdouble blue,
                    GLdouble alpha);

  virtual void draw();
  virtual void click();
  virtual void mouseDown(int x, int y);
  virtual void mouseUp(int x, int y);
  virtual void hover(int x, int y);
  virtual void unHover();
  virtual bool underMouse(int x, int y);
private:
  //calculate and set position of text
  void resetTextPos();
  Texture2D texture;
  std::pair<int,int> left_top;
  std::pair<int,int> right_bottom;
  Label text;
  std::function<void()> click_call_back;
};

#endif // BUTTON_H
