
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <cocos/2d/CCSprite.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);

    void move_by_left();
    void move_by_right();
    void stoped_position();

    void drop(float dt);
    cocos2d::Sprite *spaceship_object;

    bool onContactBegin(cocos2d::PhysicsContact &contact);


    cocos2d::Sprite *small_meteorite_object;
   /* cocos2d::Sprite *middle_meteorite_object;
    cocos2d::Sprite *large_meteorite_object;*/

};

#endif // __HELLOWORLD_SCENE_H__
