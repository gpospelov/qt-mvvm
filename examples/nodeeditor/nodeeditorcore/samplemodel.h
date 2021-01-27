// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_SAMPLEMODEL_H
#define NODEEDITORCORE_SAMPLEMODEL_H

#include "mvvm/model/sessionmodel.h"
#include <string>

namespace NodeEditor {

//! Main application model.

class SampleModel : public ModelView::SessionModel {
public:
    SampleModel();

    void insertConnectableItem(const std::string& itemType, double xpos, double ypos);

    void loadFromFile(const std::string& name);

    void saveToFile(const std::string& name);

private:
    void populateModel();
};

} // namespace NodeEditor

#endif // NODEEDITORCORE_SAMPLEMODEL_H
