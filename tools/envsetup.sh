#!/bin/bash

BASE_PATH=$(dirname -- "$(readlink -f "${BASH_SOURCE}")")
APP_PATH=${BASE_PATH}/../app
CONFIG_FILE_NAME=env.cfg

echo "Project enviroment setup!";
PROJECTS=(${APP_PATH}/*)

PROJECT_IDX=0
for d in ${APP_PATH}/* ; do
    echo "["${PROJECT_IDX}"]" $(basename -- ${PROJECTS[PROJECT_IDX]})
    PROJECT_IDX=$((PROJECT_IDX+1)) 
done

APP_NAME=
while [ -z "${APP_NAME}" ]; do
    echo "Select project to build:";
    read SELECTED_PROJECT

    if (( ${SELECTED_PROJECT} >= ${#PROJECTS[@]} || ${SELECTED_PROJECT} < 0 )); then
        echo "Invalid choice!";
        APP_NAME=${NULL}
    else
        APP_NAME=$(basename -- ${PROJECTS[SELECTED_PROJECT]})
        echo "Selected:" ${APP_NAME};
    fi
done

TOOLCHAIN_BIN_PATH=
while [ -z "${TOOLCHAIN_BIN_PATH}" ]; do
    echo "Enter toolchaing bin path:";
    read TOOLCHAIN_BIN_PATH

    if [ ! -d ${TOOLCHAIN_BIN_PATH} ]; then
        echo "Invalid path";
        TOOLCHAIN_BIN_PATH=
    else
        echo "Toolchain set:" ${TOOLCHAIN_BIN_PATH}
    fi
done

echo "Exporting config!";

cat > ${CONFIG_FILE_NAME} << EOF
# Project configuration created $(date) by $(whoami)

TOOLCHAIN_BIN_PATH := ${TOOLCHAIN_BIN_PATH}
APP_NAME           := ${APP_NAME}
BUILD_VERSION      := 0.1
BUILD_USER         := $(whoami)
EOF
