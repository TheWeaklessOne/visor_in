#!/bin/bash

FRAMEWORKS_DIR=~/Library/Frameworks/
SDL2=SDL2.framework
SDL2_IMAGE=SDL2_image.framework
SDL2_TTF=SDL2_ttf.framework
SDL2_MIXER=SDL2_mixer.framework
SDL2_DIR=$FRAMEWORKS_DIR$SDL2
SDL2_IMAGE_DIR=$FRAMEWORKS_DIR$SDL2_IMAGE
SDL2_TTF_DIR=$FRAMEWORKS_DIR$SDL2_TTF
SDL2_MIXER_DIR=$FRAMEWORKS_DIR$SDL2_MIXER

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
LMAGENTA='\033[1;35m'
NORMAL='\033[0m'

function check_frameworks()
{

    if [ ! -e $SDL2_DIR ] || [ ! -e $SDL2_IMAGE_DIR ] || [ ! -e $SDL2_MIXER_DIR ] || [ ! -e $SDL2_TTF_DIR ]; then

      echo "${CYAN}Can't find all SDL2 frameworks, cloning...${NORMAL}"
      echo "${LMAGENTA}"
      git clone https://github.com/TheWeaklessOne/Wolf3d .temp
      echo "${NORMAL}"
      if [ ! -e $SDL2_DIR ]; then
        mv .temp/Frameworks/$SDL2 $FRAMEWORKS_DIR
        echo "${GREEN}$SDL2 successfully cloned${NORMAL}"
      fi

      if [ ! -e $SDL2_IMAGE_DIR ]; then
        mv .temp/Frameworks/$SDL2_IMAGE $FRAMEWORKS_DIR
        echo "${GREEN}$SDL2_IMAGE successfully cloned${NORMAL}"
      fi

      if [ ! -e $SDL2_TTF_DIR ]; then
        mv .temp/Frameworks/$SDL2_TTF $FRAMEWORKS_DIR
        echo "${GREEN}$SDL2_TTF successfully cloned${NORMAL}"
      fi

        if [ ! -e $SDL2_MIXER_DIR ]; then
            mv .temp/Frameworks/$SDL2_MIXER $FRAMEWORKS_DIR
            echo "${GREEN}$SDL2_MIXER successfully cloned${NORMAL}"
        fi

      rm -rf .temp
    fi

    echo "\n${CYAN}All SDL2 frameworks is found${NORMAL}\n"
}

if [ ! -d "$FRAMEWORKS_DIR" ]; then
    echo "${CYAN}Directory $FRAMEWORKS_DIR is not exist, creating${NORMAL}"
    mkdir -p "$FRAMEWORKS_DIR"
    check_frameworks
else
    check_frameworks
fi
