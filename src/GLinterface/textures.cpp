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

Texture2D::Texture2D(const string& filename, Tcontext* cxt): cxt(nullptr),
    crop_lt(0,1), crop_rt(1,1), crop_rb(1,0), crop_lb(0,0) {
  load(filename, cxt);
}

Texture2D::~Texture2D() {
  release();
}

Texture2D::Texture2D(const Texture2D& right): cxt(nullptr),
    crop_lt(0,1), crop_rt(1,1), crop_rb(1,0), crop_lb(0,0){
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
  draw(left_top,{left_top.x+width(),left_top.y+height()});
}

void Texture2D::draw(const point& left_top,const point& right_bottom) const {
  draw(left_top,
        {right_bottom.x, left_top.y},
        right_bottom,
        {left_top.x, right_bottom.y});
}

void Texture2D::draw(const point& left_top,
           const point& right_top,
           const point& right_bottom,
           const point& left_bottom) const {
  glBindTexture(GL_TEXTURE_2D, info.texture);
  glBegin(GL_QUADS);
    glTexCoord2i(crop_lt.x, crop_lt.y); glVertex2d(left_top.x, left_top.y);
    glTexCoord2i(crop_rt.x, crop_rt.y); glVertex2d(right_top.x, right_top.y);
    glTexCoord2i(crop_rb.x, crop_rb.y); glVertex2d(right_bottom.x, right_bottom.y);
    glTexCoord2i(crop_lb.x, crop_lb.y); glVertex2d(left_bottom.x, left_bottom.y);
  glEnd();
}

//Texture2D& Texture2D::setRepeatScale(float x_sc, float y_sc) {
//  return *this;
//}

Texture2D& Texture2D::setCropRegion(
        const point& left_top,const point& right_top,
        const point& right_bottom, const point& left_bottom) {
    crop_lt.x = double(info.width)/left_top.x;
    crop_rt.x = double(info.width)/right_top.x;
    crop_rb.x = double(info.width)/right_bottom.x;
    crop_lb.x = double(info.width)/left_bottom.x;

    crop_lt.y = double(info.height)/left_top.y;
    crop_rt.y = double(info.height)/right_top.y;
    crop_rb.y = double(info.height)/right_bottom.y;
    crop_lb.y = double(info.height)/left_bottom.y;
    return *this;
}
