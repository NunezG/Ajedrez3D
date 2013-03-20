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
        , mTarget(0)
        , mTopSpeed(150)
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
        setTarget(mTarget ? mTarget : mCamera->getSceneManager()->getRootSceneNode());
        mCamera->setFixedYawAxis(true);
    }

    virtual Ogre::Camera* getCamera()
    {
        return mCamera;
    }

    /*-----------------------------------------------------------------------------
        | Sets the target we will revolve around. Only applies for orbit style.
        -----------------------------------------------------------------------------*/
    virtual void setTarget(Ogre::SceneNode* target)
    {
        if (target != mTarget)
        {
            mTarget = target;
            if(target)
            {
                setYawPitchDist(Ogre::Degree(90), Ogre::Degree(45), 110);
                mCamera->setAutoTracking(true, mTarget);
            }
            else
            {
                mCamera->setAutoTracking(false);
            }
        }
    }

    virtual Ogre::SceneNode* getTarget()
    {
        return mTarget;
    }

    virtual void distanciaCamara(int nuevaDistancia)
    {

        Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

        // the further the camera is, the faster it moves
        mCamera->moveRelative(Ogre::Vector3(0, 0, -nuevaDistancia * 0.0008f * dist));


    }



    /*-----------------------------------------------------------------------------
        | Sets the spatial offset from the target. Only applies for orbit style.
        -----------------------------------------------------------------------------*/
    virtual void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist)
    {
        mCamera->setPosition(mTarget->_getDerivedPosition());
        mCamera->setOrientation(mTarget->_getDerivedOrientation());
        mCamera->yaw(yaw);
        mCamera->pitch(-pitch);
        mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
    }

    /*-----------------------------------------------------------------------------
        | Sets the camera's top speed. Only applies for free-look style.
        -----------------------------------------------------------------------------*/
    virtual void setTopSpeed(Ogre::Real topSpeed)
    {
        mTopSpeed = topSpeed;
    }

    virtual Ogre::Real getTopSpeed()
    {
        return mTopSpeed;
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



        Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

        //Mueve la camara a la posicion central
        mCamera->setPosition(mTarget->_getDerivedPosition());
        //ANGULO Ogre::Real(120.0f) * evt.timeSinceLastFrame


        //Rota la camara

        mCamera->yaw(-angulo);




        //Devuelve la camara a su posicion ¿z? original
        // mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.025f));
        mCamera->moveRelative(Ogre::Vector3(0, 0, dist));



        //   }




        return true;
    }





protected:
    Ogre::Camera* mCamera;
    Ogre::SceneNode* mTarget;
    Ogre::Real mTopSpeed;
    Ogre::Vector3 mVelocity;

    bool mGoingUp;
    bool mGoingDown;
};
}

#endif
