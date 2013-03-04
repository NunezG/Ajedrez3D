/*
 -----------------------------------------------------------------------------
 This source file is part of OGRE
 (Object-oriented Graphics Rendering Engine)
 For the latest info, see http://www.ogre3d.org/

 Copyright (c) 2000-2012 Torus Knot Software Ltd

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 -----------------------------------------------------------------------------
 */
#ifndef __SdkCameraMan_H2__
#define __SdkCameraMan_H2__

#include "Ogre.h"

#define CASILLA 1 << 0  // Mascara para el escenario
#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2
#define TABLERO 1 << 3

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
        , mZooming(false)
        , mTopSpeed(150)
        , mVelocity(Ogre::Vector3::ZERO)
        , mGoingForward(false)
        , mGoingBack(false)
        , mGoingLeft(false)
        , mGoingRight(false)
        , mGoingUp(false)
        , mGoingDown(false)
        , mFastMove(false)
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



    /*

        virtual void setStyle(CameraStyle style)
        {
            if (mStyle != CS_ORBIT && style == CS_ORBIT)
            {

                mCamera->setFixedYawAxis(true);




            }
            else if (mStyle != CS_FREELOOK && style == CS_FREELOOK)
            {
                mCamera->setAutoTracking(false);

            }


        }

*/




    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt)
    {


        std::cout << "frameRenderingQueued en INPUTMAN" << std::endl;

        //   if (mStyle == CS_FREELOOK)
        //  {
        //   std::cout << "FRAME RENDERING QUEUE" << std::endl;
        // build our acceleration vector based on keyboard input composite
        Ogre::Vector3 accel = Ogre::Vector3::ZERO;
        //        if (mGoingForward) accel += mCamera->getDirection();
        //        if (mGoingBack) accel -= mCamera->getDirection();

        if (mGoingRight) accel += mCamera->getRight();


        if (mGoingLeft) accel -= mCamera->getRight();



        //       if (mGoingUp) accel += mCamera->getUp();
        //      if (mGoingDown) accel -= mCamera->getUp();

        //        std::cout << "ACCEL: "<< accel << std::endl;




        // if accelerating, try to reach top speed in a certain time
        //     Ogre::Real topSpeed = mFastMove ? mTopSpeed * 20 : mTopSpeed;


        //  std::cout << "topSpeed: "<< topSpeed << std::endl;


        if (accel.squaredLength() != 0)
        {
            accel.normalise();
            mVelocity += accel  * mTopSpeed  * evt.timeSinceLastFrame * 10;
        }



        // if not accelerating, try to stop in a certain time
        else mVelocity -= mVelocity * evt.timeSinceLastFrame * 10;


        //    Ogre::Real tooSmall = std::numeric_limits<Ogre::Real>::epsilon();

        // keep camera velocity below top speed and above epsilon
        if (mVelocity.squaredLength() > mTopSpeed * mTopSpeed)
        {
            mVelocity.normalise();
            mVelocity *= mTopSpeed;
        }

        //    std::cout << "mVelocity squaredLength "<< mVelocity.squaredLength() << std::endl;
        //       else             if (mVelocity.squaredLength() < tooSmall * tooSmall)
        //           mVelocity = Ogre::Vector3::ZERO;

        if (mVelocity != Ogre::Vector3::ZERO) mCamera->move(mVelocity * evt.timeSinceLastFrame);
        //   }

        return true;
    }

    /*-----------------------------------------------------------------------------
        | Processes key presses for free-look style movement.
        -----------------------------------------------------------------------------*/
    virtual void injectKeyDown(const OIS::KeyEvent& evt)
    {
        // if (mStyle == CS_FREELOOK)
        //   {
        //   if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) mGoingForward = true;
        //   else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingBack = true;
        //  else
        if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT) {         //
            std::cout << "TECLA IZQUIERDA: " << std::endl;
            mGoingLeft = true;
            //   mCamera->moveRelative(Ogre::Vector3(-1,0,0));//yaw(Ogre::Degree(-1.25f));
        }
        // else
        if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT){         //
            std::cout << "TECLA DERECHA: " << std::endl;
            mGoingRight = true;


            //        mCamera->moveRelative(Ogre::Vector3(1,0,0));
            // mCamera->pitch(Ogre::Degree(1.025f));

        }

        /*  else if (evt.key == OIS::KC_PGUP) mGoingUp = true;
                else if (evt.key == OIS::KC_PGDOWN) mGoingDown = true;
                else if (evt.key == OIS::KC_LSHIFT) mFastMove = true;
              }*/
    }

    /*-----------------------------------------------------------------------------
        | Processes key releases for free-look style movement.
        -----------------------------------------------------------------------------*/
    virtual void injectKeyUp(const OIS::KeyEvent& evt)
    {
        //  if (mStyle == CS_FREELOOK)
        //   {
        //  if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) mGoingForward = false;
        //  else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingBack = false;
        // else
        if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT){   //
            mGoingLeft = false;
            // mCamera->yaw(Ogre::Degree(-10.25f));

        }

        //  else
        if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) {   //
            mGoingRight = false;
            // mCamera->pitch(Ogre::Degree(10.025f));
        }

        //  else if (evt.key == OIS::KC_PGUP) mGoingUp = false;
        //  else if (evt.key == OIS::KC_PGDOWN) mGoingDown = false;
        //  else if (evt.key == OIS::KC_LSHIFT) mFastMove = false;
        //     }
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
        //  if (mStyle == CS_ORBIT)
        //   {

        Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();
        if (mOrbiting)   // yaw around the target, and pitch locally
        {

            std::cout << "ORBITANDO!!! " << std::endl;

            mCamera->setPosition(mTarget->_getDerivedPosition());

            mCamera->yaw(Ogre::Degree(-evt.state.X.rel * 0.025f));
            // mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.025f));

            mCamera->moveRelative(Ogre::Vector3(0, 0, dist));

            // don't let the camera go over the top or around the bottom of the target
        }
        /*   else if (mZooming)  // move the camera toward or away from the target
                {
                    // the further the camera is, the faster it moves
                    mCamera->moveRelative(Ogre::Vector3(0, 0, evt.state.Y.rel * 0.004f * dist));
                }*/
        else if (evt.state.Z.rel != 0)  // move the camera toward or away from the target
        {
            // the further the camera is, the faster it moves
            mCamera->moveRelative(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.0008f * dist));
        }
        //    }

    }

    /*-----------------------------------------------------------------------------
        | Processes mouse presses. Only applies for orbit style.
        | Left button is for orbiting, and right button is for zooming.
        -----------------------------------------------------------------------------*/
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
    virtual void injectMouseDown(const OIS::MultiTouchEvent& evt)
    {
        //if (mStyle == CS_ORBIT)
        //  {
        mOrbiting = true;
        // }
    }
