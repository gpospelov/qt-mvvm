// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "welcomeviewsettings.h"
#include <QDir>
#include <QSettings>

namespace
{
const QString welcome_view_group = "WelcomeView";

const QString current_wordkir_setting()
{
    return welcome_view_group + "/CurrentWorkdir";
}

} // namespace

WelcomeViewSettings::WelcomeViewSettings()
{
    readSettings();
}

WelcomeViewSettings::~WelcomeViewSettings()
{
    writeSettings();
}

//! Returns current workdir as selected by the user.
QString WelcomeViewSettings::currentWorkdir() const
{
    return m_current_workdir;
}

void WelcomeViewSettings::setCurrentWorkDir(const QString& dirname)
{
    m_current_workdir = dirname;
}

//! Write all settings to file.
void WelcomeViewSettings::writeSettings()
{
    QSettings settings;

    settings.setValue(current_wordkir_setting(), m_current_workdir);
}

//! Reads all settings from file.
void WelcomeViewSettings::readSettings()
{
    QSettings settings;
    m_current_workdir = QDir::homePath();

    if (settings.contains(current_wordkir_setting()))
        m_current_workdir = settings.value(current_wordkir_setting()).toString();
}
