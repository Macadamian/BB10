#ifndef COCOS_EVENT_HANDLER_H_
#define COCOS_EVENT_HANDLER_H_

#include <QObject>

class CocosEventHandler: public QObject {
Q_OBJECT

public:
    static CocosEventHandler* getInstance();

public slots:
    void cleanup();
    void onTweetPress(QString, QString);
    void onFriendStaged(QString);
    void onStarStaged(QString);
    void onStagePicked(QString, QString);
    void resetControls();

signals:
    void tweet(QString, QString);
    void buddy(QString);
    void star(QString);
    void stage(QString, QString);
    void reset();

private:
    CocosEventHandler();
    ~CocosEventHandler();
    CocosEventHandler(const CocosEventHandler &);
    CocosEventHandler& operator=(const CocosEventHandler &);
};

#endif /* CocosEventHANDLER_H_ */
