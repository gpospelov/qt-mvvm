// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELHASCHANGEDCONTROLLER_H
#define MODELHASCHANGEDCONTROLLER_H

#include <mvvm/signals/modellistener.h>

//! Tracks changes in the model.
//! Allows to check if model has been changed (e.g. modified, inserted or removed items) since last
//! call of ::resetChanged().

class ModelHasChangedController : public ModelView::ModelListener<ModelView::SessionModel>
{
public:
    ModelHasChangedController(ModelView::SessionModel* model);

    bool hasChanged() const;

    void resetChanged();

private:
    void process_change();
    bool has_changed{false};
};

#endif // MODELHASCHANGEDCONTROLLER_H
