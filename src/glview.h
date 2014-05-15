#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>
#include <QtOpenGL>

class GLview : public QGLWidget
{
    Q_OBJECT
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
public:
    GLview(QWidget *parent = 0);
    ~GLview();
private:
    virtual void mouseDoubleClickEvent ( QMouseEvent * event );
    int  ww, hh;
    float angle;
};

#endif // GLVIEW_H
