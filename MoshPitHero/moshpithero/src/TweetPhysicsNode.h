#ifndef _Tweet_Physics_Node_H_
#define _Tweet_Physics_Node_H_

#include "PhysicsNode.h"
#include <QStringList>

class TweetPhysicsNode: public PhysicsNode {
    bool m_sentLongPress;
    QString m_tweet;
public:
    TweetPhysicsNode(CCPoint p, AroundMeLayer* layer, int randNum);
    virtual ~TweetPhysicsNode(void);

    void touchBeganActions(CCPoint touchPoint);
    void touchMovedActions(CCPoint touchPoint);
    void touchEndedActions(CCPoint touchPoint) {
    }
    void tintObj() {
    }
    void clearTint(){
    }
    void fillTweetArray(QStringList tweets);
    CCRect rect();
    void triggerCascadesControl(){
    }
};

#endif
