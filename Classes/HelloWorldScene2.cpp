#include "HelloWorldScene2.h"
USING_NS_CC;

CCScene* HelloWorld2::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld2 *layer = HelloWorld2::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld2::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 20);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    CCTMXTiledMap *map=CCTMXTiledMap::create("map/map_fact.tmx");
    map->setScaleX(visibleSize.width/(map->getMapSize().width*map->getTileSize().width));
    map->setScaleY(visibleSize.height/(map->getMapSize().height*map->getTileSize().height));
    this->addChild(map,0);

	gbird = CCSprite::create("green_bird.png", CCRectMake(0,0,49,30));
	gbird->setPosition(ccp(40,visibleSize.height/2));
	this->addChild(gbird, 2);
     return true;
}



void HelloWorld2::menuCloseCallback(CCObject* pSender)
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCMoveTo* move = CCMoveTo::create(2, ccp(size.width-40, size.height/2));
	CCMoveTo* moveback = CCMoveTo::create(2, ccp(40, size.height/2));
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("green_bird.png");
	float w = texture->getContentSize().width / 2;
	float h = texture->getContentSize().height;
	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	for(int i = 0; i <2; i ++)
		animation->addSpriteFrameWithTexture(texture, CCRectMake(i * w, 0, w, h));
	CCAnimate* animate = CCAnimate::create(animation);
	gbird->runAction(CCRepeatForever::create(animate));

	CCFiniteTimeAction* flipXAction = CCFlipX::create(true);
	CCCallFuncN* end = CCCallFuncN::create(this,callfuncN_selector(HelloWorld2::moveActionEnd));
	CCAction* action = CCSequence::create(flipXAction,move, flipXAction->reverse(),moveback,end, NULL);
	gbird->runAction(action);
}

void HelloWorld2::moveActionEnd(CCNode* sender)
{
	CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	    exit(0);
	#endif
}
