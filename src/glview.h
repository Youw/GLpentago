#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>

#include "GLinterface/textures.h"
#include "GLinterface/button.h"

class GLview : public QGLWidget
{
    Q_OBJECT
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void renderBackground(Texture2D& texture);
public:
    GLview(QWidget *parent = 0);
    ~GLview();

    struct Point3D {
      GLdouble x,y,z;
    };

    static Point3D unProject(int x, int y);
private:
    virtual void keyPressEvent(QKeyEvent * e);
    virtual void mouseDoubleClickEvent ( QMouseEvent * event );
    virtual void mouseMoveEvent(QMouseEvent * event);

    int  width, height;
    Texture2D menu_background_texture;

    Button b_new_local;
    Button b_host;
    Button b_join;
    Button b_exit;


#ifdef QT_DEBUG
    float angle;
    int count;
    int m_x, m_y;
    Point3D m_w;
#endif
};

#endif // GLVIEW_H
