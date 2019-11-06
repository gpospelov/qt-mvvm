// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SCIENTIFICSPINBOXEDITOR_H
#define MVVM_SCIENTIFICSPINBOXEDITOR_H

#include <mvvm/editors/customeditor.h>

namespace ModelView
{

class ScientificSpinBox;

//! Custom editor for QVariant based on double with scientific notation support.

class CORE_EXPORT ScientificSpinBoxEditor : public CustomEditor
{
public:
    explicit ScientificSpinBoxEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);
    void setDecimals(int decimals);
    void setSingleStep(double step);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    ScientificSpinBox* m_doubleEditor;
};

} // namespace ModelView

#endif // MVVM_SCIENTIFICSPINBOXEDITOR_H
