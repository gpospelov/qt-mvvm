// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_SELECTABLECOMBOBOX_H
#define MVVM_EDITORS_SELECTABLECOMBOBOX_H

#include <QWidget>
#include <mvvm/viewmodel_export.h>

namespace ModelView
{

//! Adds multi-selection capabilities to QComboBox.

class MVVM_VIEWMODEL_EXPORT SelectableComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit SelectableComboBox(QWidget* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_EDITORS_SELECTABLECOMBOBOX_H
