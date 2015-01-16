#include "OGRE/OgreRoot.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreConfigFile.h"
#include "OGRE/OgreEntity.h"

int main(){
	Ogre::Root* root = new Ogre::Root("..\\LabFiles\\OgreConfig\\plugins_d.cfg");

	if(!root->showConfigDialog()){
		return -1;
	}

	Ogre::RenderWindow* window = root->initialise(true, "Ogre3D Beginners Guide");

	Ogre::SceneManager* sceneManager = root->createSceneManager(Ogre::ST_GENERIC);

	Ogre::Camera* camera = sceneManager->createCamera("Camera");
	camera->setPosition(Ogre::Vector3(0, 0, 30));
	camera->lookAt(Ogre::Vector3(0, 0, 0));
	camera->setNearClipDistance(5);

	Ogre::Viewport* viewport = window->addViewport(camera);
	viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));

	camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

	//Ogre::ResourceGroupManager::getSingleton().addResourceLocation("C:/OgreSDK/OgreSDK_vc10_v1-9-0/media/packs/Sinbad.zip", "Zip");
	
	
	Ogre::ConfigFile cf;
	//cf.load("..\\..\\LabFiles\\OgreConfig\\resources_d.cfg");
	
	cf.load("../LabFiles/OgreConfig/resources_t.cfg");
	Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
	Ogre::String sectionName, typeName, dataName;
	
	while(sectionIter.hasMoreElements()){
		sectionName = sectionIter.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for(i = settings->begin(); i != settings->end(); ++i){
			typeName = i->first;
			dataName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataName, typeName, sectionName);
		}
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
	Ogre::Entity* ent = sceneManager->createEntity("Sinbad.mesh");
	sceneManager->getRootSceneNode()->attachObject(ent);

	sceneManager->setAmbientLight(Ogre::ColourValue(.3f,.3f,.3f));

	root->startRendering();

	return 0;
}
