/*
 * Calendar.hpp
 *
 *  Created on: May 9, 2013
 *      Author: Bakhshi
 */

#ifndef CALENDAR_HPP_
#define CALENDAR_HPP_

#include <QObject>
#include <bb/pim/calendar/CalendarService>
#include <QVariant>

class Calendar : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDateTime startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(QDateTime endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)
    Q_PROPERTY(QString subject READ subject WRITE setSubject NOTIFY subjectChanged)
public:
    Calendar(QObject* parent = 0);

    Q_INVOKABLE void createEvent();

    QDateTime startTime() const;
    void setStartTime(const QDateTime& startTime);

    QDateTime endTime() const;
    void setEndTime(const QDateTime& endTime);

    QString subject() const;
    void setSubject(const QString& subject);

Q_SIGNALS:
    void startTimeChanged(const QDateTime&);
    void endTimeChanged(const QDateTime&);
    void subjectChanged(const QString&);

private:
    QDateTime mStartTime;
    QDateTime mEndTime;
    QString mSubject;
};

#endif /* CALENDAR_HPP_ */
