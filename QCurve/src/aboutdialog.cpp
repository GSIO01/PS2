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

#include "aboutdialog.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent)
{
  initComponents();
  m_icon = QIcon("qcurve");

  m_icon = windowIcon();
}

AboutDialog::~AboutDialog()
{ }

void AboutDialog::initComponents()
{
  QVBoxLayout* layout = new QVBoxLayout(this);

  QHBoxLayout* lyt = new QHBoxLayout();
  #ifdef Q_OS_LINUX
  QLabel* icon = new QLabel("<img src=\"/usr/share/icons/hicolor/128x128/apps/qcurve.png\" width=\"64\" height=\"64\"> </img>");
  #elif WIN32
  QLabel* icon = new QLabel("<img src=\":/hi128-app-qcurve.png\" width=\"64\" height=\"64\"> </img>");
  #endif
  icon->setFixedSize(64, 64);

  QVBoxLayout* subLyt = new QVBoxLayout();
  QLabel* progName = new QLabel(QString("<b>%1</b>").arg(tr("QCurve")));
  QLabel* versionName = new QLabel("Version 1.0");
  subLyt->addWidget(progName);
  subLyt->addWidget(versionName);
  subLyt->addStretch();

  lyt->addWidget(icon);
  lyt->addLayout(subLyt);
  lyt->addStretch();

  QWidget* about = new QWidget();
  subLyt = new  QVBoxLayout(about);
  subLyt->addWidget(new QLabel(tr("QCurve - Parametric curve viewer")));
  subLyt->addWidget(new QLabel(tr("(c) 2012-2013 QCurve team")));

  QLabel* url = new QLabel(QString("<a href=\"http://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt\">%1</a>")
  .arg(tr("License: LGPL 2.1 License")));
  url->setOpenExternalLinks(true);
  subLyt->addWidget(url);

  QWidget* authors = new QWidget();

  m_tabWgt = new QTabWidget();
  m_tabWgt->addTab(about, tr("About"));
  m_tabWgt->addTab(authors, tr("Authors"));

  layout->addLayout(lyt);
  layout->addWidget(m_tabWgt);
}