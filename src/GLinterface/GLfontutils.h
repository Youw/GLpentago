#ifndef GL_FONT_UTILS_H
#define GL_FONT_UTILS_H

#include <QtGlobal>

class QChar;
class QFont;
class QFontMetrics;
class QString;

namespace glutils
{

class TextPrivate;

class GLfont
{
public:
    GLfont(const QFont &f);
    virtual ~GLfont();

    const QFont& font() const;
    const QFontMetrics& fontMetrics() const;

    void renderText(float x, float y, const QString &text);


private:
    Q_DISABLE_COPY(GLfont)

    TextPrivate *const d;
};

} // namespace opengl


#endif // GL_FONT_UTILS_H
