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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtGui/QTabWidget>
#include <QtGui/QLabel>
#include <QtGui/QIcon>
#include <QtGui/QDialog>

/**
 * About dialog.
 */
class AboutDialog : public QDialog
{
  Q_OBJECT
  public:
    AboutDialog(QWidget* parent = 0);
    ~AboutDialog();

  private:
    void initComponents();

    QTabWidget* m_tabWgt;
    QLabel* m_progName;
    QLabel* m_progVersion;
    QLabel* m_description;

    QIcon m_icon;
};

#endif
