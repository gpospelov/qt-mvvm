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
#include <functional>
#include <mvvm/core/modeldocuments.h>
#include <mvvm/utils/fileutils.h>

struct Project::ProjectImpl {
    ApplicationModelsInterface* app_models{nullptr};    
    std::string project_dir;

    ProjectImpl(ApplicationModelsInterface* app_models) : app_models(app_models) {}

    //! Returns list of models which are subject to save/load.
    std::vector<ModelView::SessionModel*> models() const { return app_models->persistent_models(); }

    //! Processes all models one by one and either save or load them to/from given directory.
    //! Template parameter `method` specifies ModelDocumentInterface's method to use.
    template <typename T> bool process(const std::string& dirname, T method)
    {
        if (!ModelView::Utils::exists(dirname))
            return false;

        for (auto model : models()) {
            auto document = ModelView::CreateJsonDocument({model});
            auto filename = ModelView::Utils::join(dirname, ProjectUtils::SuggestFileName(*model));
            std::invoke(method, document, filename);
        }
        project_dir = dirname;
        return true;
    }
};

Project::Project(ApplicationModelsInterface* app_models)
    : p_impl(std::make_unique<ProjectImpl>(app_models))
{
}

std::string Project::projectDir() const
{
    return p_impl->project_dir;
}

Project::~Project() = default;

//! Saves all models to given directory.
bool Project::save(const std::string& dirname) const
{
    return p_impl->process(dirname, &ModelView::ModelDocumentInterface::save);
}

//! Loads all models from the given directory.
bool Project::load(const std::string& dirname)
{
    return p_impl->process(dirname, &ModelView::ModelDocumentInterface::load);
}
