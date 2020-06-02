// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <functional>
#include <mvvm/core/modeldocuments.h>
#include <mvvm/interfaces/applicationmodelsinterface.h>
#include <mvvm/project/project.h>
#include <mvvm/project/projectchangecontroller.h>
#include <mvvm/project/projectutils.h>
#include <mvvm/utils/fileutils.h>

struct ModelView::Project::ProjectImpl {
    ModelView::ApplicationModelsInterface* app_models{nullptr};
    std::string project_dir;
    ProjectChangedController change_controller;

    ProjectImpl(ModelView::ApplicationModelsInterface* app_models, callback_t callback)
        : app_models(app_models), change_controller(app_models->persistent_models(), callback)
    {
    }

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
        change_controller.resetChanged();
        return true;
    }
};

ModelView::Project::Project(ModelView::ApplicationModelsInterface* app_models,
                            callback_t project_changed_callback)
    : p_impl(std::make_unique<ProjectImpl>(app_models, project_changed_callback))
{
}

ModelView::Project::~Project() = default;

std::string ModelView::Project::projectDir() const
{
    return p_impl->project_dir;
}

//! Saves all models to a given directory. Directory should exist.
//! Provided name will become 'projectDir'.

bool ModelView::Project::save(const std::string& dirname) const
{
    return p_impl->process(dirname, &ModelView::ModelDocumentInterface::save);
}

//! Loads all models from the given directory.
bool ModelView::Project::load(const std::string& dirname)
{
    return p_impl->process(dirname, &ModelView::ModelDocumentInterface::load);
}

bool ModelView::Project::isModified() const
{
    return p_impl->change_controller.hasChanged();
}
