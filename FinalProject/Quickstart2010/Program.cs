using System;

using Mogre;

using Quickstart2010.Modules;
using Quickstart2010.States;

namespace Quickstart2010
{
  public class Program
  {
    //////////////////////////////////////////////////////////////////////////
    private static OgreManager mEngine;
    private static StateManager mStateMgr;

    //////////////////////////////////////////////////////////////////////////
    private Light mLight1;
    private Light mLight2;

    /************************************************************************/
    /* program starts here                                                  */
    /************************************************************************/
    [STAThread]
    static void Main()
    {
      // create Ogre manager
      mEngine = new OgreManager();

      // create state manager
      mStateMgr = new StateManager( mEngine );

      // create main program
      Program prg = new Program();

      // try to initialize Ogre and the state manager
      if( mEngine.Startup() && mStateMgr.Startup( typeof( TurningHead ) ) )
      {
        // create objects in scene
        prg.CreateScene();

        // run engine main loop until the window is closed
        while( !mEngine.Window.IsClosed )
        {
          // update the objects in the scene
          prg.UpdateScene();

          // update Ogre and render the current frame
          mEngine.Update();
        }

        // remove objects from scene
        prg.RemoveScene();
      }

      // shut down state manager
      mStateMgr.Shutdown();

      // shutdown Ogre
      mEngine.Shutdown();
    }

    /************************************************************************/
    /* constructor                                                          */
    /************************************************************************/
    public Program()
    {
      mLight1 = null;
      mLight2 = null;
    }

    /************************************************************************/
    /* create a scene to render                                             */
    /************************************************************************/
    public void CreateScene()
    {
      // set a dark ambient light
      mEngine.SceneMgr.AmbientLight = new ColourValue( 0.1f, 0.1f, 0.1f );

      // place the camera to a better position
      mEngine.Camera.Position = new Vector3( 0.0f, 25.0f, 100.0f );
      mEngine.Camera.LookAt( new Vector3() );

      // create one bright front light
      mLight1 = mEngine.SceneMgr.CreateLight( "LIGHT1" );
      mLight1.Type = Light.LightTypes.LT_POINT;
      mLight1.DiffuseColour = new ColourValue( 1.0f, 0.975f, 0.85f );
      mLight1.Position = new Vector3( -70.5f, 150.0f, 250.0f );
      mEngine.SceneMgr.RootSceneNode.AttachObject( mLight1 );

      // and a darker back light
      mLight2 = mEngine.SceneMgr.CreateLight( "LIGHT2" );
      mLight2.Type = Light.LightTypes.LT_POINT;
      mLight2.DiffuseColour = new ColourValue( 0.1f, 0.15f, 0.3f );
      mLight2.Position = new Vector3( 150.0f, 100.0f, -400.0f );
      mEngine.SceneMgr.RootSceneNode.AttachObject( mLight2 );
    }

    /************************************************************************/
    /* update objects in the scene                                          */
    /************************************************************************/
    public void UpdateScene()
    {
      // update the state manager, this will automatically update the active state
      mStateMgr.Update( 0 );
    }

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    public void RemoveScene()
    {
      // check if light 2 exists
      if( mLight2 != null )
      {
        // remove light 2 from scene and destroy it
        mEngine.SceneMgr.RootSceneNode.DetachObject( mLight2 );
        mEngine.SceneMgr.DestroyLight( mLight2 );
        mLight2 = null;
      }

      // check if light 1 exists
      if( mLight1 != null )
      {
        // remove light 1 from scene and destroy it
        mEngine.SceneMgr.RootSceneNode.DetachObject( mLight1 );
        mEngine.SceneMgr.DestroyLight( mLight1 );
        mLight1 = null;
      }
    }

  } // class

} // namespace
