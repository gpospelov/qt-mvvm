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
#include <mvvm/core/filesystem.h>

namespace fs = std::filesystem;

namespace
{
const std::string json_extention = ".json";
}

std::string ProjectUtils::SuggestFileName(const ModelView::SessionModel& model)
{
    std::string result = model.modelType();
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result + json_extention;
}

std::vector<std::string> ProjectUtils::FindFiles(const std::string& dirname, const std::string& ext)
{
    std::vector<std::string> result;
    for (const auto& entry : fs::directory_iterator(dirname)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_regular_file() && entry.path().extension() == ext)
            result.push_back(entry.path().string());
    }
    return result;
}
