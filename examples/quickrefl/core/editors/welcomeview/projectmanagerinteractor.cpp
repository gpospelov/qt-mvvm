// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectmanagerinteractor.h"
#include "welcomeviewsettings.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <mvvm/utils/fileutils.h>

ProjectManagerInteractor::ProjectManagerInteractor(QWidget* parent, WelcomeViewSettings* settings)
    : m_parent(parent), m_settings(settings)
{
}

//! Returns directory on disk selected by the user via QFileDialog.
std::string ProjectManagerInteractor::onSelectDirRequest()
{
    qDebug() << "ProjectManagerInteractor::onSelectDirRequest()";
    auto dirname = selectDir();

    if (dirname.empty()) // no valid selection
        return {};


    return {};
}

//! Returns new directory on disk created by the user via QFileDialog.
std::string ProjectManagerInteractor::onCreateDirRequest()
{
    qDebug() << "ProjectManagerInteractor::onCreateDirRequest()" << m_settings->currentWorkdir();
    auto dirname = selectDir();

    if (dirname.empty()) // no valid selection
        return {};

    if (!ModelView::Utils::is_empty(dirname)) {
        QMessageBox msgBox;
        msgBox.setText("The selected directory is not empty, choose another one.");
        msgBox.exec();
        return {};
    }

    return dirname;
}

//! Returns save/cancel/discard changes choice provided by the user.
int ProjectManagerInteractor::onSaveChangesRequest()
{
    qDebug() << "ProjectManagerInteractor::onSaveChangesRequest()";
    return 0;
}

//! Summon dialog to select directory on disk. If selection is not empty,
//! save parend directory for later use.

std::string ProjectManagerInteractor::selectDir() const
{
    QString dirname = QFileDialog::getExistingDirectory(
        m_parent, "Select directory", m_settings->currentWorkdir(),
        QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);

    if (!dirname.isEmpty())
        m_settings->updateWorkdirFromSelection(dirname);

    qDebug() << "       selected dir:" << dirname;

    return dirname.toStdString();
}
