#include "staticpagebenchmark.h"
#include "timedemo.h"

#include <MApplication>
#include <MApplicationPage>

#include <QTimer>

namespace
{
    const int pageDuration = 3000;
}

StaticPageBenchmark::StaticPageBenchmark(MApplicationPage *applicationPage, Timedemo *timedemo, M::OrientationAngle targetOrientationAngle)
    : TimedemoBenchmark(applicationPage, timedemo)
    , targetOrientationAngle(targetOrientationAngle)
{
}

QString StaticPageBenchmark::name()
{
    return QString("StaticPageBenchmark (%1)").arg(QString::number(targetOrientationAngle));
}

void StaticPageBenchmark::start()
{
    MApplication::activeWindow()->setOrientationAngle(targetOrientationAngle);
    MApplication::activeWindow()->setOrientationAngleLocked(true);
    if (!applicationPage->isOnDisplay()) {
        connect(applicationPage, SIGNAL(appeared()), this, SLOT(stabilizeFps()));
        applicationPage->appear(MApplication::activeWindow());
        verifyAppearanceTimer->start(5000);
    } else {
        QTimer::singleShot(0, this, SLOT(stabilizeFps()));
    }
}

void StaticPageBenchmark::stabilizeFps() {
    verifyAppearanceTimer->stop();
    QTimer::singleShot(1000, this, SLOT(waitPageDuration()));
}

void StaticPageBenchmark::waitPageDuration()
{
    timedemo->startTiming(this);
    QTimer::singleShot(pageDuration, this, SLOT(terminateBenchmark()));
}

void StaticPageBenchmark::terminateBenchmark()
{
    timedemo->stopTiming(this);
    emit finished();
}
