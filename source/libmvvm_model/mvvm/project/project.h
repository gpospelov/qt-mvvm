// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECT_H
#define PROJECT_H

#include <mvvm/interfaces/projectinterface.h>
#include <functional>
#include <memory>

namespace ModelView {
class ApplicationModelsInterface;
}

//! Project represents content of all application models in a folder on disk.
//! Responsible for saving/loading application models to/from disk.

class Project : public ModelView::ProjectInterface
{
public:
    using callback_t = std::function<void()>;
    Project(ModelView::ApplicationModelsInterface* app_models, callback_t project_changed_callback = {});
    ~Project();

    std::string projectDir() const override;

    bool save(const std::string& dirname) const override;

    bool load(const std::string& dirname) override;

    bool isModified() const override;

private:
    struct ProjectImpl;
    std::unique_ptr<ProjectImpl> p_impl;
};

#endif // PROJECT_H
