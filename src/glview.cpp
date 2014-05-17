#include "glview.h"

#include <QtOpenGL>
#include <QDebug>
#include "GL/glu.h"

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
}

void GLview::initializeGL() {
//    glClearColor(1.0,1.0,1.0,0);
  menu_background_texture.load(":/graphics/background.jpg",this->context());
  b_new_local = Button(256,128,512,100,"Local game",Texture2D(":/graphics/button_menu.jpg",this->context()));
  b_join = Button(256,238,512,100,"Join game",Texture2D(":/graphics/button_menu.jpg",this->context()));
  b_host = Button(256,348,512,100,"Host game",Texture2D(":/graphics/button_menu.jpg",this->context()));
  b_exit = Button(256,548,512,100,"Exit",Texture2D(":/graphics/button_menu.jpg",this->context()));  
}

void GLview::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
    int wh = std::min(w,h);
    int dx = w-wh;
    int dy = h-wh;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1 );
    glTranslatef(dx/2.0,dy/2.0,0);
    glScalef(wh/1024.0,wh/1024.0,1);
    width = w;
    height = h;
}

void GLview::paintGL() {
  glColor3f(1,1,1);
  glClear(GL_COLOR_BUFFER_BIT); // чистим буфер
  renderBackground(menu_background_texture);

  glBegin(GL_POLYGON);
    glColor4f(1,0,0, 0.25);
    glVertex2f(0, 0);
    glColor4f(0,1,0, 0.25);
    glVertex2f(512, 0);
    glColor4f(0,0,1, 0.25);
    glVertex2f(1024, 1024);
    glColor4f(0,1,0, 0.25);
    glVertex2f(0, 512);
  glEnd();

  glColor3f(1,1,1);

  b_new_local.draw();
  b_host.draw();
  b_join.draw();
  b_exit.draw();


  renderText(100,100,0.0,QString("Press and hold T or press Y %1")
#ifdef QT_DEBUG
             .arg(count)
#else
             .arg("")
#endif
             );
  glColor3f(0,0,0);
  renderText(20,20,QString("Mouse pos: X:%1 Y:%2").arg(m_x).arg(m_y));
  renderText(20,40,QString("Mouse world pos:"));
  renderText(20,50,QString("X:%1").arg(m_w.x));
  renderText(20,60,QString("Y:%1").arg(m_w.y));
  renderText(20,70,QString("Z:%1").arg(m_w.z));
}

void GLview::renderBackground(Texture2D& texture) {
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, width, height, 0, -1, 1 );
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
}

GLview::Point3D GLview::unProject(int x, int y) {
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
}

void GLview::mouseDoubleClickEvent ( QMouseEvent * event ) {
    setWindowState(windowState() ^ Qt::WindowFullScreen);
    event->accept();
}

void GLview::mouseMoveEvent(QMouseEvent* event) {
  m_x = event->pos().x();
  m_y = event->pos().y();
  m_w = unProject(m_x,m_y);
  updateGL();
}

void GLview::keyPressEvent(QKeyEvent * e)
{
#ifdef QT_DEBUG
    if(e->key() == Qt::Key_T) {
      glRotatef(angle+0.1*(count/10), 0,0,1);
      count++;
      updateGL();
    }
    if(e->key() == Qt::Key_Y) {
      count=0;
      updateGL();
    }
#endif
    if(e->key() == Qt::Key_A) {

      updateGL();
    }
    if(e->key() == Qt::Key_Z) {

      updateGL();
    }
}
