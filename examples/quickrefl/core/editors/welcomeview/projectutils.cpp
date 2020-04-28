// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectutils.h"
#include <cctype>
#include <mvvm/model/sessionmodel.h>

namespace
{
const std::string json_extention = ".json";
}

//! Suggests file name which can be used to store json content of given model.
//! Uses mode type: MaterialModel -> materialmodel.json

std::string ProjectUtils::SuggestFileName(const ModelView::SessionModel& model)
{
    std::string result = model.modelType();
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result + json_extention;
}

