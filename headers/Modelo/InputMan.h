#ifndef __SdkCameraMan_H2__
#define __SdkCameraMan_H2__

#include "Ogre.h"

namespace InputMan
{

/*=============================================================================
    | Utility class for controlling the camera in samples.
    =============================================================================*/
class SdkCameraMan
{
public:
    SdkCameraMan(Ogre::Camera* cam)
        : mCamera(0)

        , mVelocity(Ogre::Vector3::ZERO)
        , mGoingUp(false)
        , mGoingDown(false)
        // , mCambiaTurno(false)
    {
        setCamera(cam);
    }

    virtual ~SdkCameraMan() {
    }

    /*-----------------------------------------------------------------------------
        | Swaps the camera on our camera man for another camera.
        -----------------------------------------------------------------------------*/
    virtual void setCamera(Ogre::Camera* cam)
    {
        mCamera = cam;

    }

    virtual Ogre::Camera* getCamera()
    {
        return mCamera;
    }



    virtual Ogre::SceneNode* getTarget()
    {
        //return mTarget;
    }



    /*-----------------------------------------------------------------------------
        | Sets the spatial offset from the target. Only applies for orbit style.
        -----------------------------------------------------------------------------*/


    /*-----------------------------------------------------------------------------
        | Sets the camera's top speed. Only applies for free-look style.
        -----------------------------------------------------------------------------*/
    virtual void setTopSpeed(Ogre::Real topSpeed)
    {
        //mTopSpeed = topSpeed;
    }

    virtual Ogre::Real getTopSpeed()
    {
  //      return mTopSpeed;
    }

    virtual bool rotaCamara(Ogre::Degree angulo)
    {
        // build our acceleration vector based on keyboard input composite
        // Ogre::Vector3 accel = Ogre::Vector3::ZERO;

        //   if (mGoingRight) accel += mCamera->getRight();

        //    if (mGoingLeft) accel -= mCamera->getRight();

        //   if (rotaTurno > Ogre::Real(0.0f))
        //   {
        //    std::cout << "cambiaturnorota "<< accel<< std::endl;


        //  mCambiaTurno = false;
        // accel += mCamera->getRight();

        //   accel -= mCamera->getRight();

    }

protected:
    Ogre::Camera* mCamera;
    Ogre::Vector3 mVelocity;

    bool mGoingUp;
    bool mGoingDown;
};
}

#endif
