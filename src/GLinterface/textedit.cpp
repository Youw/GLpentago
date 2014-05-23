#include "textedit.h"

#define DP 4

TextEdit::TextEdit(
    GLint x_left_top, GLint y_left_top, GLint width, GLint height, const Texture2D &background):
  background(background),  pos(x_left_top,y_left_top) {

  calcCrop();
  text.setFont(QFont("Snap ITC", height/2, 40, false));
  setSize(width,height);
}

void TextEdit::calcCrop() {
  crop_pos = decltype(crop_pos)
      (pos.posX()+6,pos.posY()+4,pos.width()-12, pos.height()-8);
}

TextEdit& TextEdit::setSize(GLint width,GLint  height) {
  pos.setSize(width,height);
  calcCrop();
  QFont font = text.getFont();
  height = abs(height);
  height = std::min(height,150);
  height /= 2;
  font.setPointSize(height==0?1:height);
  text.setFont(font);
  text.setPos(crop_pos.posX()+DP,crop_pos.posY());
  return *this;
}

TextEdit& TextEdit::setCurPos(unsigned pos) {
  if(pos<(unsigned)text.getText().length()) {
      cur_pos = pos;
      cur_world_pos = text.posX() + text.getFontMetrics().width(text.getText(),cur_pos);
      if (cur_world_pos>crop_pos.getRight()-DP) {
          int dx = cur_world_pos-(crop_pos.getRight()-DP);
          cur_world_pos-=dx;
          text.setPos(text.posX()-dx,text.posY());
        }
      if (cur_world_pos<crop_pos.getLeft()+DP) {
          int dx = crop_pos.getLeft()+DP-cur_world_pos;
          cur_world_pos+=dx;
          text.setPos(text.posX()+dx,text.posY());
        }
    }
  return *this;
}

TextEdit& TextEdit::setText(const string& text) {
  this->text.setText(text);
  return *this;
}

TextEdit& TextEdit::setTexture(const Texture2D& bckgrnd) {
  background = bckgrnd;
  return *this;
}

void TextEdit::draw() const {
  glColor4f(1,1,1,1);
  background.draw(pos.glCoords(),pos.dimension);

  glColor4f(1,1,1,0.5);
  glBindTexture(GL_TEXTURE_2D, 0);
  glVertexPointer(crop_pos.dimension, GL_INT, 0, crop_pos.glCoords());
  glDrawArrays(GL_TRIANGLE_FAN,0,4);

  text.draw();
}

void TextEdit::setActive(bool act) {
  active = act;
}

bool TextEdit::isActive() const {
  return active;
}

bool TextEdit::canBeActive() const {
  return true;
}

void TextEdit::click(int x, int y) {
  (void)x;
  (void)y;
}

void TextEdit::mouseDown(int x, int y) {
  (void)x;
  (void)y;
}

void TextEdit::mouseUp(int x, int y) {
  (void)x;
  (void)y;
}

void TextEdit::hover(int x, int y) {
  (void)x;
  (void)y;
}

void TextEdit::unHover() {

}

bool TextEdit::underMouse(int x, int y) const {
  return pos.posInRect(x,y);
}
void TextEdit::setPos(int x, int y) {
  pos.setPos(x,y);
  calcCrop();
  setCurPos(0);
  text.setPos(crop_pos.posX()+DP,crop_pos.posY());
}

int  TextEdit::posX() const {
  return pos.posX();
}

int  TextEdit::posY() const {
  return pos.posY();
}

int  TextEdit::height() const {
  return pos.height();
}

int  TextEdit::width() const {
  return pos.width();
}

void TextEdit::keyPress(int key, bool repeat, KeyboardModifier mod) {
  (void)key;
  (void)repeat;
  (void)mod;
}

void TextEdit::keyRelease(int key, KeyboardModifier mod) {
  (void)key;
  (void)mod;
}

void TextEdit::charInput(int unicode_key) {
  if ((unsigned)text.getText().size()>=max_width) {
      // TODO: Beep here
      return;
    }
  string temp_text = text.getText();
  temp_text.insert(cur_pos++,unicode_key);

  int key_wid = text.getFontMetrics().width(QChar(unicode_key));
  if (cur_world_pos+key_wid>crop_pos.getRight()-DP) {
      int dx = cur_world_pos+key_wid - (crop_pos.getRight()-DP);
      text.setPos(text.posX()-dx,text.posY());
      setCurPos(cur_pos);
    } else {
      cur_world_pos += key_wid;
    }
}
