#include "AppDelegate.h"
#include "MainScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{

}

static cocos2d::Size designResolutionSize = cocos2d::Size(1280, 1024);

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview)
    {
        glview = GLViewImpl::create("AussieTetris");
        glview->setFrameSize(designResolutionSize.width, designResolutionSize.height);
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

    auto scene = MainScene::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    
}

void AppDelegate::applicationWillEnterForeground()
{

}
