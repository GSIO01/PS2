/*
 * (C) Copyright 2012-2013 QCurve Team
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

#ifndef EXPORT_DIALOG
#define EXPORT_DIALOG

#include <QtGui/QFileDialog>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>

class ExportDialog : public QFileDialog
{
  Q_OBJECT

  public:
    ExportDialog(QWidget* parent = 0);
    ~ExportDialog();

    bool showLabels() { return m_labels->isChecked(); }
    bool showGrid() { return m_grid->isChecked(); }
    bool showHelperItems() { return m_helperItems->isChecked(); }

    QString author() { return m_author->text(); }

  private:
    void extendLayout();

    QCheckBox* m_labels;
    QCheckBox* m_grid;
    QCheckBox* m_helperItems;
    QLineEdit* m_author;
};

#endif
