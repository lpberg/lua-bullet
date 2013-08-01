/**
	@file
	@brief Implementation

	@date 2013

	@author
	Patrick Carlson
	<carlsonp@iastate.edu>
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


// Internal Includes
#include "../BindingFwd.h"

// Library/third-party includes
#include <luabind/class.hpp>

#include <osgbCollision/ComputeShapeVisitor.h>


// Standard includes
// - none



template<> luabind::scope getLuaBinding<osgbCollision::ComputeShapeVisitor>() {
	using namespace luabind;

	return
	    class_<osgbCollision::ComputeShapeVisitor> ("ComputeShapeVisitor")
	    .def(constructor<const BroadphaseNativeTypes, const osgbCollision::AXIS, const unsigned int, osg::NodeVisitor::TraversalMode>())
	    //http://www.rasterbar.com/products/luabind/docs.html#overloaded-functions
	    ///@TODO these are close, how to specify osg::Group & ?
	    //.def("apply", (void(*)(osg::Group))&osgbCollision::ComputeShapeVisitor::apply)
	    //.def("apply", (void(*)(osg::Node))&osgbCollision::ComputeShapeVisitor::apply)
	    //.def("apply", (void(*)(osg::Transform))&osgbCollision::ComputeShapeVisitor::apply)
	    //.def("apply", (void(*)(osg::Geode))&osgbCollision::ComputeShapeVisitor::apply)
	    ///@TODO figure out how we can bind these appropriately, one normal, one const
	    //.def("getShape", &osgbCollision::ComputeShapeVisitor::getShape)
	    ;
}