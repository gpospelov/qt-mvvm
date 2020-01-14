// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLETREECONTROLLER_H
#define SAMPLETREECONTROLLER_H

#include "LayerTableViewModel.h"
#include <QItemSelectionModel>
#include <QObject>
#include <set>

class SampleModel;
namespace ModelView
{
class SessionItem;
}

class SampleTreeController : public QObject
{
    Q_OBJECT
public:
    explicit SampleTreeController(SampleModel* model);
    ~SampleTreeController() override;

    LayerTableViewModel& viewModel() { return m_view_model; }
    QItemSelectionModel& selectionModel() { return m_selection_model; }

    void onCreateMultiLayer();
    void onCreateLayer();
    void onClone();
    void onRemove();

private:
    ModelView::SessionItem* insertSampleElement(const std::string& model_type);
    ModelView::SessionItem* findNextSibling(ModelView::SessionItem* item);
    void selectItem(ModelView::SessionItem* item);

    SampleModel* m_sample_model;
    LayerTableViewModel m_view_model;
    QItemSelectionModel m_selection_model;
};

#endif // SAMPLETREECONTROLLER_H
