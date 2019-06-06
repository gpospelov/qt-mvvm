// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALSELECTORCELLEDITOR_H
#define MATERIALSELECTORCELLEDITOR_H

#include "customeditor.h"

class QComboBox;
class QStandardItemModel;
class MaterialModel;

namespace ModelView
{
class SessionModel;
class ExternalProperty;
} // namespace ModelView

/*!
@class MaterialSelectorCellEditor
@brief Custom editor for table cells to select material from the list of existing materials.

FIXME: move editor itself (which is combo box with colors) to separate widget independend
from model.
*/

//!


class CORE_EXPORT MaterialSelectorCellEditor : public ModelView::CustomEditor
{
public:
    explicit MaterialSelectorCellEditor(ModelView::SessionModel* model, QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected slots:
    virtual void onIndexChanged(int index);

private:
    int internIndex();
    void setConnected(bool isConnected);
    void update_components() override;
    QComboBox* m_box;
    ModelView::SessionModel* m_model;
    QStandardItemModel* m_combo_model;
};

#endif // MATERIALSELECTORCELLEDITOR_H
