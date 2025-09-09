#ifndef AttackMusic_H
#define AttackMusic_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class AttackMusic : public QObject
{
    Q_OBJECT
public:
    explicit AttackMusic(QObject *parent = nullptr);
    
    void play(const QString &filePath);   // Start music
    void stop();                           // Stop music
    void setLoop(bool loop);        // Repeat music
    void musicAttack(const QString &filepath);
    
private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    bool loopEnabled = true;
    
private slots:
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
};

#endif
