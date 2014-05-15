#include "glview.h"

#include <QDesktopWidget>
#include <QDebug>


GLview::GLview(QWidget *parent)
    : QGLWidget(parent)
{
    QDesktopWidget desktop;
    setWindowIcon(QIcon(":/window/pentago.ico"));
    setGeometry(
      desktop.screenGeometry().right()/2-320,
      desktop.screenGeometry().bottom()/2-240,
      640,480);

//    setMinimumSize(640,480);
    setFormat(QGLFormat(QGL::DoubleBuffer));
    setAutoBufferSwap(true);
//    qDebug() << autoBufferSwap() << doubleBuffer();
    angle = 0;
}

GLview::~GLview()
{

}

void GLview::initializeGL() {
//    glClearColor(1.0,1.0,1.0,0);

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
    glScalef(wh/100.0,wh/100.0,1);

    ww = w;
    hh = h;
}

void GLview::paintGL() {
    angle +=0.1;
    glClear(GL_COLOR_BUFFER_BIT); // чистим буфер
    glPushMatrix();
    glRotatef(angle, 0,0,1);
    glBegin(GL_POLYGON);
        glColor4f(1,0,0, 0.25);
        glVertex2f(0, 0);
        glColor4f(0,1,0, 0.25);
        glVertex2f(50, 0);
        glColor4f(0,0,1, 0.25);
        glVertex2f(100, 100);
        glColor4f(0,1,0, 0.25);
        glVertex2f(0, 50);
    glEnd();
    glColor3f(1,1,1);
    renderText(20,20,0,"Hello text!");
    glPopMatrix();
}

void GLview::mouseDoubleClickEvent ( QMouseEvent * event ) {
    setWindowState(windowState() ^ Qt::WindowFullScreen);
    event->accept();
}
