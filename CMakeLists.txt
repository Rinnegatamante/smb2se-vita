cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(smb2se C CXX)
include("${VITASDK}/share/vita.cmake" REQUIRED)
set(VITA_APP_NAME "Super Monkey Ball 2: Sakura Edition")
set(VITA_TITLEID  "SMB2SAKED")
set(VITA_VERSION  "01.00")
set(VITA_MKSFOEX_FLAGS "-d ATTRIBUTE2=12")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wl,-q,--wrap,memcpy,--wrap,memmove,--wrap,memset -D_GNU_SOURCE -Wall -O3 -mfloat-abi=softfp")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

add_executable(smb2se
  loader/main.c
  loader/dialog.c
  loader/so_util.c
  loader/sha1.c
  loader/trophies.c
  loader/audio_player.cpp
)

target_link_libraries(smb2se
  -Wl,--whole-archive pthread -Wl,--no-whole-archive
  m
  z
  stdc++
  vorbis
  vorbisfile
  ogg
  vitaGL
  vitashark
  soloud
  mathneon
  SceShaccCgExt
  taihen_stub
  kubridge_stub
  SceAppMgr_stub
  SceAppUtil_stub
  SceAudio_stub
  SceAudioIn_stub
  SceCtrl_stub
  SceCommonDialog_stub
  SceDisplay_stub
  SceKernelDmacMgr_stub
  SceRazorHud_stub
  SceRazorCapture_stub
  SceFios2_stub
  SceGxm_stub
  SceLibcBridge_stub
  SceShaccCg_stub
  SceSysmodule_stub
  ScePower_stub
  SceTouch_stub
  SceVshBridge_stub
  SceMotion_stub
  SceNpTrophy_stub
)

vita_create_self(eboot.bin smb2se UNSAFE)
vita_create_vpk(smb2se.vpk ${VITA_TITLEID} eboot.bin
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE ${CMAKE_SOURCE_DIR}/livearea/icon0.png sce_sys/icon0.png
       ${CMAKE_SOURCE_DIR}/livearea/bg0.png sce_sys/livearea/contents/bg0.png
       ${CMAKE_SOURCE_DIR}/livearea/startup.png sce_sys/livearea/contents/startup.png
       ${CMAKE_SOURCE_DIR}/livearea/template.xml sce_sys/livearea/contents/template.xml
       ${CMAKE_SOURCE_DIR}/livearea/TROPHY.TRP sce_sys/trophy/SMBS00001_00/TROPHY.TRP
)

add_custom_target(copy
  COMMAND cp eboot.bin D:/app/${VITA_TITLEID}/eboot.bin
  DEPENDS eboot.bin
)
