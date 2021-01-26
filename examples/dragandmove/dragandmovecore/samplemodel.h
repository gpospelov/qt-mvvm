// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DRAGANDMOVECORE_SAMPLEMODEL_H
#define DRAGANDMOVECORE_SAMPLEMODEL_H

#include "mvvm/model/sessionmodel.h"

namespace ModelView {
class SessionItem;
}

namespace DragAndMove {

//! Main application model.

class SampleModel : public ModelView::SessionModel {
public:
    SampleModel();

    void appendRandomItem(ModelView::SessionItem* container);

private:
    void populateModel();
};

} // namespace DragAndMove

#endif // DRAGANDMOVECORE_SAMPLEMODEL_H
