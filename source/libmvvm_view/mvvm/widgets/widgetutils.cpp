// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/widgets/widgetutils.h"
#include "mvvm/utils/numericutils.h"
#include <QApplication>
#include <QColor>
#include <QDir>
#include <QFontMetrics>
#include <QLabel>
#include <QMainWindow>
#include <QSize>

namespace {

//! Calculates size of letter `M` for current system font settings.

QSize FindSizeOfLetterM()
{
    QFontMetrics fontMetric(QApplication::font());
    auto em = fontMetric.horizontalAdvance('M');
    auto fontAscent = fontMetric.ascent();
    return QSize(em, fontAscent);
}

const QString untitled_name = "Untitled";

} // namespace

QColor ModelView::Utils::RandomColor()
{
    auto rndm = []() -> int { return ModelView::Utils::RandInt(0, 255); };
    return QColor(rndm(), rndm(), rndm());
}

std::string ModelView::Utils::RandomNamedColor()
{
    return RandomColor().name().toStdString();
}

bool ModelView::Utils::IsWindowsHost()
{
#if defined(Q_OS_WIN)
    return true;
#else
    return false;
#endif
}

bool ModelView::Utils::IsMacHost()
{
#if defined(Q_OS_MAC)
    return true;
#else
    return false;
#endif
}

bool ModelView::Utils::IsLinuxHost()
{
#if defined(Q_OS_LINUX)
    return true;
#else
    return false;
#endif
}

QString ModelView::Utils::WithTildeHomePath(const QString& path)
{
    if (ModelView::Utils::IsWindowsHost())
        return path;

    static const QString homePath = QDir::homePath();

    QFileInfo fi(QDir::cleanPath(path));
    QString outPath = fi.absoluteFilePath();
    if (outPath.startsWith(homePath))
        outPath = QLatin1Char('~') + outPath.mid(homePath.size());
    else
        outPath = path;
    return outPath;
}

//! Project without projectDir will be "Untitled", modified project will be "*Untitled".
//! Project with projectDir in "/home/user/project1" will get title "project1".

QString ModelView::Utils::ProjectWindowTitle(const QString& project_dir, bool is_modified)
{
    auto pos = project_dir.lastIndexOf('/');
    auto project_name = (pos == -1) ? untitled_name : project_dir.mid(pos + 1);
    auto unsaved_status = is_modified ? QString("*") : QString();
    return unsaved_status + project_name;
}

int ModelView::Utils::WidthOfLetterM()
{
    return ModelView::Utils::SizeOfLetterM().width();
}

int ModelView::Utils::HeightOfLetterM()
{
    return ModelView::Utils::SizeOfLetterM().height();
}

QSize ModelView::Utils::SizeOfLetterM()
{
    static QSize result = FindSizeOfLetterM();
    return result;
}

int ModelView::Utils::SystemPointSize()
{
    return QApplication::font().pointSize();
}

QMainWindow* ModelView::Utils::FindMainWindow()
{
    for (auto widget : qApp->topLevelWidgets()) {
        if (auto result = dynamic_cast<QMainWindow*>(widget); result)
            return result;
    }
    return nullptr;
}

QString ModelView::Utils::ClickableText(const QString& text, const QString& tag)
{
    return QString("<a href=\"%1\">%2</a>").arg(tag.isEmpty() ? text : tag, text);
}

void ModelView::Utils::ScaleLabelFont(QLabel* label, double scale)
{
    QFont font = label->font();
    font.setPointSize(ModelView::Utils::SystemPointSize() * scale);
    label->setFont(font);
}

QStringList ModelView::Utils::toStringList(const std::vector<std::string>& vec)
{
    QStringList result;
    for (const auto& x : vec)
        result.push_back(QString::fromStdString(x));
    return result;
}

std::vector<std::string> ModelView::Utils::fromStringList(const QStringList& string_list)
{
    std::vector<std::string> result;
    for (const auto& x : string_list)
        result.push_back(x.toStdString());
    return result;
}

QByteArray ModelView::Utils::serialize(const QStringList& data)
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out << data;
    return byteArray;
}

QStringList ModelView::Utils::deserialize(const QByteArray& byteArray)
{
    QByteArray array = byteArray;
    QStringList result;
    QDataStream in(&array, QIODevice::ReadOnly);
    in >> result;
    return result;
}
