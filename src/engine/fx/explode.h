/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
*
* This library is open source and may be redistributed and/or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/

#ifndef OSGPARTICLE_EXPLOSIONEFFECT
#define OSGPARTICLE_EXPLOSIONEFFECT

#include <osgParticle/ParticleEffect>
#include <osgParticle/ModularEmitter>
#include <osgParticle/FluidProgram>

namespace osgParticle
{

    class OSGPARTICLE_EXPORT Explode : public ParticleEffect
    {
    public:

        explicit Explode(bool automaticSetup=true);

        Explode(const osg::Vec3& position, float scale=1.0f, float intensity=1.0f);

        Explode(const Explode& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        //META_Node(osgParticle,ExplosionEffect);

        virtual void setDefaults();

        virtual void setUpEmitterAndProgram();

        virtual Emitter* getEmitter() { return _emitter.get(); }
        virtual const Emitter* getEmitter() const { return _emitter.get(); }

        virtual Program* getProgram() { return _program.get(); }
        virtual const Program* getProgram() const { return _program.get(); }

    protected:

        virtual ~Explode() {}

        osg::ref_ptr<ModularEmitter> _emitter;
        osg::ref_ptr<FluidProgram> _program;

    };
}

#endif
