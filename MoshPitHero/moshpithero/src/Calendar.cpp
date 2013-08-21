/*
 * Calendar.cpp
 *
 *  Created on: May 9, 2013
 *      Author: Bakhshi
 */

#include <bb/pim/calendar/CalendarService>
#include <bb/pim/calendar/CalendarEvent>
#include <QDateTime>
#include "Calendar.hpp"

using namespace bb::pim::calendar;

Calendar::Calendar(QObject* parent) : QObject(parent)
{
    const QDate today = QDate::currentDate();
    const QTime now = QTime::currentTime();

    mStartTime = QDateTime(today, now);
    mEndTime = QDateTime(today, now.addSecs(3600));
    mSubject = "No subject";
}

void Calendar::createEvent()
{
    CalendarService calendarService;

    // create a new event
    CalendarEvent ev;
    ev.setAccountId(1);
    ev.setFolderId(1);
    ev.setStartTime(mStartTime);
    ev.setEndTime(mEndTime);
    ev.setSubject(mSubject);

    // save it to the database
    calendarService.createEvent(ev);;
}

QDateTime Calendar::startTime() const
{
    return mStartTime;
}

void Calendar::setStartTime(const QDateTime& startTime)
{
    if(startTime != mStartTime)
    {
        mStartTime = startTime;
        emit startTimeChanged(mStartTime);
    }
}


QDateTime Calendar::endTime() const
{
    return mEndTime;
}

void Calendar::setEndTime(const QDateTime& endTime)
{
    if(endTime != mEndTime)
    {
        mEndTime = endTime;
        emit endTimeChanged(mEndTime);
    }
}

QString Calendar::subject() const
{
    return mSubject;
}

void Calendar::setSubject(const QString& subject)
{
    if(subject != mSubject)
    {
        mSubject = subject;
        emit subjectChanged(mSubject);
    }
}
