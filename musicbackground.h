#ifndef MUSICBACKGROUND_H
#define MUSICBACKGROUND_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class MusicBackground : public QObject
{
    Q_OBJECT
public:
    explicit MusicBackground(QObject *parent = nullptr);
    
    void play(const QString &filePath);   // Start music
    void stop();                           // Stop music
    void setLoop(bool loop);               // Repeat music
    
private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    bool loopEnabled = true;
    
private slots:
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
};

#endif
