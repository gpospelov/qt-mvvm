// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "project.h"
#include "applicationmodelsinterface.h"
#include "projectutils.h"
#include <filesystem>
#include <mvvm/core/modeldocuments.h>

struct Project::ProjectImpl {
    ApplicationModelsInterface* app_models{nullptr};
    ProjectImpl(ApplicationModelsInterface* app_models) : app_models(app_models) {}

    //! Returns list of models which are subject to save/load.
    std::vector<ModelView::SessionModel*> models() const { return app_models->persistent_models(); }
};

Project::Project(ApplicationModelsInterface* app_models)
    : p_impl(std::make_unique<ProjectImpl>(app_models))
{
}

Project::~Project() = default;

bool Project::save(const std::string& dirname) const
{
    std::filesystem::path outputdir(dirname);
    if (!std::filesystem::exists(outputdir))
        return false;

    for (auto model : p_impl->models()) {
        auto document = ModelView::CreateJsonDocument({model});
        std::filesystem::path filename = outputdir / ProjectUtils::SuggestFileName(*model);
        document->save(filename.string());
    }
    return true;
}

bool Project::load(const std::string& dirname)
{
    return true;
}
