#if defined(ENABLE_VIDEO_RENDER)
#if defined(__windows__)

#include <QtConcurrent>
#include <QtQuick>
#include <QThread>
#include <QtConcurrent>
#include <QFuture>

#include "openhdwindowsvideo.h"
#include "openhdmmalrender.h"
#include "constants.h"
#include "localmessage.h"

#include "sharedqueue.h"

using namespace std::chrono;


OpenHDWindowsVideo::OpenHDWindowsVideo(enum OpenHDStreamType stream_type): OpenHDVideo(stream_type) {
    qDebug() << "OpenHDWindowsVideo::OpenHDWindowsVideo()";
    connect(this, &OpenHDWindowsVideo::configure, this, &OpenHDWindowsVideo::vtdecConfigure, Qt::DirectConnection);
}


OpenHDWindowsVideo::~OpenHDWindowsVideo() {
    qDebug() << "~OpenHDWindowsVideo()";
}


void OpenHDWindowsVideo::start() {
    // nothing needed
}


void OpenHDWindowsVideo::stop() {

}


OpenHDMMALRender* OpenHDWindowsVideo::videoOut() const {
    return m_videoOut;
}


void OpenHDWindowsVideo::setVideoOut(OpenHDMMALRender *videoOut) {
    qDebug() << "OpenHDWindowsVideo::setVideoOut(" << videoOut << ")";

    if (m_videoOut == videoOut) {
        return;
    }

    if (m_videoOut) {
        //m_videoOut->disconnect(this);
    }

    m_videoOut = videoOut;

    emit videoOutChanged();
}


void OpenHDWindowsVideo::vtdecConfigure() {
    auto t = QThread::currentThread();

    qDebug() << "OpenHDWindowsVideo::vtdecConfigure()";
    qDebug() << t;

    isConfigured = true;

    QThread::msleep(100);



    // the pi decoder hardware always gives us this format, so we hardcode it
    m_videoOut->setFormat(width, height, QVideoFrame::PixelFormat::Format_YUV420P);
}


void OpenHDWindowsVideo::inputLoop() {

}


void OpenHDWindowsVideo::processFrame(QByteArray &nal) {

}


void OpenHDWindowsVideo::processDecodedFrame(char* imageBuffer) {
    if (m_videoOut) {
        m_videoOut->paintFrame(imageBuffer);
    }
}

void OpenHDWindowsVideo::renderLoop() {

}

#endif
#endif
