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

