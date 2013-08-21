#include "CocosEventHandler.h"

CocosEventHandler::CocosEventHandler() {
}

CocosEventHandler* CocosEventHandler::getInstance() {
    static CocosEventHandler* ceh = new CocosEventHandler();
    return ceh;
}

void CocosEventHandler::cleanup() {
    getInstance()->deleteLater();
}

CocosEventHandler::~CocosEventHandler() {

}

void CocosEventHandler::onTweetPress(QString s, QString t)
{
    emit tweet(s, t);
}

void CocosEventHandler::onFriendStaged(QString s)
{
    emit buddy(s);
}

void CocosEventHandler::onStarStaged(QString s)
{
    emit star(s);
}

void CocosEventHandler::onStagePicked(QString s, QString t)
{
    emit stage(s, t);
}

void CocosEventHandler::resetControls()
{
    emit reset();
}
