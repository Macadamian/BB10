#include "TweetPhysicsNode.h"
#include "CocosEventHandler.h"

namespace {
    QStringList TWEETS_LIST = QStringList() <<
            "What's the one moment you wish you could relive at BlackBerry Live?"<<
            "Check our Lost and Found for any items you might have left at BlackBerry Live"<<
            "Retweet if you still have your wristband from this year! #BlackBerry Live #2013"<<
            "Yuma vs. Sahara tent. Which came out on top this year?! #BlackBerry Live #2013"<<
            "RT if you're having #BlackBerry Live withdrawals! #takemeback"<<
            "It's too quiet in the desert without all of you!"<< "What did you guys think of the Sahara tent this year?"<<
            "We're loving these 360-degree videos of BlackBerry Live"<<
            "Who are you hoping will perform next year at #BlackBerry Live?"<<
            "What did you think of the @rkelly x @wearephoenix performance this year?"<<
            "Did anyone see the Chelsea Clintons perform?!"<<
            "Tell us where you spent the most time at #BlackBerry Live this year!"<<
            "Retweet if you think we keep the Yuma tent around! #BlackBerry Live"<<
            "We loved all the art! Which installation did you dig the most?"<<
            "There were so many epic performances this year! Who was your favorite?"<<
            "Who spotted Goldie from @goldenvoice at BlackBerry Live?"<<
            "Retweet if you wish you were still on the Polo Grounds. #BlackBerry Live"<<
            "Retweet if you're missing this already!"<<
            "So many memories! What was your favorite part of #BlackBerry Live?";
    // convert the timespec into milliseconds
    long time2millis(struct timespec *times)
    {
        return times->tv_sec*1000 + times->tv_nsec/1000000;
    }
}

TweetPhysicsNode::TweetPhysicsNode(CCPoint p, AroundMeLayer* layer, int randNum)
        : PhysicsNode(layer) {
    float w = 11.5, h = 2;
    b2PolygonShape polygon;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.5;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = TWEET_BOX;

    polygon.SetAsBox(w, h);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);
    bd.userData = this;
    b2Body *body = m_world->CreateBody(&bd);
    body->CreateFixture(&fixtureDef);

    setContentSize(CCSize(WORLD_TO_SCREEN(w*2), WORLD_TO_SCREEN(h*2)));
    setPosition(ccp(p.x, p.y));
    setB2Body(body);

    QString active = m_tweet = TWEETS_LIST[randNum];
    int prevSpace = 0;
    for (int i = 0; i < active.length(); i++) {
        if (active[i] == ' ') {
            prevSpace = i;
        }

        if (i == 41 && active[i] != ' ') {
            active[prevSpace] = '\n';
        }

        else if (i == 41 && active[i] == ' ') {
            active[i] = '\n';
        }
    }

    CCLabelTTF* font = CCLabelTTF::create(active.toStdString().c_str(), "Helvetica", 32, getContentSize(), kCCTextAlignmentCenter,
            kCCVerticalTextAlignmentCenter);
    font->setColor(ccc3(0x11, 0x33, 0x44));

    addChild(font);
}

TweetPhysicsNode::~TweetPhysicsNode(void) {
}

CCRect TweetPhysicsNode::rect() {
    CCSize s = getContentSize();
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);

}

void TweetPhysicsNode::touchBeganActions(CCPoint touchPoint) {
    clock_gettime(CLOCK_REALTIME, &m_time_struct);
    m_touchDownTime = time2millis(&m_time_struct);
    m_sentLongPress = false;
}

void TweetPhysicsNode::touchMovedActions(CCPoint touchPoint) {
    if(!m_sentLongPress)
    {
        clock_gettime(CLOCK_REALTIME, &m_time_struct);
        long curTime = time2millis(&m_time_struct);
        if(curTime - m_touchDownTime > 500)
        {
            CocosEventHandler::getInstance()->onTweetPress("app/native/assets/images/friends/friends_square/friend"+QString::number(rand()%11)+"_sq.png", m_tweet);
            m_sentLongPress = true;
        }
    }
}
