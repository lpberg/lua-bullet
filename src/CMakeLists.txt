#Put some checks in here so we know the variables have a value
#http://www.cmake.org/cmake/help/v2.8.11/cmake.html#command:message
if("${LUABIND_INCLUDE_DIRS}" STREQUAL "")
	message(FATAL_ERROR "LUABIND_INCLUDE_DIRS is empty.")
endif()
if("${OPENSCENEGRAPH_INCLUDE_DIR}" STREQUAL "")
	message(FATAL_ERROR "OPENSCENEGRAPH_INCLUDE_DIR is empty.")
endif()

include_directories(${LUABIND_INCLUDE_DIRS}
	${OPENSCENEGRAPH_INCLUDE_DIR}
	"${OSGWORKS_INSTALL_DIR}/include"
	"${BULLET_INSTALL_DIR}/include/bullet"
	"${OSGBULLET_INSTALL_DIR}/include"
	${Boost_INCLUDE_DIRS})

add_definitions(-DLUABULLET_BUILDING)


#list(APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/lib/")
#find_package(Bullet REQUIRED)

#Add FindOSGWorks.cmake file
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/submodules/osgworks/extra/")
#find_package(osgWorks REQUIRED)

#Add FindOSGBullet.cmake file
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/submodules/osgbullet/extra/")
#find_package(osgBullet REQUIRED)


set(SOURCES
	BindingFwd.h
	ClassInfo.cpp
	ClassInfo.h
	LuaInclude.h
	LuaInterface.h
	ModuleEntryPoint.cpp
	ModuleEntryPoint.h
	Version.h
)

set(OSGBULLET_BINDING
	#Bullet:	
	LinearMath/btVector3.cpp
	#BulletCollision/CollisionShapes/btCollisionShape.cpp
	BulletCollision/CollisionShapes/btBoxShape.cpp
	BulletDynamics/Dynamics/btRigidBody.cpp
	BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp
	BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp
	BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp
	BulletCollision/BroadphaseCollision/btAxisSweep3.cpp
	BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp
	LinearMath/btTransform.cpp
	BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp
	BulletCollision/CollisionShapes/btCompoundShape.cpp
	
	#osgBullet:
	osgbDynamics/CreationRecord.cpp
	osgbDynamics/MotionState.cpp
	osgbDynamics/PhysicsThread.cpp
	osgbDynamics/PhysicsState.cpp
	osgbDynamics/PhysicsData.cpp
	osgbCollision/ComputeShapeVisitor.cpp
	osgbCollision/ComputeTriMeshVisitor.cpp
	osgbCollision/CollectVerticesVisitor.cpp
	osgbCollision/ComputeCylinderVisitor.cpp
	osgbCollision/CollisionShapes.cpp
	osgbCollision/CollisionShapes.h
)

add_library(luabullet MODULE ${SOURCES} ${OSGBULLET_BINDING})
set_property(TARGET luabullet PROPERTY PREFIX "")

# Handle linking against shared libraries on Linux and Windows.
if(CMAKE_LINK_LIBRARY_SUFFIX)
	set(SHARED_LIBRARY_SUFFIX ${CMAKE_LINK_LIBRARY_SUFFIX})
else()
	set(SHARED_LIBRARY_SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()

target_link_libraries(luabullet
	${LUA_LIBRARIES}
	${LUABIND_LIBRARIES}
	${OPENSCENEGRAPH_LIBRARIES}
	"${BULLET_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}BulletCollision${CMAKE_STATIC_LIBRARY_SUFFIX}"
	"${BULLET_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}BulletDynamics${CMAKE_STATIC_LIBRARY_SUFFIX}"
	"${BULLET_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}LinearMath${CMAKE_STATIC_LIBRARY_SUFFIX}"
	"${BULLET_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}BulletSoftBody${CMAKE_STATIC_LIBRARY_SUFFIX}"
	"${OSGBULLET_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}osgbCollision${SHARED_LIBRARY_SUFFIX}"
	"${OSGBULLET_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}osgbDynamics${SHARED_LIBRARY_SUFFIX}"
	"${OSGWORKS_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}osgwTools${SHARED_LIBRARY_SUFFIX}")

add_dependencies(luabullet osgBullet)

#http://www.cmake.org/cmake/help/v2.8.11/cmake.html#command:install
install(TARGETS luabullet
	RUNTIME DESTINATION bin COMPONENT binding
	LIBRARY DESTINATION lib COMPONENT binding)

set(LUABULLET_INSTALL_NAME "${CMAKE_INSTALL_PREFIX}/bin/${CMAKE_SHARED_LIBRARY_PREFIX}luabullet${CMAKE_SHARED_MODULE_SUFFIX}")

set(APP)
set(PLUGINS)
set(LIBRARY_DIRS)

if(LUA_COMMAND)
	install(PROGRAMS "${LUA_COMMAND}" DESTINATION bin)
	get_filename_component(LUA_COMMAND_FILENAME "${LUA_COMMAND}" NAME)
	list(APPEND PLUGINS "${LUABULLET_INSTALL_NAME}")
	set(APP "${CMAKE_INSTALL_PREFIX}/bin/${LUA_COMMAND_FILENAME}")
else()
	set(APP "${LUABULLET_INSTALL_NAME}")
endif()


get_filename_component(LUA_LIBDIR "${LUA_LIBRARY}" PATH)
list(APPEND LIBRARY_DIRS "${LUA_LIBDIR}")

# Copy over Version.h header into install location
#file(COPY "${PROJECT_SOURCE_DIR}/src/Version.h" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/")


#For OSX:
#http://www.cmake.org/Wiki/BundleUtilitiesExample
#install(CODE "
#  include(BundleUtilities)
#  fixup_bundle(\"${APP}\" \"${PLUGINS}\" \"${LIBRARY_DIRS}\")
#  ")
