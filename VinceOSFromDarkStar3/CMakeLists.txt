cmake_minimum_required (VERSION 2.6)
project(DARKSTAR3)

#project defined variables
SET(fw_name "darkstar3") 
SET(${fw_name}_FLAGS "-g") #-fprofile-arcs")
SET(dev_include include)
SET(ARCH "x86") 

#predefined variables
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${${fw_name}_FLAGS}" )
FOREACH(flag ${${fw_name}_FLAGS})
    message("auto FLAGS:" ${flag}) 
ENDFOREACH(flag)
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g") 

#Architecture variable check
IF ("${ARCH}" STREQUAL "x86") 
    message ("Platform:" ${ARCH}) 
    ADD_DEFINITIONS("-DTARGET")
ENDIF ("${ARCH}" STREQUAL "x86") 

#add_library(name STATIC filename.c)
SET (dependents "dbus-glib-1") #sudo apt-get install libdbus-glib-1-dev
#when pc_dependents is required ? when dependents is required? why they are different?
SET (pc_dependents "dbus-glib-1") 
#Use FindPkgConfig and PKG_CHECK_MODULES to find packages
INCLUDE(FindPkgConfig)
#PKG_CHECK_MODULES(${fw_name} REQUIRED ${depedents})
PKG_CHECK_MODULES(pkgs REQUIRED ${dependents}) 
MESSAGE("pkgs ${pkgs_CFLAGS}, ${pkgs_LDFLAGS}") 
#MESSAGE("PKG_CHECK_MODULE Result: ${${fw_name}_CFLAGS}") 

#PKG_CHECK_MODULES updated this project's CFLAGS so check it out and save into CMAKE_C_FLAGS
FOREACH(flag ${pkgs_CFLAGS})
    message("flag:"${flag})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

#Compiler only cares this
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}" )

#add_subdirectory(src)

SET(${fw_name}_INCLUDES 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${${fw_name}_INCLUDES})

SET(${fw_name}_LINKS 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    /usr/local/lib)

#FIND_LIBRARY is better choice
link_directories(${${fw_name}_LINKS})

#if you make new line for each file generate error
SET(${fw_name}_SRCS 
    src/main.c 
    src/app_launcher/app_launcher_daemon.c
    src/system_controller/system_server.c
    src/queue/circular_queue_array.c)
    #src/redblacktree/rdb.c)

add_executable(${fw_name} ${${fw_name}_SRCS})

target_link_libraries(${fw_name} liblog4c.so) 

#install dev (headers) here why includes means /usr/local/include????
INSTALL(
        DIRECTORY ${dev_include}/ DESTINATION /usr/local/include/${fw_name}
        FILES_MATCHING
        PATTERN "*_private.h" EXCLUDE
        PATTERN "${dev_include}/*.h"
        )


#TBD: Install at ${CMAKE_INSTALL_PREFIX} which is /usr/local so include and lib all means /usr/local as default
install(TARGETS ${fw_name} DESTINATION /usr/local/bin)

#TBD: pkg-config setting
SET(PC_NAME ${fw_name})
SET(PC_REQUIRED ${pc_dependents})
SET(PC_LDFLAGS -l${fw_name})

#CONFIGURE_FILE 
CONFIGURE_FILE(
    pkgconfig-template.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc
    @ONLY
)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc DESTINATION lib/pkgconfig)


