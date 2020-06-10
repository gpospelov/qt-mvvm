// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef USERINTERACTOR_H
#define USERINTERACTOR_H

#include <mvvm/project/project_types.h>
#include <string>

class QWidget;
class RecentProjectSettings;

//! Provide save/discard/cancel and similar dialogs on user request.
//! Intended to work in pair with ProjectManagerDecorator.

class UserInteractor
{
public:
    UserInteractor(QWidget* parent, RecentProjectSettings* settings);

    std::string onSelectDirRequest();

    std::string onCreateDirRequest();

    SaveChangesAnswer onSaveChangesRequest();

private:
    std::string selectDir() const;

    QWidget* m_parent{nullptr};
    RecentProjectSettings* m_settings{nullptr};
};

#endif // USERINTERACTOR_H
