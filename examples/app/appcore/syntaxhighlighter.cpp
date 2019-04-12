/****************************************************************************
**
** Copyright (C) 2010-2018 B.D. Mihai.
**
** This file is part of JSON Viewer.
**
** JSON Viewer is free software: you can redistribute it and/or modify it
** under the terms of the GNU Lesser Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** JSON Viewer is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
** or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser Public License for
** more details.
**
** You should have received a copy of the GNU Lesser Public License along
** with JSON Viewer.  If not, see http://www.gnu.org/licenses/.
**
****************************************************************************/

#include "syntaxhighlighter.h"
#include <QTextDocument>


SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
  symbolFormat.setForeground(Qt::red);
  symbolFormat.setFontWeight(QFont::Bold);

  nameFormat.setForeground(Qt::blue);
  nameFormat.setFontWeight(QFont::Bold);
  nameFormat.setFontItalic (true);

  valueFormat.setForeground(Qt::darkGreen);
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
  QString textBlock = text;

  QRegExp expression("(\\{|\\}|\\[|\\]|\\:|\\,)");
  int index = expression.indexIn(textBlock);
  while (index >= 0) {
    int length = expression.matchedLength();
    setFormat(index, length, symbolFormat);
    index = expression.indexIn(textBlock, index + length);
  }

  textBlock.replace("\\\"", "  ");

  expression = QRegExp("\".*\" *\\:");
  expression.setMinimal(true);
  index = expression.indexIn(textBlock);
  while (index >= 0) {
    int length = expression.matchedLength();
    setFormat(index, length - 1, nameFormat);
    index = expression.indexIn(textBlock, index + length);
  }

  expression = QRegExp("\\: *\".*\"");
  expression.setMinimal(true);
  index = expression.indexIn(textBlock);
  while (index >= 0) {
    int length = expression.matchedLength();
    setFormat(index + 1, length - 1, valueFormat);
    index = expression.indexIn(textBlock, index + length);
  }
}
