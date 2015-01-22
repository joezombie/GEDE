#pragma once
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OIS/ois.h"

class MyFrameListener : public Ogre::FrameListener {
private:
	OIS::InputManager* _inputManager;
	OIS::Keyboard* _keyboard;
	OIS::Mouse* _mouse;
	Ogre::Camera* _cam;
	float _movementSpeed;
public:
	MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam);
	~MyFrameListener();
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

