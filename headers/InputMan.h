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
        , mOrbiting(false)
        , mTopSpeed(150)
        , mVelocity(Ogre::Vector3::ZERO)
        , mGoingUp(false)
        , mGoingLeft(false)
        , mGoingRight(false)
        , mGoingDown(false)
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
                setYawPitchDist(Ogre::Degree(0), Ogre::Degree(150), 125);
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

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt)
    {
        // build our acceleration vector based on keyboard input composite
        Ogre::Vector3 accel = Ogre::Vector3::ZERO;

        if (mGoingRight) accel += mCamera->getRight();

        if (mGoingLeft) accel -= mCamera->getRight();

        if (accel.squaredLength() != 0)
        {
            accel.normalise();
            mVelocity += accel  * mTopSpeed  * evt.timeSinceLastFrame * 10;
        }

        // if not accelerating, try to stop in a certain time
        else mVelocity -= mVelocity * evt.timeSinceLastFrame * 10;

        // keep camera velocity below top speed and above epsilon
        if (mVelocity.squaredLength() > mTopSpeed * mTopSpeed)
        {
            mVelocity.normalise();
            mVelocity *= mTopSpeed;
        }

        if (mVelocity != Ogre::Vector3::ZERO) mCamera->move(mVelocity * evt.timeSinceLastFrame);

        return true;
    }

    /*-----------------------------------------------------------------------------
        | Processes key presses for free-look style movement.
        -----------------------------------------------------------------------------*/
    virtual void injectKeyDown(const OIS::KeyEvent& evt)
    {

        if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT)
        {
            mGoingLeft = true;
            //   mCamera->moveRelative(Ogre::Vector3(-1,0,0));//yaw(Ogre::Degree(-1.25f));
        }

        if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT)
        {
            mGoingRight = true;

            // mCamera->moveRelative(Ogre::Vector3(1,0,0));
            // mCamera->pitch(Ogre::Degree(1.025f));
        }
    }

    /*-----------------------------------------------------------------------------
        | Processes key releases for free-look style movement.
        -----------------------------------------------------------------------------*/
    virtual void injectKeyUp(const OIS::KeyEvent& evt)
    {
        if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT)
        {
            mGoingLeft = false;
            // mCamera->yaw(Ogre::Degree(-10.25f));
        }
        if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT)
        {
            mGoingRight = false;
            // mCamera->pitch(Ogre::Degree(10.025f));
        }
    }

    /*-----------------------------------------------------------------------------
        | Processes mouse movement differently for each style.
        -----------------------------------------------------------------------------*/
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
    virtual void injectMouseMove(const OIS::MultiTouchEvent& evt)
#else
    virtual void injectMouseMove(const OIS::MouseEvent& evt)
#endif
    {
        Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();
        if (mOrbiting)   // yaw around the target, and pitch locally
        {
            mCamera->setPosition(mTarget->_getDerivedPosition());
            mCamera->yaw(Ogre::Degree(-evt.state.X.rel * 0.025f));
            // mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.025f));
            mCamera->moveRelative(Ogre::Vector3(0, 0, dist));

        }

        else if (evt.state.Z.rel != 0)  // move the camera toward or away from the target
        {
            // the further the camera is, the faster it moves
            mCamera->moveRelative(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.0008f * dist));
        }
    }

    /*-----------------------------------------------------------------------------
        | Processes mouse presses. Only applies for orbit style.
        | Left button is for orbiting, and right button is for zooming.
        -----------------------------------------------------------------------------*/
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
    virtual void injectMouseDown(const OIS::MultiTouchEvent& evt)
    {
        mOrbiting = true;
    }
#else
    virtual void injectMouseDown(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
    {
        if (id == OIS::MB_Middle){
            mOrbiting = true;
        }
    }
#endif

    /*-----------------------------------------------------------------------------
        | Processes mouse releases. Only applies for orbit style.
        | Left button is for orbiting, and right button is for zooming.
        -----------------------------------------------------------------------------*/
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
    virtual void injectMouseUp(const OIS::MultiTouchEvent& evt)
    {
        if (id == OIS::MB_Middle) mOrbiting = false;
    }
#else
    virtual void injectMouseUp(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
    {
        if (id == OIS::MB_Middle) mOrbiting = false;
    }
#endif

protected:
    Ogre::Camera* mCamera;
    Ogre::SceneNode* mTarget;
    bool mOrbiting;
    Ogre::Real mTopSpeed;
    Ogre::Vector3 mVelocity;
    bool mGoingLeft;
    bool mGoingRight;
    bool mGoingUp;
    bool mGoingDown;
};
}

#endif
