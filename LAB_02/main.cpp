#include "OGRE/OgreRoot.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreConfigFile.h"
#include "OGRE/OgreEntity.h"
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
	MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam){
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

	~MyFrameListener(){
		_inputManager->destroyInputObject(_keyboard);
		_inputManager->destroyInputObject(_mouse);
		OIS::InputManager::destroyInputSystem(_inputManager);
	}

	bool frameStarted(const Ogre::FrameEvent& evt){
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

	bool frameEnded(const Ogre::FrameEvent& evt){
		return true;
	}

	bool frameRenderingQueued(const Ogre::FrameEvent& evt){
		return true;
	}
};

class MyApplication {
private:
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	MyFrameListener* _listener;
	bool _keepRunning;

public:
	MyApplication(){
		_sceneManager = NULL;
		_root = NULL;
		_listener = NULL;
	}

	~MyApplication(){
		delete _root;
	}

	void loadResources() {
		Ogre::ConfigFile cf;
		cf.load("../LabFiles/OgreConfig/resources_d.cfg");

		Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
		Ogre::String sectionName, typeName, dataName;

		while (sectionIter.hasMoreElements()){
			sectionName = sectionIter.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;

			for (i = settings->begin(); i != settings->end(); ++i){
				typeName = i->first;
				dataName = i->second;

				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataName, typeName, sectionName);
			}
		}

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	int startup(){
		_root = new Ogre::Root("../LabFiles/OgreConfig/plugins_d.cfg");
		
		if (!_root->showConfigDialog()){
			return -1;
		}

		Ogre::RenderWindow* window = _root->initialise(true, "GEDE LAB_02 JohannesH10@ru.is");

		_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);

		Ogre::Camera* camera = _sceneManager->createCamera("Camera");
		camera->setPosition(Ogre::Vector3(0, 0, 50));
		camera->lookAt(Ogre::Vector3(0, 0, 0));
		camera->setNearClipDistance(5);

		Ogre::Viewport* viewport = window->addViewport(camera);
		viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
		camera->setAspectRatio(Ogre::Real(viewport->getActualWidth() / Ogre::Real(viewport->getActualHeight())));

		_listener = new MyFrameListener(window, camera);
		_root->addFrameListener(_listener);

		loadResources();
		createScene();

		//_root->startRendering();

		return 0;
	}

	void createScene(){
		Ogre::Entity* ent = _sceneManager->createEntity("Sinbad.mesh");
		_sceneManager->getRootSceneNode()->attachObject(ent);

		_sceneManager->setAmbientLight(Ogre::ColourValue(.3f, .3f, .3f));
	}

	void renderOneFrame(){
		Ogre::WindowEventUtilities::messagePump();
		_keepRunning = _root->renderOneFrame();
	}

	bool keepRunning(){
		return _keepRunning;
	}
};


int main() {
	MyApplication app;
	app.startup();

	while (app.keepRunning()){
		app.renderOneFrame();
	}

	return 0;
}