#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

class RenderObject
{
public:
  virtual void draw() const = 0; //at least must be implemented
  virtual void click(int x, int y) { x=y=x; }
  virtual void mouseDown(int x, int y) { x=y=x; }
  virtual void mouseUp(int x, int y) { x=y=x; }
  virtual void hover(int x, int y) { x=y=x; }
  virtual void unHover() {}
  virtual bool underMouse(int x, int y) const { x=y=x; return false; }
  virtual ~RenderObject() { }

  virtual void setPos(int x, int y) = 0;
  virtual int posX() const = 0;
  virtual int posY() const = 0;
};

#endif // RENDEROBJECT_H
