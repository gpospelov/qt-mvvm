// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/hostosinfo.h
//! @brief     Defines Utils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef HOSTOSINFO_H
#define HOSTOSINFO_H

#include <QString>

namespace GUI_OS_Utils {

#define QTC_WIN_EXE_SUFFIX ".exe"

enum EOsType { WINDOWS_OS, LINUX_OS, MAC_OS, OTHER_UNIX_OS, OTHER_OS };

class OsSpecificAspects
{
public:
    OsSpecificAspects(EOsType osType) : m_osType(osType) { }

    QString withExecutableSuffix(const QString &executable) const {
        QString finalName = executable;
        if (m_osType == WINDOWS_OS)
            finalName += QLatin1String(QTC_WIN_EXE_SUFFIX);
        return finalName;
    }

    Qt::CaseSensitivity fileNameCaseSensitivity() const {
        return m_osType == WINDOWS_OS ? Qt::CaseInsensitive : Qt::CaseSensitive;
    }

    QChar pathListSeparator() const {
        return QLatin1Char(m_osType == WINDOWS_OS ? ';' : ':');
    }

    Qt::KeyboardModifier controlModifier() const {
        return m_osType == MAC_OS ? Qt::MetaModifier : Qt::ControlModifier;
    }

private:
    const EOsType m_osType;
};


class HostOsInfo
{
public:

    static inline EOsType hostOs();

    enum HostArchitecture { HostArchitectureX86, HostArchitectureAMD64, HostArchitectureItanium,
                            HostArchitectureArm, HostArchitectureUnknown };
    static HostArchitecture hostArchitecture();

    static bool isWindowsHost() { return hostOs() == WINDOWS_OS; }
    static bool isLinuxHost() { return hostOs() == LINUX_OS; }
    static bool isMacHost() { return hostOs() == MAC_OS; }
    static inline bool isAnyUnixHost();

    static QString withExecutableSuffix(const QString &executable)
    {
        return hostOsAspects().withExecutableSuffix(executable);
    }

    static Qt::CaseSensitivity fileNameCaseSensitivity()
    {
        return hostOsAspects().fileNameCaseSensitivity();
    }

    static QChar pathListSeparator()
    {
        return hostOsAspects().pathListSeparator();
    }

    static Qt::KeyboardModifier controlModifier()
    {
        return hostOsAspects().controlModifier();
    }

private:
    static OsSpecificAspects hostOsAspects() { return OsSpecificAspects(hostOs()); }
};


EOsType HostOsInfo::hostOs()
{
#if defined(Q_OS_WIN)
    return WINDOWS_OS;
#elif defined(Q_OS_LINUX)
    return LINUX_OS;
#elif defined(Q_OS_MAC)
    return MAC_OS;
#elif defined(Q_OS_UNIX)
    return OTHER_UNIX_OS;
#else
    return OTHER_OS;
#endif
}

bool HostOsInfo::isAnyUnixHost()
{
#ifdef Q_OS_UNIX
    return true;
#else
    return false;
#endif
}

} // namespace Utils

#endif // HOSTOSINFO_H
