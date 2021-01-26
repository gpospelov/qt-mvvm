// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_EXTERNALPROPERTYCOMBOEDITOR_H
#define MVVM_EDITORS_EXTERNALPROPERTYCOMBOEDITOR_H

#include "mvvm/editors/customeditor.h"
#include <functional>
#include <vector>

class QComboBox;
class QStandardItemModel;

namespace ModelView {

class ExternalProperty;

//! Custom editor for table/tree cells to select ExternalProperty from the list of
//! external properties. Uses callbacks to retrieve vector of possible properties.

class MVVM_VIEWMODEL_EXPORT ExternalPropertyComboEditor : public CustomEditor {
    Q_OBJECT

public:
    using callback_t = std::function<std::vector<ModelView::ExternalProperty>()>;

    ExternalPropertyComboEditor(callback_t callback, QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected slots:
    virtual void onIndexChanged(int index);

private:
    int internIndex();
    void setConnected(bool isConnected);
    void update_components() override;

    callback_t m_getPropertiesCallback;
    QComboBox* m_box{nullptr};
    QStandardItemModel* m_comboModel{nullptr};
};

} // namespace ModelView

#endif // MVVM_EDITORS_EXTERNALPROPERTYCOMBOEDITOR_H
