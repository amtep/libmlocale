/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libdui.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/*
 * A simple example of hiding a widget
 */

#include <DuiApplication>
#include <DuiApplicationPage>
#include <DuiApplicationWindow>
#include <DuiLabel>
#include <DuiLinearLayoutPolicy>
#include <DuiLayout>
#include <DuiTheme>
#include <DuiWidget>

int main(int argc, char **argv)
{
    DuiApplication app(argc, argv);
    DuiTheme::loadCSS("hidden_widgets.css");
    DuiApplicationWindow window;
    DuiApplicationPage page;
    /* Create a DuiLayout that we set the policy for */
    DuiLayout *layout = new DuiLayout;
    DuiLinearLayoutPolicy *policy = new DuiLinearLayoutPolicy(layout, Qt::Vertical);
    policy->setSpacing(10);

    /* Add 3 items to the policy, arranging them vertically stacked on top of each other */
    for (int i = 0; i < 3; ++i) {
        DuiLabel *label = new DuiLabel(QString("Item %1").arg(i + 1));
        policy->addItem(label);
        label->setObjectName("item");
        label->setAlignment(Qt::AlignCenter);
    }
    /* Hide the middle item manually.  Note that we must call the DuiWidget::hide() function. */
    qgraphicsitem_cast<DuiWidget *>(policy->itemAt(1)->graphicsItem())->hide();

    /* Attach the layout to the page */
    page.centralWidget()->setLayout(layout);
    page.appear();
    window.show();
    return app.exec();
}
