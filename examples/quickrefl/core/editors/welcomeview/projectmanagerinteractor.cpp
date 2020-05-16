// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectmanagerinteractor.h"
#include <QFileDialog>

ProjectManagerInteractor::ProjectManagerInteractor(QWidget *parent)
    : m_parent(parent)
{

}

//! Returns directory on disk selected by the user via QFileDialog.
std::string ProjectManagerInteractor::onSelectDirRequest()
{

    return {};
}


//! Returns new directory on disk created by the user via QFileDialog.
std::string ProjectManagerInteractor::onCreateDirRequest()
{
    return {};
}

//! Returns save/cancel/discard changes choice provided by the user.
int ProjectManagerInteractor::onSaveChangesRequest()
{
    return {};
}
