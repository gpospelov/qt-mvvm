// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TREEVIEWSCORE_SAMPLEMODEL_H
#define TREEVIEWSCORE_SAMPLEMODEL_H

#include "mvvm/model/sessionmodel.h"

namespace TreeViews {

//! Main application model.

class SampleModel : public ModelView::SessionModel {
public:
    SampleModel();

private:
    void populateModel();
};

} // namespace TreeViews

#endif // TREEVIEWSCORE_SAMPLEMODEL_H