#else
    virtual void injectMouseDown(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
    {
        std::cout << "INJECTMOUSEDOWN " << std::endl;


        //     if (mStyle == CS_ORBIT)
        //        {


        /*   if (id == OIS::MB_Left) mOrbiting = true;
               else  if (id == OIS::MB_Right) mZooming = true;
              */ if (id == OIS::MB_Middle){
            mOrbiting = true;


        }


        // }
    }
#endif

    /*-----------------------------------------------------------------------------
        | Processes mouse releases. Only applies for orbit style.
        | Left button is for orbiting, and right button is for zooming.
        -----------------------------------------------------------------------------*/
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
    virtual void injectMouseUp(const OIS::MultiTouchEvent& evt)
    {
        //if (mStyle == CS_ORBIT)
        // {
        mOrbiting = false;
        // }
    }
#else
    virtual void injectMouseUp(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
    {
        // if (mStyle == CS_ORBIT)
        //  {

        if (id == OIS::MB_Left) mOrbiting = false;
        else if (id == OIS::MB_Right) mZooming = false;
        if (id == OIS::MB_Middle) mOrbiting = false;
        //  }
    }
#endif






protected:

    Ogre::Camera* mCamera;
    //CameraStyle mStyle;
    Ogre::SceneNode* mTarget;
    bool mOrbiting;
    bool mZooming;
    Ogre::Real mTopSpeed;
    Ogre::Vector3 mVelocity;
    bool mGoingForward;
    bool mGoingBack;
    bool mGoingLeft;
    bool mGoingRight;
    bool mGoingUp;
    bool mGoingDown;
    bool mFastMove;
    // Ogre::SceneNode *_selectedNode;
    // Ogre::RaySceneQuery *_raySceneQuery;
};
}

#endif
