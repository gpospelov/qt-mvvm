// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERTABLEWIDGET_H
#define LAYERTABLEWIDGET_H

#include "SampleTreeController.h"
#include <QWidget>
#include <memory>

class QTreeView;
class CustomModelDelegate;
class ApplicationModels;

/*!
@class LayerTableWidget
@brief Shows content of multi layer in a tree view in special "flat" form.
*/

class LayerTableWidget : public QWidget
{
public:
    explicit LayerTableWidget(ApplicationModels* models, QWidget* parent = nullptr);
    ~LayerTableWidget() override;

private:
    SampleTreeController m_controller;
    std::unique_ptr<CustomModelDelegate> m_delegate;
    QTreeView* m_sample_table;
};

#endif // LAYERTABLEWIDGET_H
