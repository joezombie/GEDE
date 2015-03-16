#include "MyFrameListener.h"


MyFrameListener::MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam){
	_cam = cam;
	_movementSpeed = 50.0f;

	OIS::ParamList parameters;
	unsigned int windowHandle = 0;
	std::ostringstream windowHandleString;

	win->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleString << windowHandle;

	parameters.insert(std::make_pair("WINDOW", windowHandleString.str()));

	_inputManager = OIS::InputManager::createInputSystem(parameters);

	_keyboard = static_cast<OIS::Keyboard*>(_inputManager->createInputObject(OIS::OISKeyboard, false));

	_mouse = static_cast<OIS::Mouse*>(_inputManager->createInputObject(OIS::OISMouse, false));
}

MyFrameListener::~MyFrameListener(){
	_inputManager->destroyInputObject(_keyboard);
	_inputManager->destroyInputObject(_mouse);
	OIS::InputManager::destroyInputSystem(_inputManager);
}

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt){
	// Keyboard
	_keyboard->capture();

	// Stop on escape key
	if (_keyboard->isKeyDown(OIS::KC_ESCAPE)){
		return false;
	}

	// Move camera with WASD
	Ogre::Vector3 translate(0, 0, 0);
	if (_keyboard->isKeyDown(OIS::KC_W)){
		translate += Ogre::Vector3(0, 0, -1);
	}
	if (_keyboard->isKeyDown(OIS::KC_S)){
		translate += Ogre::Vector3(0, 0, 1);
	}
	if (_keyboard->isKeyDown(OIS::KC_A)){
		translate += Ogre::Vector3(-1, 0, 0);
	}
	if (_keyboard->isKeyDown(OIS::KC_D)){
		translate += Ogre::Vector3(1, 0, 0);
	}
	_cam->moveRelative(translate * evt.timeSinceLastFrame * _movementSpeed);

	// Mouse
	_mouse->capture();
	// Move camera with mouse
	float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
	float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
	_cam->yaw(Ogre::Radian(rotX));
	_cam->pitch(Ogre::Radian(rotY));


	return true;
}

bool MyFrameListener::frameEnded(const Ogre::FrameEvent& evt){
	return true;
}

bool MyFrameListener::frameRenderingQueued(const Ogre::FrameEvent& evt){
	return true;
}
