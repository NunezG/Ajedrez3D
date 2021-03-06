#/*
#-----------------------------------------------------------------------------
#Filename:    CMakeLists.txt
#-----------------------------------------------------------------------------
#
#This source file is part of the
#   ___                 __    __ _ _    _ 
#  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
# //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
#/ \_// (_| | | |  __/  \  /\  /| |   <| |
#\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
#      |___/                              
#      Tutorial Framework
#      http://www.ogre3d.org/tikiwiki/
#-----------------------------------------------------------------------------
#*/


cmake_minimum_required(VERSION 2.6)
 
project(OgreApp)
 

if(WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		$ENV{OGRE_HOME}/Samples/include
	)
endif(WIN32)
 
if(UNIX)
	message("TEST.")
	if(EXISTS "/usr/local/lib/OGRE/cmake")
message("PRIMER IFF.")
	  set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

	elseif(EXISTS "/usr/share/OGRE/cmake/modules")
message("SEGUNDO IFF.")
	  set(CMAKE_MODULE_PATH "/usr/share/OGRE/cmake/modules/;${CMAKE_MODULE_PATH}")
          set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/include/OGRE/") # Otherwise, this one

	else ()
	  message(SEND_ERROR "Failed to find module path.")
        endif()
endif(UNIX)
 
if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")
 
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")
 
message("INICIA FINDOGRE.")
find_package(OGRE REQUIRED)
message("ACABA FINDOGRE.") 

#if(NOT "${OGRE_VERSION_NAME}" STREQUAL "Cthugha")
#  message(SEND_ERROR "You need Ogre 1.7 Cthugha to build this.")
#endif()
 
find_package(OIS REQUIRED)
 
if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()
 
# Find Boost
#if (NOT OGRE_BUILD_PLATFORM_IPHONE)
#	if (WIN32 OR APPLE)
#		set(Boost_USE_STATIC_LIBS TRUE)
#	else ()
#		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
#		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
#	endif ()
#	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
#		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
#	endif ()
#	set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
#	# Components that need linking (NB does not include header-only components like bind)
#	set(OGRE_BOOST_COMPONENTS thread date_time)
#	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
#	if (NOT Boost_FOUND)
#		# Try again with the other type of libs
#		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
#		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
#	endif()
#	find_package(Boost QUIET)
 #
#	# Set up referencing of Boost
#	include_directories(${Boost_INCLUDE_DIR})
#	add_definitions(-DBOOST_ALL_NO_LIB)
#	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
#endif()
 
# NUEVA SECCIÓN

message("llama a FINDCEGUI.")
find_package(CEGUI REQUIRED)
message("ACABA FINDÇCEGUI.")
#if(NOT CEGUI_FOUND)
#message(SEND_ERROR "Failed to find CEGUI.")
#endif()
message("INICIA CEGUIOGRE.")
find_package(CEGUIOGRE REQUIRED)
message("ACABA CEGUIOGRE.")
#if(NOT CEGUIOGRE_FOUND)
#message("Failed to find CEGUIOGRE.")
#endif()

# FIN NUEVA SECCIÓN


set(HDRS
        #./headers/BaseOgre.h
        #./headers/CreacionJuego.h
       # ./headers/MenuInicial.h
       # ./headers/Control/Inicio.h
        #./headers/Inicio.h
      #  ./headers/Control/ControlJuego.h

        ./headers/Vistas/Ventana.h
        ./headers/Vistas/VistaAjedrez.h
        ./headers/Vistas/VistaAjedrezSolo.h
        ./headers/Vistas/MenuInicio.h
        ./headers/Vistas/BaseVistas.h

        # headers de modelo
      #  ./headers/Modelo/InputMan.h
   #    ./headers/Modelo/Calculos.h

       ./headers/Modelo/Autorizaciones.h
        ./headers/Modelo/Movimientos.h
        ./headers/Modelo/Modelo.h
        ./headers/Modelo/ModeloTablero.h
        ./headers/Modelo/ArbolBusqueda.h

       # ./headers/Modelo/ModeloMenu.h
      #  ./headers/Modelo/ModuloIA.h

       ./headers/ModeloVista/Tablero.h
       ./headers/ModeloVista/FichaRey.h
       ./headers/ModeloVista/FichaReina.h
       ./headers/ModeloVista/FichaPeon.h
       ./headers/ModeloVista/FichaAlfil.h
       ./headers/ModeloVista/FichaCaballo.h
       ./headers/ModeloVista/FichaTorre.h
       ./headers/ModeloVista/Ficha.h
        ./headers/ModeloVista/ObjetoOgre.h
        ./headers/ModeloVista/Casilla.h
        ./headers/ModeloVista/EscenaAjedrez.h
        ./headers/ModeloVista/ModeloVista.h
        ./headers/ModeloVista/Jugador.h
        ./headers/ModeloVista/JugadorHumano.h
        ./headers/ModeloVista/JugadorArtificial.h
)
 
