#ifndef TEXTURES_H
#define TEXTURES_H
#include <GL/gl.h>

//QT staff
#include <QString>
#include <QGLContext>
#include <QPoint>
typedef QString string;
typedef QGLContext Tcontext;
typedef QPoint point;
//

struct Texture2DInfo {
  GLint texture;
  int width, height;
  Texture2DInfo(): texture(0), width(0), height(0) {}
  Texture2DInfo(GLuint t, int w, int h): texture(t), width(w), height(h) {}
};

class Texture2D
{
  Texture2DInfo info;
  string filename;
  Tcontext* cxt;
public:

  Texture2D();
  //construct and load texture from file
  Texture2D(const string& filename, Tcontext* cxt);
  ~Texture2D();

  Texture2D(const Texture2D& right);
  Texture2D& operator=(const Texture2D& right);

  Tcontext* getCurContext() const { return cxt; }

  //release current and load new texture from filename
  bool load(const string& filename, Tcontext* cxt);
  //release this texture resources
  void release();

  operator GLuint() const { return info.texture; }

  int width() const { return info.width; }

  int height() const { return info.height; }

  //draw texture on current OpenGL context
  //starting with left top coordinates
  //and keep original texture size
  void draw(const point& left_top = point()) const;

  //draw texture on current OpenGL context
  //starting with left top coordinates to right bottom
  void draw(const point& left_top,const point& right_bottom) const;

  //draw texture on current OpenGL context
  //in quadrangle setted by input parameters
  void draw(const point& left_top,
             const point& right_top,
             const point& right_bottom,
             const point& left_bottom) const;
};

#endif // TEXTURES_H
