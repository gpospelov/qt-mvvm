// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/project/project.h"
#include "mvvm/factories/modeldocumentfactory.h"
#include "mvvm/project/project_types.h"
#include "mvvm/project/projectchangecontroller.h"
#include "mvvm/project/projectutils.h"
#include "mvvm/utils/fileutils.h"
#include <functional>

using namespace ModelView;

struct Project::ProjectImpl {
    std::string m_project_dir;
    ProjectContext m_context;
    ProjectChangedController m_change_controller;

    ProjectImpl(const ProjectContext& context)
        : m_context(context)
        , m_change_controller(context.m_models_callback(), context.m_modified_callback)
    {
    }

    //! Returns list of models which are subject to save/load.
    std::vector<SessionModel*> models() const { return m_context.m_models_callback(); }

    //! Processes all models one by one and either save or load them to/from given directory.
    //! Template parameter `method` specifies ModelDocumentInterface's method to use.
    template <typename T> bool process(const std::string& dirname, T method)
    {
        if (!Utils::exists(dirname))
            return false;

        for (auto model : models()) {
            auto document = CreateJsonDocument({model});
            auto filename = Utils::join(dirname, ProjectUtils::SuggestFileName(*model));
            std::invoke(method, document, filename);
        }
        m_project_dir = dirname;
        m_change_controller.resetChanged();
        return true;
    }
};

Project::Project(const ProjectContext& context) : p_impl(std::make_unique<ProjectImpl>(context)) {}

Project::~Project() = default;

//! Returns the full path to a project directory. It is a name where the project has been last time
//! saved, or loaded from.

std::string Project::projectDir() const
{
    return p_impl->m_project_dir;
}

//! Saves all models to a given directory. Directory should exist.
//! Provided name will become 'projectDir'.

bool Project::save(const std::string& dirname) const
{
    return p_impl->process(dirname, &ModelDocumentInterface::save);
}

//! Loads all models from the given directory.
bool Project::load(const std::string& dirname)
{
    return p_impl->process(dirname, &ModelDocumentInterface::load);
}

bool Project::isModified() const
{
    return p_impl->m_change_controller.hasChanged();
}
