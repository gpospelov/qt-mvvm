// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_DOUBLEEDITOR_H
#define MVVM_EDITORS_DOUBLEEDITOR_H

#include "mvvm/editors/customeditor.h"

class QDoubleSpinBox;

namespace ModelView {

//! Custom editor for QVariant based on double with possibility to set limits.

class MVVM_VIEWMODEL_EXPORT DoubleEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit DoubleEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);

    void setDecimals(int decimals);

    void setSingleStep(double value);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QDoubleSpinBox* m_doubleEditor;
};

} // namespace ModelView

#endif // MVVM_EDITORS_DOUBLEEDITOR_H
