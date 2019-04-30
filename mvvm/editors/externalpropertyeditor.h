// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_EXTERNALPROPERTYEDITOR_H
#define MVVM_EXTERNALPROPERTYEDITOR_H

#include "customeditor.h"

class QLabel;

namespace ModelView
{

class LostFocusFilter;

//! Custom editor for QVariant based on QColor.

class CORE_EXPORT ExternalPropertyEditor : public CustomEditor
{
public:
    explicit ExternalPropertyEditor(QWidget* parent = nullptr);

private slots:
    void buttonClicked();

private:
    void update_components() override;
    QLabel* m_textLabel;
    QLabel* m_pixmapLabel;
    LostFocusFilter* m_focusFilter;
};

} // namespace ModelView

#endif // MVVM_EXTERNALPROPERTYEDITOR_H
