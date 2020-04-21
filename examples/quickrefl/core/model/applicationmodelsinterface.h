// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef APPLICATIONMODELSINTERFACE_H
#define APPLICATIONMODELSINTERFACE_H

#include <vector>

namespace ModelView
{
class SessionModel;
}

//! Interface to access application's model list for further manipulation.
//! Used in the context of save/load projects.

class ApplicationModelsInterface
{
public:
    //! Returns vector of models intended for saving on disk.
    virtual std::vector<ModelView::SessionModel*> persistent_models() const = 0;
};

#endif //  APPLICATIONMODELSINTERFACE_H
