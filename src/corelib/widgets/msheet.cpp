/***************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libmeegotouch.
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

#include "msheet.h"
#include "msheetmodel.h"
#include "msheet_p.h"
#include "mdismissevent.h"
#include <mscene.h>
#include <mscenemanager.h>
#include <mscenemanager_p.h>
#include <mwindow.h>

#include <QApplication>
#include <QCloseEvent>
#include <QTimer>

#include "mwidgetcreator.h"
M_REGISTER_WIDGET(MSheet)

#ifdef Q_WS_X11
# include <QX11Info>
# include <X11/Xatom.h>
# include <X11/Xlib.h>
#endif

//////////////////
// MSheetPrivate

MSheetPrivate::MSheetPrivate()
    : standAloneWindow(0),
    appearSystemwideDeletionPolicy(0)
{
}

MSheetPrivate::~MSheetPrivate()
{
    delete standAloneWindow;
    standAloneWindow = 0;

    delete appearSystemwideDeletionPolicy;
    appearSystemwideDeletionPolicy = 0;
}

bool MSheetPrivate::canDisappear(bool dismissing)
{
    Q_Q(MSheet);

    if (standAloneWindow && standAloneWindow->scene() == q->scene()
            && standAloneWindow->isVisible()) {

        // we are being shown systemwide and disappearance is being triggered
        // from application code (e.g. from the click of a "Cancel" button in
        // the header) instead of due to the stand alone window being hidden or
        // closed.
        //
        // For system-wide sheets we let the window manager handle our disappearance
        // animation (i.e. it will animate the stand alone window).
        // The scene window animation is not used at all and is therefore
        // denied here.

        if (dismissing) {
            standAloneWindow->close();
        } else {
            standAloneWindow->hide();
        }

        return false;
    } else {
        return true;
    }
}

bool MSheetPrivate::canDisappear()
{
    return canDisappear(false);
}

bool MSheetPrivate::canDismiss()
{
    return canDisappear(true);
}

void MSheetPrivate::_q_makeSystemSheetDisappearImmediately()
{
    Q_Q(MSheet);

    Q_ASSERT(standAloneWindow->scene() == q->scene());
    q->sceneManager()->disappearSceneWindowNow(q);
}

void MSheetPrivate::_q_dismissSystemSheetImmediately()
{
    Q_Q(MSheet);

    Q_ASSERT(standAloneWindow->scene() == q->scene());
    q->sceneManager()->dismissSceneWindowNow(q);
}

void MSheetPrivate::_q_onCentralWidgetDestroyed()
{
    Q_Q(MSheet);
    q->model()->setCentralWidget(0);
}

void MSheetPrivate::_q_onHeaderWidgetDestroyed()
{
    Q_Q(MSheet);
    q->model()->setHeaderWidget(0);
}

void MSheetPrivate::_q_onStandAloneSheetDisappeared()
{
    Q_Q(MSheet);
    Q_ASSERT(standAloneWindow != 0);
    Q_ASSERT(!standAloneWindow->isVisible());

    standAloneWindow->setSheet(0);

    q->disconnect(SIGNAL(disappeared()), q, SLOT(_q_onStandAloneSheetDisappeared()));

    // Remove sheet from scene otherwise scene will delete sheet
    // on scene's destructor

    standAloneWindow->sceneManager()->d_func()->removeSceneWindow(q);

    if (q->scene()) {
        q->scene()->removeItem(q);
    }

    if (*appearSystemwideDeletionPolicy == MSceneWindow::DestroyWhenDone
        || (*appearSystemwideDeletionPolicy == MSceneWindow::DestroyWhenDismissed && dismissed)) {

        q->deleteLater();
    }

    delete appearSystemwideDeletionPolicy;
    appearSystemwideDeletionPolicy = 0;
}

void MSheetPrivate::appearSystemwide(MSceneWindow::DeletionPolicy policy)
{
    Q_Q(MSheet);

    if (standAloneWindow == 0) {
        standAloneWindow = new MSheetStandAloneWindow;
    }

    standAloneWindow->setSheet(q);

    q->connect(q, SIGNAL(disappeared()), SLOT(_q_onStandAloneSheetDisappeared()));

    if (!appearSystemwideDeletionPolicy) {
        appearSystemwideDeletionPolicy = new MSceneWindow::DeletionPolicy;
    }
    *appearSystemwideDeletionPolicy = policy;

    standAloneWindow->sceneManager()->appearSceneWindowNow(q);
    standAloneWindow->show();
}

//////////////////
// MSheet

MSheet::MSheet() :
    MSceneWindow(new MSheetPrivate,
                 new MSheetModel,
                 MSceneWindow::Sheet, QString(""), 0)
{
}

MSheet::~MSheet()
{
    Q_D(MSheet);

    setHeaderWidget(0);
    setCentralWidget(0);

    if (d->standAloneWindow) {
        if (d->standAloneWindow->isVisible()) {
            d->standAloneWindow->setSheet(0);
            disconnect(SIGNAL(disappeared()), this, SLOT(_q_onStandAloneSheetDisappeared()));
            d->standAloneWindow->scene()->removeItem(this);
            d->standAloneWindow->close();
        }
    }
}

QGraphicsWidget *MSheet::centralWidget()
{
    return model()->centralWidget();
}

void MSheet::setCentralWidget(QGraphicsWidget *newWidget)
{
    QGraphicsWidget *oldWidget  = model()->centralWidget();

    if (newWidget == oldWidget)
        return;

    if (oldWidget)
        disconnect(oldWidget, SIGNAL(destroyed()), this, SLOT(_q_onCentralWidgetDestroyed()));

    model()->setCentralWidget(newWidget);

    delete oldWidget;

    if (newWidget)
        connect(newWidget, SIGNAL(destroyed()), SLOT(_q_onCentralWidgetDestroyed()));
}

QGraphicsWidget *MSheet::headerWidget()
{
    return model()->headerWidget();
}

void MSheet::setHeaderWidget(QGraphicsWidget *newWidget)
{
    QGraphicsWidget *oldWidget  = model()->headerWidget();

    if (newWidget == oldWidget)
        return;

    if (oldWidget)
        disconnect(oldWidget, SIGNAL(destroyed()), this, SLOT(_q_onHeaderWidgetDestroyed()));

    model()->setHeaderWidget(newWidget);

    delete oldWidget;

    if (newWidget)
        connect(newWidget, SIGNAL(destroyed()), SLOT(_q_onHeaderWidgetDestroyed()));
}

void MSheet::appearSystemwide(MSceneWindow::DeletionPolicy policy)
{
    Q_D(MSheet);
    d->appearSystemwide(policy);
}

void MSheet::setHeaderVisible(bool visible)
{
    model()->setHeaderVisible(visible);
}

bool MSheet::isHeaderVisible() const
{
    return model()->headerVisible();
}

//////////////////
// MSheetStandAloneWindow

MSheetStandAloneWindow::MSheetStandAloneWindow()
    : MWindow(new MSceneManager, 0), beingClosed(false), sheet(0)
{
    setRoundedCornersEnabled(true);
#ifdef Q_WS_X11
    appendMSheetTypeProperty();
#endif //Q_WS_X11
}

void MSheetStandAloneWindow::closeEvent(QCloseEvent *event)
{
    if (sheet) {
        MDismissEvent dismissEvent;
        QApplication::sendEvent(sheet, &dismissEvent);

        event->setAccepted(dismissEvent.isAccepted());
    } else {
        event->accept();
    }

    beingClosed = event->isAccepted();
}

void MSheetStandAloneWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    // reset variable
    beingClosed = false;
}

void MSheetStandAloneWindow::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);

    if (!sheet)
        return;

    // OBS: disappear only on the next event loop as we might be
    // called from within MSceneWindowPrivate::canDisappear()

    if (beingClosed) {
        QTimer::singleShot(0, sheet, SIGNAL(_q_dismissSystemSheetImmediately()));
    } else {
        QTimer::singleShot(0, sheet, SIGNAL(_q_makeSystemSheetDisappearImmediately()));
    }
}

#ifdef Q_WS_X11
void MSheetStandAloneWindow::appendMSheetTypeProperty()
{
    Atom atomWindowType = XInternAtom(QX11Info::display(),
                                      "_MEEGOTOUCH_NET_WM_WINDOW_TYPE_SHEET", False);

    XChangeProperty(QX11Info::display(), effectiveWinId(),
                    XInternAtom(QX11Info::display(), "_NET_WM_WINDOW_TYPE", False),
                    XA_ATOM, 32, PropModeAppend, (unsigned char*) &atomWindowType, 1);
}
#endif //Q_WS_X11

#include "moc_msheet.cpp"
