// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALSELECTORCELLEDITOR_H
#define MATERIALSELECTORCELLEDITOR_H

#include <functional>
#include <vector>
#include <mvvm/editors/customeditor.h>

namespace ModelView {
class ExternalProperty;
}

class QComboBox;
class QStandardItemModel;

/*!
@class MaterialSelectorCellEditor
@brief Custom editor for table cells to select material from the list of existing materials.
*/

class MaterialSelectorCellEditor : public ModelView::CustomEditor
{
public:
    using callback_t = std::function<std::vector<ModelView::ExternalProperty>()>;
    explicit MaterialSelectorCellEditor(callback_t callback, QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected slots:
    virtual void onIndexChanged(int index);

private:
    int internIndex();
    void setConnected(bool isConnected);
    void update_components() override;
    callback_t get_properties;
    QComboBox* m_box;
    QStandardItemModel* m_combo_model;
};

#endif // MATERIALSELECTORCELLEDITOR_H
