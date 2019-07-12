// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include <QWidget>
#include <memory>

class SampleModel;
class ContainerEditorWidget;
class QToolBar;

/*!
@class ModelEditorWidget
@brief Shows model content as two table-like trees.

It is expected that model has two containers with demo items, left tree shows first container,
right tree the second. It is possible to drag-and-drop items between two containers.
*/

class ModelEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);

    void setModel(SampleModel* model);

private slots:
    void onUndo();
    void onRedo();

private:
    void init_toolbar();

    QToolBar* m_toolBar;
    ContainerEditorWidget* m_leftWidget;
    ContainerEditorWidget* m_rightWidget;
};

#endif // MODELEDITORWIDGET_H
