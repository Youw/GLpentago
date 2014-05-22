#include "glview.h"

#include <QtOpenGL>
#include <QDebug>
#include <climits>

#include "GLinterface/button.h"

#if !defined(HAVE_GLES)
#include <GL/gl.h>
#include "GL/glu.h"
#else
#include <GLES/gl.h>
#endif


GLview::GLview(QWidget *parent)
    : QGLWidget(parent)
{
  setWindowIcon(QIcon(":/window/pentago.ico"));
  setMouseTracking(true);
  QDesktopWidget desktop;
  setGeometry(
    desktop.screenGeometry().right()/2-320,
    desktop.screenGeometry().bottom()/2-240,
    640,480);

#ifndef QT_DEBUG
  setMinimumSize(640,480);
#else //QT_DEBUG
  count = 0;
  angle = 0.2;
#endif

  setFormat(QGLFormat(QGL::DoubleBuffer));
  setAutoBufferSwap(true);
}

GLview::~GLview() {
  Button::texture_blurr.release();
}

void GLview::buildMenus() {
  Texture2D button_texture(":/graphics/button_menu.jpg",this->context());
  main_menu.setPos(200,150);
  main_menu.setSize(624,724);
  main_menu
      .setTexture(Texture2D(":/graphics/dots.png",this->context()))
      .addObject(Button(0,206,512,100,"New game",button_texture).setClickCallBack(
                   [&]() {
                       this->goToMenu(menu_new_game);
                   }))
      .addObject(Button(0,316,512,100,"Load game",button_texture).setClickCallBack(
                   [&]() {
                       this->goToMenu(menu_load_game);
                   }))
      .addObject(Button(0,426,512,100,"Join game",button_texture).setClickCallBack(
                   [&]() {
                       this->goToMenu(menu_join_game);
                   }))
      .addObject(Button(0,536,512,100,"Host game",button_texture))
      .addObject(Button(0,746,512,100,"Exit",button_texture).setClickCallBack(
                   [&]() {
                       this->close();
                     }));

  menu_new_game.setPos(200,260);
  menu_new_game.setSize(624,504);
  menu_new_game
      .setTexture(Texture2D(":/graphics/dots.png",this->context()))
      .addObject(Button(0,311,512,100,"One player",button_texture))
      .addObject(Button(0,421,512,100,"Two players",button_texture))
      .addObject(Button(0,631,512,100,"Back",button_texture).setClickCallBack(
                   [&]() {
                       this->goMenuBack();
                     }));

  menu_load_game.setPos(200,260);
  menu_load_game.setSize(624,504);
  menu_load_game
      .setTexture(Texture2D(":/graphics/dots.png",this->context()))
      .addObject(Button(0,311,512,100,"Autosave",button_texture))
      .addObject(Button(0,631,512,100,"Back",button_texture).setClickCallBack(
                   [&]() {
                       this->goMenuBack();
                     }));

  menu_join_game.setPos(200,260);
  menu_join_game.setSize(624,504);
  menu_join_game
      .setTexture(Texture2D(":/graphics/dots.png",this->context()))
      .addObject(Label("Enter Host IP:",0,280, QFont("Snap ITC", 32, 40, false))
                .setBackground(Texture2D(":/graphics/screwed_background.jpg",this->context()))
                )
      .addObject(Button(0,431,512,100,"Connect",button_texture))
      .addObject(Button(0,631,512,100,"Back",button_texture).setClickCallBack(
                   [&]() {
                       this->goMenuBack();
                     }));
}

void GLview::goMenuBack() {
  if(!view_history.empty()) {
    current_objects = view_history.top();
    view_history.pop();
  }
  updateGL();
}

void GLview::goToMenu(Menu& menu) {
  view_history.push(current_objects);
  current_objects.clear();
  current_objects.push_back(&menu);
  updateGL();
}

void GLview::initializeGL() {
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  Button::texture_blurr.load(":/graphics/glass_blurred.jpg",this->context());
  menu_background_texture.load(":/graphics/background.jpg",this->context());

  buildMenus();

  current_objects.push_back(&main_menu );  
}

void GLview::resizeGL(int w, int h) {
  width = w;
  height = h;
  glViewport(0,0,w,h);
#if !defined(HAVE_GLES)
  int wh = std::min(w,h);
  int dx = w-wh;
  int dy = h-wh;
  glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
//    gluPerspective(45.0f, float(w)/h, -1024.f, 2048.0f);
    glOrtho(0, w, h, 0, -1024, 1024 );
    glTranslatef(dx/2.0,dy/2.0,0);
    glScalef(wh/1024.0,wh/1024.0,1);
  glMatrixMode( GL_MODELVIEW );
//  glTranslatef(dx/2.0,dy/2.0,0);
//  glScalef(wh/1024.0,wh/1024.0,1);
//  glTranslatef(-1100.0,dy/2.0,0);
#else
    glOrthof(0, w, h, 0, -1024, 1024 );
#endif
}

void GLview::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT); // чистим буфер
  glColor4f(1,1,1,1);
  drawBackground(menu_background_texture);