set(SRCS

        #CONTROL
       # ./impl/Control/Inicio.cpp

        ./impl/Inicio.cpp
      #  ./impl/Control/ControlJuego.cpp

        # VISTA
       # ./impl/BaseOgre.cpp
        ./impl/Vistas/VistaAjedrez.cpp
        ./impl/Vistas/VistaAjedrezSolo.cpp
        ./impl/Vistas/Ventana.cpp
        ./impl/Vistas/MenuInicio.cpp
        ./impl/Vistas/BaseVistas.cpp

       # ./impl/CreacionJuego.cpp
       # ./impl/MenuInicial.cpp

        # implementaciones de modelo

         #  MODELO
  #     ./impl/Modelo/Calculos.cpp
       ./impl/Modelo/Autorizaciones.cpp
       ./impl/Modelo/Movimientos.cpp
        ./impl/Modelo/Modelo.cpp
        ./impl/Modelo/ModeloTablero.cpp
       ./impl/Modelo/ArbolBusqueda.cpp

      #    ./impl/Modelo/ModuloIA.cpp

        # MODELOVISTA
       ./impl/ModeloVista/Tablero.cpp
       ./impl/ModeloVista/FichaRey.cpp
       ./impl/ModeloVista/FichaReina.cpp
       ./impl/ModeloVista/FichaPeon.cpp
       ./impl/ModeloVista/FichaAlfil.cpp
       ./impl/ModeloVista/FichaCaballo.cpp
       ./impl/ModeloVista/FichaTorre.cpp
       ./impl/ModeloVista/Ficha.cpp
        ./impl/ModeloVista/ObjetoOgre.cpp
       ./impl/ModeloVista/Casilla.cpp
        ./impl/ModeloVista/EscenaAjedrez.cpp
        ./impl/ModeloVista/ModeloVista.cpp
       ./impl/ModeloVista/Jugador.cpp
      ./impl/ModeloVista/JugadorHumano.cpp
       ./impl/ModeloVista/JugadorArtificial.cpp

     #  ./impl/Modelo/ModeloMenu.cpp
)
 
include_directories( ${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	#NUEVA SECCIÓN
        ${CEGUI_INCLUDE_DIRS}
${CEGUIOGRE_INCLUDE_DIRS}
	# FIN NUEVA SECCIÓN
)
 
add_executable(OgreApp WIN32 ${HDRS} ${SRCS})
 
set_target_properties(OgreApp PROPERTIES DEBUG_POSTFIX _d)
 
# CAMBIA target_link_libraries(OgreApp ${OGRE_LIBRARIES} ${OIS_LIBRARIES})
 target_link_libraries(OgreApp ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${CEGUI_LIBRARIES} ${CEGUIOGRE_LIBRARIES})
 

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)
 
# post-build copy for win32
if(WIN32 AND NOT MINGW)
        add_custom_command( TARGET OgreApp PRE_BUILD
		COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
        add_custom_command( TARGET OgreApp POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
    message("SET EXECUTABLE")
    message( ${PROJECT_BINARY_DIR})
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)
 
if(WIN32)
 
        install(TARGETS OgreApp
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/Media
                DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
                DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/dist/bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
                DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/dist/bin       #bin
		CONFIGURATIONS Debug
	)
 
        # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
        # so you'll have to change that to make it work with 1.7.1
	install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
                DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/dist/bin #bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
                DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/dist/bin
		CONFIGURATIONS Debug
	)
 
   # as of sdk 1.7.2 we need to copy the boost dll's as well
   # because they're not linked statically (it worked with 1.7.1 though)
#   install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
#      ${Boost_THREAD_LIBRARY_RELEASE}
#      DESTINATION bin
#      CONFIGURATIONS Release RelWithDebInfo
#   )
 
#   install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
#      ${Boost_THREAD_LIBRARY_DEBUG}
#      DESTINATION bin
#      CONFIGURATIONS Debug
 #  )
endif(WIN32)

if(UNIX)
 
        install(TARGETS OgreApp
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
endif(UNIX)
 
