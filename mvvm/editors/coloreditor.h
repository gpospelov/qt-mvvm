// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COLOREDITOR_H
#define MVVM_COLOREDITOR_H

#include "customeditor.h"

class QLabel;

namespace ModelView
{

//! Custom editor for QVariant based on QColor.

class CORE_EXPORT ColorEditor : public CustomEditor
{
public:
    explicit ColorEditor(QWidget* parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event);

private:
    QColor currentColor() const;

    void update_components() override;
    QLabel* m_textLabel;
    QLabel* m_pixmapLabel;
};

} // namespace ModelView

#endif // MVVM_COLOREDITOR_H
