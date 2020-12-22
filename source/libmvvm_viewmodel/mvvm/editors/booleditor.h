// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_BOOLEDITOR_H
#define MVVM_EDITORS_BOOLEDITOR_H

#include "mvvm/editors/customeditor.h"

class QCheckBox;

namespace ModelView {

//! Custom editor for QVariant based on bool values.

class MVVM_VIEWMODEL_EXPORT BoolEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit BoolEditor(QWidget* parent = nullptr);

    bool is_persistent() const override;

private slots:
    void onCheckBoxChange(bool value);

private:
    void update_components() override;
    QCheckBox* m_checkBox;
};

} // namespace ModelView

#endif // MVVM_EDITORS_BOOLEDITOR_H
