#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>

#include "GLinterface/textures.h"
#include "GLinterface/renderobject.h"
#include "GLinterface/menu.h"

#include <vector>
#include <stack>

class GLview : public QGLWidget
{
    Q_OBJECT
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void drawBackground(Texture2D& texture);

    virtual void keyPressEvent(QKeyEvent * e) override;
    virtual void mousePressEvent ( QMouseEvent * event ) override;
    virtual void mouseReleaseEvent( QMouseEvent * event ) override;
    virtual void mouseDoubleClickEvent ( QMouseEvent * event ) override;
    virtual void mouseMoveEvent(QMouseEvent * event) override;
    virtual void enterEvent(QEvent * event) override;
    virtual void leaveEvent(QEvent * event) override;

    void mouseCoordTranslate(int x, int y);
public:
    GLview(QWidget *parent = 0);
    ~GLview();

    struct Point3D {
      GLdouble x,y,z;
    };

    static Point3D unProject(int x, int y);
private:
    int  width, height;
    Texture2D menu_background_texture;

    Menu main_menu;
    Menu menu_new_game;
    Menu menu_load_game;
    Menu menu_join_game;
    void buildMenus();

    void goMenuBack();
    void goToMenu(Menu& manu);


    std::vector<RenderObject*> current_objects;

    std::stack<std::vector<RenderObject*> > view_history;

    int m_x, m_y;//mouse window coordinates
    Point3D m_w;//mouse world coordinates

#ifdef QT_DEBUG
    float angle;
    int count;

#endif
};

#endif // GLVIEW_H
