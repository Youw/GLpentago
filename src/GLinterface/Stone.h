#ifndef STONE_H
#define STONE_H

#include "renderobject.h"
#include "GLRectangleCoord.h"
#include "textures.h"

#ifndef HAVE_GLES
#include <GL/gl.h>
#else
#include <GLES/gl.h>
#endif

class Stone: public RenderObject
{
public:
  Stone(GLint x_left_top = 0,
        GLint y_left_top = 0,
        GLint radius = 0,
        const Texture2D& texture = Texture2D());

  bool isSetted() const { return setted; }
  Stone& setSetted(bool set);

  Stone& setTexture(const Texture2D& texture = Texture2D());

  virtual void draw() const override;

  virtual void setActive(bool active) { this->active = active; }
  virtual bool isActive() const { return active; }
  virtual bool canBeActive() const { return true; }

//  virtual void click(int x, int y) override;
  virtual void mouseDown(int x, int y) override;
  virtual void mouseUp(int x, int y) override;
  virtual void hover(int x, int y) override;
  virtual void unHover() override;
  virtual bool underMouse(int x, int y) const override;

  virtual void setPos(int x, int y) override;
  virtual int posX() const override;
  virtual int posY() const override;
  virtual int height() const override;
  virtual int width() const override;

private:
  bool active;
  bool setted;
  bool pressed;
  GLfloat color[4];

  GLRectangleCoord<GLint,2> pos;
  Texture2D texture;
};

#endif // STONE_H
