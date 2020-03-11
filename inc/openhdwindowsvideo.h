#if defined(ENABLE_VIDEO_RENDER)
#if defined(__windows__)

#ifndef OpenHDWindowsVideo_H
#define OpenHDWindowsVideo_H

#include <QObject>

#include <QtQml>

#include "openhdvideo.h"
#include "openhdmmalrender.h"


class OpenHDWindowsVideo : public OpenHDVideo
{
    Q_OBJECT
    Q_PROPERTY(OpenHDMMALRender *videoOut READ videoOut WRITE setVideoOut NOTIFY videoOutChanged)

public:
    OpenHDWindowsVideo(enum OpenHDStreamType stream_type = OpenHDStreamTypeMain);
    virtual ~OpenHDWindowsVideo() override;

    OpenHDMMALRender *videoOut() const;
    Q_INVOKABLE void setVideoOut(OpenHDMMALRender *videoOut);


    void start() override;
    void stop() override;
    void renderLoop() override;
    void inputLoop() override;
    void processFrame(QByteArray &nal) override;
    void processDecodedFrame(char* imageBuffer);

public slots:
    void vtdecConfigure();

signals:
    void videoOutChanged();

protected:
    QPointer<OpenHDMMALRender> m_videoOut;

private:
    quint64 m_last_time = 0;
    quint64 m_frames = 0;

};

#endif // OpenHDWindowsVideo_H

#endif
#endif
