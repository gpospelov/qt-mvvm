// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef GRAPHICSOBJECTCONTROLLER_H
#define GRAPHICSOBJECTCONTROLLER_H

#include <QObject>

class GraphicsObjectController : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsObjectController(QObject *parent = nullptr);
};

#endif // GRAPHICSOBJECTCONTROLLER_H
