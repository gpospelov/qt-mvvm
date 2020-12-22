// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_SCIENTIFICSPINBOXEDITOR_H
#define MVVM_EDITORS_SCIENTIFICSPINBOXEDITOR_H

#include "mvvm/editors/customeditor.h"

namespace ModelView {

class ScientificSpinBox;

//! Custom editor for QVariant based on double with scientific notation support.

class MVVM_VIEWMODEL_EXPORT ScientificSpinBoxEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit ScientificSpinBoxEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);
    void setDecimals(int decimals);
    void setSingleStep(double step);

    bool is_persistent() const override;

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    ScientificSpinBox* m_doubleEditor;
};

} // namespace ModelView

#endif // MVVM_EDITORS_SCIENTIFICSPINBOXEDITOR_H
