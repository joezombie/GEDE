#include "MyApplication.h"



MyApplication::MyApplication(){
	_sceneManager = NULL;
	_root = NULL;
	_listener = NULL;
}

MyApplication::~MyApplication(){
	delete _root;
}

void MyApplication::loadResources() {
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

int MyApplication::startup(){
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

void MyApplication::createScene(){
	// Sinbad
	Ogre::Entity* ent = _sceneManager->createEntity("Sinbad.mesh");
	_sceneManager->getRootSceneNode()->attachObject(ent);

	// Ambient light
	_sceneManager->setAmbientLight(Ogre::ColourValue(.3f, .3f, .3f));

	// Plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
	Ogre::MeshManager::getSingleton().createPlane(
			"plane", 
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
			plane, 
			1500, 1500,
			200, 200,
			true,
			1, 5, 5,
			Ogre::Vector3::UNIT_Z
		);

	Ogre::Entity* ground = _sceneManager->createEntity("LightPlaneEntity", "plane");
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
	ground->setMaterialName("Examples/BeachStones");

	// Light
	Ogre::Light* light = _sceneManager->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, 0));

	// Shadows
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

}

void MyApplication::renderOneFrame(){
	// Forward window events
	Ogre::WindowEventUtilities::messagePump();

	// Render next frame
	_keepRunning = _root->renderOneFrame();
}

bool MyApplication::keepRunning(){
	return _keepRunning;
}