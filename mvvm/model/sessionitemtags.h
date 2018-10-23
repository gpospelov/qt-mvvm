// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemTags.h
//! @brief     Defines class SessionItemTags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SESSIONITEMTAGS_H
#define SESSIONITEMTAGS_H

#include <QVector>
#include <QString>
#include <QStringList>

//! Holds all tag info for SessionItem.

class  SessionItemTags
{
public:
    bool registerTag(const QString& name, int min, int max, const QStringList& modelTypes);

    bool isValid(const QString& tagName, const QString& modelType = QString()) const;

    QStringList modelTypesForTag(const QString& tagName) const;

    int tagStartIndex(const QString& tagName) const;

    int indexFromTagRow(const QString& tagName, int row) const;
    int insertIndexFromTagRow(const QString& tagName, int row);

    QString tagFromIndex(int index) const;

    int childCount(const QString& tagName);
    int childMax(const QString& tagName);

    void addChild(const QString& tagName);
    void removeChild(const QString& tagName);

    bool isSingleItemTag(const QString& tagName);

    bool maximumReached(const QString& tagName) const;

private:
    class TagInfo
    {
    public:
        TagInfo();
        QString name;
        int min;
        int max;
        int childCount;
        QStringList modelTypes;
    };

    TagInfo& tagInfo(const QString& tagName);
    const TagInfo& tagInfo(const QString& tagName) const;

    QVector<TagInfo> m_tags;
};

#endif //  SESSIONITEMTAGS_H
