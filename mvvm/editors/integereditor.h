// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_INTEGEREDITOR_H
#define MVVM_INTEGEREDITOR_H

#include "customeditor.h"

class QSpinBox;

namespace ModelView
{

//! Custom editor for QVariant based on double with scientific notation support.

class CORE_EXPORT IntegerEditor : public CustomEditor
{
public:
    explicit IntegerEditor(QWidget* parent = nullptr);

    void setRange(int minimum, int maximum);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QSpinBox* m_intEditor;
};

} // namespace ModelView

#endif // MVVM_INTEGEREDITOR_H
