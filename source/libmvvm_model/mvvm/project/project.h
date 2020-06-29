// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_PROJECT_H
#define MVVM_PROJECT_PROJECT_H

#include <functional>
#include <memory>
#include <mvvm/interfaces/projectinterface.h>
#include <mvvm/project/project_types.h>

namespace ModelView
{

class ApplicationModelsInterface;

//! Project represents content of all application models in a folder on disk.
//! Responsible for saving/loading application models to/from disk.

class MVVM_MODEL_EXPORT Project : public ModelView::ProjectInterface
{
public:
    using callback_t = std::function<void()>;
    Project(ModelView::ApplicationModelsInterface* app_models,
            callback_t project_changed_callback = {});

    Project(const ProjectContext& context);
    ~Project();

    std::string projectDir() const override;

    bool save(const std::string& dirname) const override;

    bool load(const std::string& dirname) override;

    bool isModified() const override;

private:
    struct ProjectImpl;
    std::unique_ptr<ProjectImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECT_H
