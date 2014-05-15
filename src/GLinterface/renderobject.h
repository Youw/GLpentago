#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

class RenderObject
{
public:
  virtual void draw() = 0;
  virtual void click() = 0;
  virtual void mouseDown(int x, int y) = 0;
  virtual void mouseUp(int x, int y) = 0;
  virtual void hover(int x, int y) = 0;
  virtual void unHover() = 0;
  virtual bool underMouse(int x, int y) = 0;
  virtual ~RenderObject() { }
};

#endif // RENDEROBJECT_H
