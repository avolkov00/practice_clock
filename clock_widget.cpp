#include <clock_widget.h>

#include <QPainter>
#include <QTime>
#include <iostream>

Clock::Clock(QWidget* parent)
	: QWidget(parent)
	, _hours(0)
	, _minutes(0)
	, _seconds(0)
{
	setMinimumSize(100,100);
	startTimer(1000);
}

void Clock::timerEvent(QTimerEvent*)
{
	QTime t  = QTime::currentTime();
	_hours   = t.hour();
	_minutes = t.minute();
	_seconds = t.second();

	update();
	std::cout << "Tick: " 
	<< _hours 
	<< ":" << _minutes 
	<< ":" << _seconds
	<< std::endl;
}


void drawArrow(QPainter& p)
{
    p.drawLine(0,0,  0,10);
}

void Clock::paintEvent(QPaintEvent*)
{
	QPainter p(this);
	QPoint center(width()/2, height()/2);
	p.translate(center);
    QPainter h(this);
    h.drawEllipse(width()/2-220, height()/2-220,440,440);
    for(int i = 0;i < 12;i++){
        p.save();
        p.rotate(180+i*30);
        p.drawLine(0, 210,0,225);
        p.restore();
    }
    for(int i = 0;i<12;i++){
        p.save();
        p.rotate(180+(i+1)*30);
        if((i+1)*5 == 60)
        {
             p.drawText(-6,207,"0");
        }
        else
            p.drawText(-6,207,QString::number(((i+1)*5)));
        p.drawText(-6,195,QString::number(i+1));
        p.restore();
    }

    // hours
    p.save();
    p.rotate(180 + _hours * 30);
    p.scale(7,10);
    p.setPen(Qt::black);
    drawArrow(p);
    p.restore();
  // minutes
    p.save();
    p.rotate( 180 + _minutes * 6);
    p.scale(4.5,18);
    //p.setPen(Qt::green);
    drawArrow(p);
    p.restore();

  // seconds
    p.save();
    p.rotate( 180 + _seconds * 6);
    p.scale(3,20);
    //p.setPen(Qt::blue);
    drawArrow(p);
    p.restore();
}