//  glBegin(GL_POLYGON);
//    glColor4f(1,0,0, 0.25);
//    glVertex2f(0, 0);
//    glColor4f(0,1,0, 1);
//    glVertex2f(512, 0);
//    glColor4f(0,0,1, 0.25);
//    glVertex2f(1024, 1024);
//    glColor4f(0,1,0, 1);
//    glVertex2f(0, 512);
//  glEnd();

  //glColor3(1,1,1);

  for(auto o: current_objects) {
    o->draw();
  }

#ifdef QT_DEBUG
  glColor4f(1,1,1,1);
  renderText(100,100,0.0,QString("Press and hold T or press Y %1").arg(count));
#endif

#ifndef HAVE_GLES
  glColor4f(0.15,0.63,0.02,1);
  renderText(20,20,QString("Mouse pos: X:%1 Y:%2").arg(m_x).arg(m_y));
  renderText(20,40,QString("Mouse world pos:"));
  renderText(20,50,QString("X:%1").arg(m_w.x));
  renderText(20,60,QString("Y:%1").arg(m_w.y));
  renderText(20,70,QString("Z:%1").arg(m_w.z));
#else
    qDebug() << (const char *)glGetString(GL_VERSION) << QString("\nMouse pos: X:%1 Y:%2").arg(m_x).arg(m_y);
#endif
}

void GLview::drawBackground(Texture2D& texture) {
  glMatrixMode( GL_PROJECTION );
  glPushMatrix();
  glLoadIdentity();
#if !defined(HAVE_GLES)
  glOrtho(0, width, height, 0, -1, 1 );
#else
  glOrthof(0, width, height, 0, -1, 1 );
#endif

  float back_ratio = texture.width()/float(texture.height());
  float window_ratio = width/float(height);
  if(window_ratio>back_ratio) {
    float tmp = (window_ratio/back_ratio*height-height)/2;
    texture.draw(point(0,-tmp),point(width,height+tmp));
  } else {
    float tmp = (back_ratio/window_ratio*width-width)/2;
    texture.draw(point(-tmp,0),point(width+tmp,height));
  }
  glPopMatrix();
  glMatrixMode( GL_MODELVIEW );
}

GLview::Point3D GLview::unProject(int x, int y) {
#ifndef HAVE_GLES
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    return { posX, posY, posZ };
#else
    (void)x;
    (void)y;
    return {0,0,0};
#endif
}

void GLview::mouseCoordTranslate(int x, int y) {
  m_x = x;
  m_y = y;
  m_w = unProject(x,y);
}

void GLview::mousePressEvent ( QMouseEvent * event ) {
    mouseCoordTranslate(event->pos().x(),event->pos().y());
    for(auto o: current_objects) {
      if(o->underMouse(m_w.x,m_w.y)) {
        o->mouseDown(m_w.x,m_w.y);
      }
    }
    updateGL();
}

void GLview::mouseReleaseEvent ( QMouseEvent * event ) {
    mouseCoordTranslate(event->pos().x(),event->pos().y());
    for(auto o: current_objects) {
      o->mouseUp(m_w.x,m_w.y);
    }
    updateGL();
}

void GLview::mouseDoubleClickEvent ( QMouseEvent * event ) {
    setWindowState(windowState() ^ Qt::WindowFullScreen);
    event->accept();
}

void GLview::mouseMoveEvent(QMouseEvent* event) {
  mouseCoordTranslate(event->pos().x(),event->pos().y());
  for(auto o: current_objects) {
    if(o->underMouse(m_w.x,m_w.y)) {
      o->hover(m_w.x,m_w.y);
    } else {
      o->unHover();
    }
  }
  updateGL();
}

void GLview::enterEvent(QEvent * event) {
  updateGL();
  event->accept();
}

void GLview::leaveEvent(QEvent * event) {
  for(auto o: current_objects) {
    o->mouseUp(INT_MAX,INT_MAX);
  }
  updateGL();
  (void)event;
}



void GLview::keyPressEvent(QKeyEvent * e)
{
  for(auto o: current_objects) {
    if (o->isActive()) {
      o->keyPress(e->key(),e->isAutoRepeat(),KeyboardModifier(int(e->modifiers())));
      if(e->text().length()!=0)
        o->charInput(e->text()[0].unicode());
    }
  }
  glMatrixMode( GL_PROJECTION );
#ifdef QT_DEBUG
    if(e->key() == Qt::Key_T) {
      glRotatef(angle+0.1*(count/10), 1,1,0);
      count++;
    }
    if(e->key() == Qt::Key_Y) {
      count=0;
    }
#endif
    if(e->key() == Qt::Key_A) {
      glRotatef(0.5, 1,0,0);
    }
    if(e->key() == Qt::Key_Z) {
      glRotatef(0.5, 0,1,0);
    }
    if(e->key() == Qt::Key_Q) {
      glRotatef(0.5, 0,0,1);
    }
    glMatrixMode( GL_MODELVIEW );
    updateGL();
}

void GLview::keyReleaseEvent(QKeyEvent * e) {
    for(auto o: current_objects) {
      if (o->isActive())
        o->keyRelease(e->key(),KeyboardModifier(int(e->modifiers())));
    }
    updateGL();
}

