#include "mainwindow.h"

Stopwatch::Stopwatch(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *bigTextLabel = new QLabel("Stopwatch", this);
    bigTextLabel->setAlignment(Qt::AlignCenter);
    QFont fontOne = bigTextLabel->font();
    fontOne.setPointSize(24);
    bigTextLabel->setFont(fontOne);
    bigTextLabel->setStyleSheet("color: blue;");
    layout->addWidget(bigTextLabel);

    // Add a spacer item to position the time label at the vertical center
    layout->addStretch();

    timeLabel = new QLabel("00:00:00", this);
    timeLabel->setAlignment(Qt::AlignCenter);
    QFont fontTwo = timeLabel->font();
    fontTwo.setPointSize(24);
    timeLabel->setFont(fontTwo);
    layout->addWidget(timeLabel);


    layout->addStretch();


    // Create a QHBoxLayout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    startPauseButton = new QPushButton("Start", this);
    connect(startPauseButton, &QPushButton::clicked, this, &Stopwatch::toggleStartPause);
    startPauseButton->setMaximumWidth(100);
    buttonLayout->addWidget(startPauseButton);

    resetButton = new QPushButton("Reset", this);
    connect(resetButton, &QPushButton::clicked, this, &Stopwatch::reset);
    resetButton->setMaximumWidth(100);
    buttonLayout->addWidget(resetButton);

    // Center-align button layout
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Add the button layout to the main layout
    layout->addLayout(buttonLayout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stopwatch::updateTime);

    reset();
}



void Stopwatch::toggleStartPause() {
    if (!isRunning) {
        isRunning = true;
        startPauseButton->setText("Pause");
        timer->start(10); // Update every 10ms (centiseconds)
        startTime = QDateTime::currentMSecsSinceEpoch() - centiseconds * 10; // Adjust start time
    } else {
        isRunning = false;
        startPauseButton->setText("Start");
        timer->stop();
    }
}

void Stopwatch::reset() {
    isRunning = false;
    startPauseButton->setText("Start");
    timer->stop();
    centiseconds = seconds = minutes = 0;
    displayTime();
}

void Stopwatch::updateTime() {
    if (isRunning) {
        centiseconds++;

        if (centiseconds == 100) {
            centiseconds = 0;
            seconds++;

            if (seconds == 60) {
                seconds = 0;
                minutes++;

                if (minutes == 60) {
                    reset(); // Stop when reaching 60 minutes
                    return;
                }
            }
        }
        displayTime();
    }
}

void Stopwatch::displayTime() {
    QString timeString = QString("%1:%2:%3")
                             .arg(minutes, 2, 10, QLatin1Char('0'))
                             .arg(seconds, 2, 10, QLatin1Char('0'))
                             .arg(centiseconds, 2, 10, QLatin1Char('0'));

    timeLabel->setText(timeString);
}
