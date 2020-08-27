
#include <iostream>
#include <extensions/cocos-ext.h>
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene -> getPhysicsWorld () -> setGravity(Vect(0,0));
    auto layer = HelloWorld::create();
    scene -> getPhysicsWorld() ->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init() {

    if (!Layer::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto background = Sprite::create("space.png");
    //background->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //this->addChild(background, 0);


    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::drop), 1.25f);
    this->scheduleUpdate();

    //auto armor_spaceship = AutoPolygon::generatePolygon("armor_spaceship.png");

    spaceship_object = Sprite::create("armor_spaceship.png");

        spaceship_object->setPosition(Point(visibleSize.width / 2 + origin.x + 170,
                                            visibleSize.height / 2 + origin.y + 20));

    auto rotate_start_position = RotateBy::create(0, -90);
    spaceship_object->runAction(rotate_start_position);

    this->addChild(spaceship_object, 1);


    auto pb_spaceship_object = PhysicsBody::createCircle(spaceship_object->getContentSize().width / 2);

    pb_spaceship_object->setCollisionBitmask(0x000001);
    pb_spaceship_object->setContactTestBitmask(true);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(0x000002);
    edgeBody->setContactTestBitmask(false);


    spaceship_object->setPhysicsBody(pb_spaceship_object);

    auto contactListener = EventListenerPhysicsContact::create( );
    contactListener->onContactBegin = CC_CALLBACK_1( HelloWorld::onContactBegin, this );
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( contactListener, this );




    auto edgeNode = Node::create();
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    edgeNode->setPhysicsBody( edgeBody );

    this->addChild( edgeNode );



    auto winSize = Director::getInstance()->getWinSize();




    auto button_move_right= ui::Button::create("button_right.png");
    button_move_right->setOpacity(0);

    button_move_right->setPosition(Point(visibleSize.width/2 + origin.x + 100, visibleSize.height/2 + origin.y + 80));

    button_move_right->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
                                            {
                                                switch (type)
                                                {
                                                    case cocos2d::ui::Widget::TouchEventType::BEGAN:
                                                        move_by_right();
                                                        break;
                                                    case cocos2d::ui::Widget::TouchEventType::MOVED:
                                                        move_by_right();
                                                        break;
                                                    case cocos2d::ui::Widget::TouchEventType::ENDED:
                                                        stoped_position();
                                                        break;
                                                    case cocos2d::ui::Widget::TouchEventType::CANCELED:
                                                        break;
                                                    default:
                                                        break;
                                                }
                                            });

    this->addChild(button_move_right);

    auto button_move_left = ui::Button::create("button_left.png");

    button_move_left->setOpacity(0);

    button_move_left->setPosition(Point(visibleSize.width/2 + origin.x + 100, visibleSize.height/2 + origin.y - 70));

    button_move_left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
                                  {
                                      switch (type)
                                      {
                                          case cocos2d::ui::Widget::TouchEventType::BEGAN:
                                              move_by_left();
                                              break;
                                          case cocos2d::ui::Widget::TouchEventType::MOVED:
                                              move_by_left();
                                              break;
                                          case cocos2d::ui::Widget::TouchEventType::ENDED:
                                              stoped_position();
                                              break;
                                          case cocos2d::ui::Widget::TouchEventType::CANCELED:
                                              break;
                                          default:
                                              break;
                                      }
                                  });

    this->addChild(button_move_left);
    return true;
}

void HelloWorld::drop(float dt) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    int positionY = arc4random() % 225;

    //auto small_meteorite = AutoPolygon::generatePolygon("1.png");
    small_meteorite_object = Sprite::create("1.png");

    small_meteorite_object->setPosition(Point(0, positionY));

    auto move_of_meteorite = MoveBy::create(0.003f * visibleSize.width, Point(visibleSize.width * 1.7f, 0));
    auto rotate_orbit = RotateBy::create(1.5f,360);


    auto act = Spawn::create(rotate_orbit, move_of_meteorite, nullptr);

    small_meteorite_object->runAction(act);
    this->addChild(small_meteorite_object, 1);

    auto pb_small_meteorite_object = PhysicsBody::createCircle(small_meteorite_object->getContentSize().width / 2);

    pb_small_meteorite_object->setCollisionBitmask(0x000001);
    pb_small_meteorite_object->setContactTestBitmask(true);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(0x000002);
    edgeBody->setContactTestBitmask(true);

    small_meteorite_object->setPhysicsBody(pb_small_meteorite_object);

}


void HelloWorld::move_by_left() {
    auto change_start_position = MoveBy::create(0.15f,Point(0, 8));
    spaceship_object->runAction(change_start_position);
}

void HelloWorld::stoped_position() {
    spaceship_object->setPosition(spaceship_object->getPosition().x, spaceship_object->getPosition().y);
}

void HelloWorld::move_by_right() {
    auto change_start_position = MoveBy::create(0.15f,Point(0, -8));
    spaceship_object->runAction(change_start_position);
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact &contact) {
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();

    if ( ( 0x000001 == a->getCollisionBitmask( ) && 0x000002 == b->getCollisionBitmask() ) || ( 0x000001 == b->getCollisionBitmask( ) && 0x000002 == a->getCollisionBitmask() ) )
    {
        auto scene = HelloWorld::createScene( );

        Director::getInstance( )->replaceScene( TransitionFade::create( 0.5f, scene ) );

        Director::getInstance()->end();
    }

    return true;
}
