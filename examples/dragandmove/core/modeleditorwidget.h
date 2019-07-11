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
@brief Shows content of the model as vertical tree, horizontal tree and table.
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
