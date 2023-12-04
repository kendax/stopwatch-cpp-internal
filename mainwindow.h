#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QIcon>

class Stopwatch : public QWidget {
    Q_OBJECT
public:
    explicit Stopwatch(QWidget *parent = nullptr);

private slots:
    void toggleStartPause();
    void reset();
    void updateTime();

private:
    QLabel *timeLabel;
    QPushButton *startPauseButton;
    QPushButton *resetButton;
    QTimer *timer;
    quint64 startTime;
    bool isRunning;
    int centiseconds;
    int seconds;
    int minutes;

    void displayTime();
};

#endif // WINDOW_H
