/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "glwidget.h"
#include "window.h"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    QHBoxLayout *mainLayout = new QHBoxLayout;
//    parent->layout()   /* 返回父界面的layout */
    QColor clearColor;
//    clearColor.setHsv(19, 84, 136);
    clearColor.setRgb(19, 84, 136);

    glWidgets = new GLWidget;
    glWidgets->setClearColor(clearColor);
    glWidgets->rotateBy(+42 * 16, +42 * 16, -21 * 16);
    glWidgets->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->setAlignment(parent, Qt::AlignCenter);

    mainLayout->addWidget(glWidgets);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    currentGlWidget = glWidgets;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Window::rotateOneStep);
//    timer->start(30);

    int wd = parent->width();
    int ht = parent->height();
    move( (wd - width()) * 0.85, (ht-height()) * 0.3 );
    resize(600, 500);
}

Window::~Window()
{
    delete glWidgets;
    delete timer;
}

void Window::rotateOneStep()
{
//    qDebug() <<" is rotateOneStep ";

    if (currentGlWidget)
        currentGlWidget->rotateBy(+2 * 16, +2 * 16, -1 * 16);
}
