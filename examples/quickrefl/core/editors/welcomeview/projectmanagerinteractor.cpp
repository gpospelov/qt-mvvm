// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectmanagerinteractor.h"
#include "project_types.h"
#include <mvvm/project/projectutils.h>
#include "welcomeviewsettings.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <map>
#include <mvvm/utils/fileutils.h>

namespace
{
//! Map of standard Qt answeres to what ProjectManager expects.
std::map<QMessageBox::StandardButton, SaveChangesAnswer> answer_map()
{
    std::map<QMessageBox::StandardButton, SaveChangesAnswer> result = {
        {QMessageBox::Save, SaveChangesAnswer::SAVE},
        {QMessageBox::Discard, SaveChangesAnswer::DISCARD},
        {QMessageBox::Cancel, SaveChangesAnswer::CANCEL}};
    return result;
}
} // namespace

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

    qDebug() << "   onSelectDirRequest() 1.1";
    if (!ProjectUtils::IsPossibleProjectDir(dirname)) {
        qDebug() << "   onSelectDirRequest() 1.2";
        QMessageBox msgBox;
        msgBox.setText(
            "Selected directory doesn't look like a project directory, choose another one");
        msgBox.exec();
        return {};
    }

    qDebug() << "   onSelectDirRequest() 1.3" << QString::fromStdString(dirname);
    return dirname;
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
SaveChangesAnswer ProjectManagerInteractor::onSaveChangesRequest()
{
    static auto translate = answer_map();
    qDebug() << "ProjectManagerInteractor::onSaveChangesRequest()";

    QMessageBox msgBox;
    msgBox.setText("The project has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    auto ret = static_cast<QMessageBox::StandardButton>(msgBox.exec());
    return translate[ret];
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
