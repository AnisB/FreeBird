/*************** <auto-copyright.pl BEGIN do not edit this line> **************
  *
  * VR Juggler is (C) Copyright 1998-2005 by Iowa State University
  *
  * Original Authors:
  *   Allen Bierbaum, Christopher Just,
  *   Patrick Hartling, Kevin Meinert,
  *   Carolina Cruz-Neira, Albert Baker
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Library General Public
  * License as published by the Free Software Foundation; either
  * version 2 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Library General Public License for more details.
  *
  * You should have received a copy of the GNU Library General Public
  * License along with this library; if not, write to the
  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
  * Boston, MA 02111-1307, USA.
  *
  * -----------------------------------------------------------------
  * File:          $RCSfile$
  * Date modified: $Date: 2006-11-14 13:22:08 -0600 (Tue, 14 Nov 2006) $
  * Version:       $Revision: 19509 $
  * -----------------------------------------------------------------
  *
  *************** <auto-copyright.pl END do not edit this line> ***************/
 
 #ifndef _VRJ_OSG_APP_H_
 #define _VRJ_OSG_APP_H_
 
 #include <vrj/vrjConfig.h>
 
 #include <vrj/Draw/OGL/GlApp.h>
 #include <vrj/Draw/OGL/GlContextData.h>
 #include <vrj/Draw/OGL/GlWindow.h>
 
 #include <vrj/Display/CameraProjection.h>
 
 #include <osg/Vec3>
 #include <osg/Matrix>
 #include <osg/Transform>
 #include <osg/Group>
 
 #include <osgUtil/SceneView>
 #include <osgUtil/UpdateVisitor>
 
 
 namespace vrj
 {
 
 class OsgApp : public GlApp
 {
 public:
    OsgApp(Kernel* kern = NULL)
       : GlApp(kern)
       , mFrameNumber(0)
    {
       ;
    }
 
    virtual ~OsgApp()
    {
       ;
    }
 
    virtual void initScene() = 0;
 
    virtual osg::Group* getScene() = 0;
 
    virtual void configSceneView(osgUtil::SceneView* newSceneViewer)
    {
       newSceneViewer->setDefaults();
       newSceneViewer->init();
       newSceneViewer->setClearColor(osg::Vec4(0.0f, 0.0f, 0.0f, 0.0f));
 
       // Needed for stereo to work.
       newSceneViewer->setDrawBufferValue(GL_NONE);
    }
 
    virtual void latePreFrame()
    {
       update();
    }
 
    virtual void draw();
 
    virtual void init()
    {
       mUpdateVisitor = new osgUtil::UpdateVisitor();
       mFrameStamp    = new osg::FrameStamp();
       mUpdateVisitor->setFrameStamp(mFrameStamp.get());
 
       GlApp::init();
 
       mHead.init("VJHead");
 
       //Create the scene
       this->initScene();
    }
 
    void contextInit();
 
    virtual void contextClose()
    {
       ;
    }
 
    virtual void contextPreDraw()
    {
       ;
    }
 
    virtual void bufferPreDraw()
    {
       ;
    }
 
    virtual void pipePreDraw()
    {
       ;
    }
 
 protected:
    void update()
    {
       ++mFrameNumber;
 
       // Update the frame stamp with information from this frame.
       mFrameStamp->setFrameNumber(mFrameNumber);
       mFrameStamp->setReferenceTime(mHead->getTimeStamp().secd());
 
       // Set up the time and frame number so time-dependent things (animations,
       // particle system) function correctly.
       // XXX: This may not be necessary.
       mUpdateVisitor->setTraversalNumber(mFrameNumber);
 
       // Update the scene by traversing it with the the update visitor which
       // will call all node update callbacks and animations. This is
       // equivalent to calling osgUtil::SceneView::update() but does not
       // require access to the context-specific osgUtil::SceneView instance.
       getScene()->accept(*mUpdateVisitor);
    }
 
    vrj::GlContextData< osg::ref_ptr<osgUtil::SceneView> > sceneViewer;
 
 private:
    osg::ref_ptr<osg::NodeVisitor> mUpdateVisitor;
    osg::ref_ptr<osg::FrameStamp> mFrameStamp;
 
    int mFrameNumber;
    gadget::PositionInterface mHead;
 };
 
 inline void OsgApp::contextInit()
 {
    unsigned int unique_context_id = GlDrawManager::instance()->getCurrentContext();
 
    // --- Create new context specific scene viewer -- //
    osg::ref_ptr<osgUtil::SceneView> new_sv(new osgUtil::SceneView);
    this->configSceneView(new_sv.get());            // Configure the new viewer
    new_sv->getState()->setContextID(unique_context_id);
 
    // This will eventually be changed to no light and all lighting will be handled
    // by the application.  For the time being it fixes the lighting inconsistanies
    // over multiple screens
    new_sv->setLightingMode(osgUtil::SceneView::SKY_LIGHT);
 
    (*sceneViewer) = new_sv;
 
    //Setup OpenGL light
    //This should actualy be done in the simulator code
    GLfloat light0_ambient[] = { 0.1f,  0.1f,  0.1f,  1.0f};
    GLfloat light0_diffuse[] = { 0.8f,  0.8f,  0.8f,  1.0f};
    GLfloat light0_specular[] = { 1.0f,  1.0f,  1.0f,  1.0f};
    GLfloat light0_position[] = {0.0f, 0.75f, 0.75f, 0.0f};
 
    GLfloat mat_ambient[] = { 0.7f, 0.7f,  0.7f,  1.0f};
    GLfloat mat_diffuse[] = { 1.0f,  0.5f,  0.8f,  1.0f};
    GLfloat mat_specular[] = { 1.0f,  1.0f,  1.0f,  1.0f};
    GLfloat mat_shininess[] = { 50.0f};
    //GLfloat mat_emission[] = { 1.0f,  1.0f,  1.0f,  1.0f};
    GLfloat no_mat[] = { 0.0f,  0.0f,  0.0f,  1.0f};
 
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,  light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION,  light0_position);
 
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT,  GL_DIFFUSE, mat_diffuse );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialfv( GL_FRONT,  GL_SHININESS, mat_shininess );
    glMaterialfv( GL_FRONT,  GL_EMISSION, no_mat);
 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
 }
 
 
 inline void OsgApp::draw()
 {
    glClear(GL_DEPTH_BUFFER_BIT);
 
    // Users have reported problems with OpenGL reporting stack underflow
    // problems when the texture attribute bit is pushed here, so we push all
    // attributes *except* GL_TEXTURE_BIT.
    glPushAttrib(GL_ALL_ATTRIB_BITS & ~GL_TEXTURE_BIT);
    glPushAttrib(GL_TRANSFORM_BIT);
    glPushAttrib(GL_VIEWPORT_BIT);
 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
 
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
 
 
    osg::ref_ptr<osgUtil::SceneView> sv;
    sv = (*sceneViewer);    // Get context specific scene viewer
    vprASSERT(sv.get() != NULL);
 
    // Set the timing information in the scene view.
    sv->setFrameStamp(mFrameStamp.get());
 
    GlDrawManager*    gl_manager;    
    gl_manager = GlDrawManager::instance();
 
    // Set the up the viewport (since OSG clears it out)
    float vp_ox, vp_oy, vp_sx, vp_sy;   // The float vrj sizes of the view ports
    int w_ox, w_oy, w_width, w_height;  // Origin and size of the window
    gl_manager->currentUserData()->getViewport()->getOriginAndSize(vp_ox, vp_oy, vp_sx, vp_sy);
    gl_manager->currentUserData()->getGlWindow()->getOriginSize(w_ox, w_oy, w_width, w_height);
 
    // compute unsigned versions of the viewport info (for passing to glViewport)
    unsigned ll_x = unsigned(vp_ox*float(w_width));
    unsigned ll_y = unsigned(vp_oy*float(w_height));
    unsigned x_size = unsigned(vp_sx*float(w_width));
    unsigned y_size = unsigned(vp_sy*float(w_height));
 
    // Add the tree to the scene viewer and set properties
    sv->setSceneData(getScene());
    //sv->setCalcNearFar(false);
    sv->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);
    sv->setViewport(ll_x, ll_y, x_size, y_size);
 
    //Get the view matrix and the frustrum form the draw manager
    GlDrawManager* drawMan = dynamic_cast<GlDrawManager*>(this->getDrawManager());
    vprASSERT(drawMan != NULL);
    GlUserData* userData = drawMan->currentUserData();
 
    //Get the frustrum
    Projection* project = userData->getProjection();
    Frustum frustum = project->getFrustum();
    sv->setProjectionMatrixAsFrustum(frustum[Frustum::VJ_LEFT],
                                     frustum[Frustum::VJ_RIGHT],
                                     frustum[Frustum::VJ_BOTTOM],
                                     frustum[Frustum::VJ_TOP],
                                     frustum[Frustum::VJ_NEAR],
                                     frustum[Frustum::VJ_FAR]);
 
    // Copy the view matrix
    sv->setViewMatrix(osg::Matrix(project->getViewMatrix().mData));
 
    //Draw the scene
    // NOTE: It is not safe to call osgUtil::SceneView::update() here; it
    // should only be called by a single thread. The equivalent of calling
    // osgUtil::SceneView::update() is in vrj::OsgApp::update().
    sv->cull();
    sv->draw();
 
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
 
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
 
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
 
    glPopAttrib();
    glPopAttrib();
    glPopAttrib();
 }
 
 }
 
 
 #endif /* _VRJ_OSG_APP_H_