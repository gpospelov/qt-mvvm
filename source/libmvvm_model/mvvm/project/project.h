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

#include "mvvm/interfaces/projectinterface.h"
#include <memory>

namespace ModelView {

struct ProjectContext;

//! Project represents content of all application models in a folder on disk.
//! Responsible for saving/loading application models to/from disk.

class MVVM_MODEL_EXPORT Project : public ModelView::ProjectInterface {
public:
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
