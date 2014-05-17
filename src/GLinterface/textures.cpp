#include "textures.h"
#include <map>
#include <mutex>
#include <QtOpenGL>
#include <QImage>

namespace Textures2DHolder {
  struct AllInfo {
    Texture2DInfo info;
    int count;
  };

  static std::mutex m;
  static std::map<QString,AllInfo> textures_list;

  static Texture2DInfo loadTexture(const string& filename, QGLContext* context) {
    AllInfo texture;
    if (filename!="") {
      std::lock_guard<std::mutex> lg(m);
      try {
        texture = textures_list.at(filename);
        textures_list[filename].count++;
      }catch(std::out_of_range&) {
        QImage im(filename);
        texture.info = Texture2DInfo(context->bindTexture(im), im.width(), im.height());
        texture.count = 1;
        textures_list[filename] = texture;
      }
    }
    return texture.info;
  }

  static void freeTexture(const string& filename, QGLContext* context) {
    std::lock_guard<std::mutex> lg(m);
    try {
      textures_list.at(filename).count--;
      if(textures_list[filename].count==0) {
        context->deleteTexture(textures_list[filename].info.texture);
        textures_list.erase(filename);
      }
    }catch(...) {

    }
  }
}

Texture2D::Texture2D(): cxt(nullptr) {

}

Texture2D::Texture2D(const string& filename, Tcontext* cxt): cxt(0) {
  load(filename, cxt);
}

Texture2D::~Texture2D() {
  release();
}

Texture2D::Texture2D(const Texture2D& right): cxt(0) {
  load(right.filename,right.cxt);
}

Texture2D& Texture2D::operator=(const Texture2D& right) {
  release();
  filename = right.filename;
  cxt = right.cxt;
  info = Textures2DHolder::loadTexture(filename, cxt);
  return *this;
}

bool Texture2D::load(const string& filename, Tcontext* cxt) {
  info = Textures2DHolder::loadTexture(filename, cxt);
  if (info.texture != 0) {
    this->filename = filename;
    this->cxt = cxt;
  } else {
    this->cxt = nullptr;
    return false;
  }
  return true;
}

void Texture2D::release() {
  if (cxt) {
    Textures2DHolder::freeTexture(filename, cxt);
    cxt = nullptr;
    filename.clear();
    info = Texture2DInfo();
  }
}

void Texture2D::draw(const point& left_top) const {
  draw(left_top,{left_top.x()+width(),left_top.y()+height()});
}

void Texture2D::draw(const point& left_top,const point& right_bottom) const {
  draw(left_top,
        {right_bottom.x(), left_top.y()},
        right_bottom,
        {left_top.x(), right_bottom.y()});
}

void Texture2D::draw(const point& left_top,
           const point& right_top,
           const point& right_bottom,
           const point& left_bottom) const {
//  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, info.texture);
  glBegin(GL_QUADS);
    glTexCoord2i(0, 1); glVertex2d(left_top.x(), left_top.y());
    glTexCoord2i(1, 1); glVertex2d(right_top.x(), right_top.y());
    glTexCoord2i(1, 0); glVertex2d(right_bottom.x(), right_bottom.y());
    glTexCoord2i(0, 0); glVertex2d(left_bottom.x(), left_bottom.y());
  glEnd();
//  glDisable(GL_TEXTURE_2D);
}
