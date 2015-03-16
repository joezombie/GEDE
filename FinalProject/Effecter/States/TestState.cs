using System;

using Mogre;

using Effecter.Modules;

namespace Effecter.States {
    class TestState : State {
        //////////////////////////////////////////////////////////////////////////
        private OgreManager mEngine;

        //////////////////////////////////////////////////////////////////////////
        private SceneNode mOgreHead;
        private ParticleSystem mPartSystem;

        /************************************************************************/
        /* constructor                                                          */
        /************************************************************************/
        public TestState()
        {
          mEngine = null;
          mOgreHead = null;
          mPartSystem = null;
        }

        /************************************************************************/
        /* start up                                                             */
        /************************************************************************/
        public override bool Startup( StateManager _mgr )
        {
          // store reference to engine, this state does not need to store the state manager reference
          mEngine = _mgr.Engine;

          // create the ogre head and add the object to the current scene
          mOgreHead = mEngine.CreateSimpleObject( "Ogre", "ogrehead.mesh" );
          mEngine.AddObjectToScene( mOgreHead );

          mPartSystem = mEngine.SceneMgr.CreateParticleSystem("Examples/Smoke");
          mOgreHead.AttachObject(mPartSystem);
          // OK
          return true;
        }

        /************************************************************************/
        /* shut down                                                            */
        /************************************************************************/
        public override void Shutdown()
        {
          // check if ogre head exists
          if( mOgreHead != null )
          {
            // remove ogre head from scene and destroy it
            mEngine.RemoveObjectFromScene( mOgreHead );
            mEngine.DestroyObject( mOgreHead );
            mOgreHead = null;
          }
        }

        /************************************************************************/
        /* update                                                               */
        /************************************************************************/
        public override void Update( long _frameTime )
        {
          
        }
    }
}
