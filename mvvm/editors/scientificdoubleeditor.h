// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SCIENTIFICDOUBLEEDITOR_H
#define MVVM_SCIENTIFICDOUBLEEDITOR_H

#include "customeditor.h"

class QLineEdit;
class QDoubleValidator;

namespace ModelView
{

//! Custom editor for QVariant based on double with scientific notation support.

class CORE_EXPORT ScientificDoubleEditor : public CustomEditor
{
public:
    explicit ScientificDoubleEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QLineEdit* m_lineEdit;
    QDoubleValidator* m_validator;
};

} // namespace ModelView

#endif // MVVM_SCIENTIFICDOUBLEEDITOR_H
