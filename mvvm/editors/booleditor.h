// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef BOOLEDITOR_H
#define BOOLEDITOR_H

#include "customeditor.h"

class QCheckBox;

namespace ModelView
{

//! Custom editor for QVariant based on bool values.

class CORE_EXPORT BoolEditor : public CustomEditor
{
public:
    explicit BoolEditor(QWidget* parent = nullptr);

private slots:
    void onCheckBoxChange(bool value);

private:
    void update_components();
    QCheckBox* m_checkBox;
};

} // namespace ModelView

#endif // BOOLEDITOR_H
