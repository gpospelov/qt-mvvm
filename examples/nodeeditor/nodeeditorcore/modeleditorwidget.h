// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include <QWidget>
#include <memory>

namespace NodeEditor {

class SampleModel;

//! Shows content of the model as vertical tree, horizontal tree and table.

class ModelEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);
    void setModel(SampleModel* model);
};

} // namespace NodeEditor

#endif // MODELEDITORWIDGET_H
