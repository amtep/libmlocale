/*
 * This file was generated by m-servicefwgen
 * Command line was: m-servicefwgen -c AccessManagerProxy -p accessmanagerproxy com.nokia.widgetsgallery.AccessManager-6413.xm
 *
 * m-servicefwgen is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef ACCESSMANAGERPROXY_H_1309946720
#define ACCESSMANAGERPROXY_H_1309946720

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

#include <Qt> // for Qt::HANDLE
#include <MApplication>
#include <MWindow>

/*
 * Proxy class for interface com.nokia.widgetsgallery.AccessManager
 */
class AccessManagerProxy: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.nokia.widgetsgallery.AccessManager"; }

public:
    AccessManagerProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~AccessManagerProxy();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<bool> login(bool fullscreen, bool autofocus, int orientation, const QString &_taskTitle)
    {
        Qt::HANDLE windowId = 0;

        MWindow *win = MApplication::instance()->activeWindow();
        if (win) {
            windowId = win->effectiveWinId();
        }

        QList<QVariant> argumentList;
        argumentList << qVariantFromValue((uint)windowId);
        argumentList << qVariantFromValue(_taskTitle);
        argumentList << qVariantFromValue(fullscreen) << qVariantFromValue(autofocus) << qVariantFromValue(orientation);
        return asyncCallWithArgumentList(QLatin1String("login"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace com {
  namespace nokia {
    namespace widgetsgallery {
      typedef ::AccessManagerProxy AccessManager;
    }
  }
}
#endif
