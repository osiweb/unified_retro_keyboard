#!/bin/bash

source "$(dirname "${BASH_SOURCE[0]}")/version.sh"

GENERATOR="Unix Makefiles"
NUM_VALID_TARGETS=0
BUILD_TYPE=RELEASE
INSTALL_DIR="dist"
MAKE_TARGETS="all"
DOC_DIR=docs
LINKS_DIR="$DOC_DIR/source"

add_valid_target() {
    VALID_TARGETS[$NUM_VALID_TARGETS]=$1
    TARGET_TYPE[$NUM_VALID_TARGETS]=${2:-EXECUTABLE}
    ((NUM_VALID_TARGETS++))
}

add_valid_target test         UNIT_TEST
add_valid_target atmega328p
add_valid_target atmega168p
add_valid_target atmega88p
add_valid_target atmega2560
add_valid_target atmega1280
add_valid_target atmega640
add_valid_target simavr_test  INTEGRATION_TEST


check_valid_target() {
    result="false"

    for (( i = 0; i < NUM_VALID_TARGETS; i++ ))
    do
        if [[ ${VALID_TARGETS[$i]} == $1 ]]
        then
            result=$i
        fi
    done
    echo $result
}


do_pipenv_clean() {
    echo removing old python virtual environment...
    pipenv --rm
}


do_pipenv_install() {
    echo installing python virtual environment...
    pipenv install
}

clean_arch() {
    target_arch="$1"
    echo "Removing pre-existing build directory: $target_arch..."
    rm -rf "build-$target_arch"
    echo "Removing any build artifacts"
    rm -f $INSTALL_DIR/*"$1"*
    echo "Removing any download links"
    rm -f $LINKS_DIR/*$1*
}

preflight_simavr_test() {
    local missing=0
    local ver
    ver=$(asdf_version)
    for t in atmega328p atmega168p atmega640 atmega1280 atmega2560; do
        local elf="build-$t/src/asdf-v${ver}-$t.elf"
        if [[ ! -f $elf ]]; then
            echo "ERROR: missing $elf"
            missing=1
        fi
    done
    if [[ $missing -ne 0 ]]; then
        echo
        echo "Run: bash make-targets.sh -a"
        echo "to build the AVR firmware before running integration tests."
        return 1
    fi

    if ! command -v simavr >/dev/null 2>&1; then
        echo "ERROR: simavr not found on PATH."
        echo "Install with: sudo apt-get install simavr libsimavr-dev pkg-config"
        echo "          or: sudo port install simavr  (MacPorts)"
        echo "          or: brew install simavr  (Homebrew)"
        return 1
    fi
    local header_found=
    for prefix in /usr/include /usr/local/include /opt/local/include /opt/homebrew/include; do
        if [[ -f "$prefix/simavr/sim_avr.h" ]]; then
            header_found="$prefix/simavr/sim_avr.h"
            break
        fi
    done
    if [[ -z $header_found ]]; then
        echo "ERROR: libsimavr headers not found."
        echo "Install with: sudo apt-get install libsimavr-dev"
        echo "          or: sudo port install simavr"
        echo "          or: brew install simavr"
        echo "Or build from source and pass -DSIMAVR_ROOT=<prefix> via cmake."
        return 1
    fi
    return 0
}

build_arch() {
    local target_arch="$1"
    local target_type="$2"

    if [[ $target_arch == simavr_test ]]; then
        preflight_simavr_test || exit 1
    fi

    cmake -S . -B "build-$target_arch" -G "$GENERATOR" \
        -DCMAKE_INSTALL_PREFIX="." -DARCH="$target_arch" \
        -DCMAKE_BUILD_TYPE="$BUILD_TYPE" || exit 1

    if [[ $target_type == UNIT_TEST || $target_type == INTEGRATION_TEST ]]; then
        (cd "build-$target_arch" && make && ctest --output-on-failure) || exit 1
    fi

}

deploy_arch() {
    local target_arch="$1"

    if [[ -d "build-$target_arch" ]]
    then
        (cd "build-$target_arch" \
        && make install) || exit 1
    fi
}

clean_all() {
    echo "- Removing install dir \"$INSTALL_DIR\"..."
    rm -rvf "$INSTALL_DIR"
    echo "- Removing download links from doc dir..."
    rm -vf $DOC_DIR/source/toc_*
    echo "- Removing hex files from doc dir..."
    rm -vf $DOC_DIR/source/*.hex
    echo "- Removing versioned index file from doc dir"
    rm -vf "$DOC_DIR/source/index.rst"
}

syntax() {
    echo "Usage:"
    echo "  $0 -t target [-t target] ..."
    echo "  $0 -a"
    echo "  $0 -h"
    echo ""
    echo "Options:"
    echo "  -h.  Display this help message"
    echo "  -x   Before creating a build directgory or virtual env, remove"
    echo "       any pre-existing version"
    echo "  -t   add an architecture directory"
    echo "  -a   Add all valid architecture directories"
    echo "  -i   Build each specified target and install to dist directory"
    echo "  -p   Install pipenv virtual environment for python scripts"
    echo "  -c   Clean all artifacts"
    echo "  -s   Copy dist files to sphinx directory"
    echo "Valid targets: ${VALID_TARGETS[*]}"
}

parse() {
    local SYNTAX=""
    local ALL=""
    local i
    local valid_index

    NUM_CMAKE_TARGETS=0
    CLEAN_BEFORE_BUILD=""
    DO_PIPENV_INSTALL=""
    DEPLOY=""
    CLEAN_ALL=""
    COPY_DIST_TO_DOCS=""

    while getopts "t:ahipxcs" optname
    do
        case "$optname" in
            h)
                SYNTAX="yes"
                ;;
            a)
                ALL="yes"
                ;;
            t)
                # Test that target is valid
                valid_index=$(check_valid_target $OPTARG)
                if [[ $valid_index != "false" ]]
                then
                    CMAKE_TARGETS[$NUM_CMAKE_TARGETS]=$valid_index
                    ((NUM_CMAKE_TARGETS++))
                else
                    echo Unknown target \"$OPTARG\"
                    SYNTAX="yes"
                fi
                ;;
            p)
                DO_PIPENV_INSTALL="yes"
                ;;
            x)
                CLEAN_BEFORE_BUILD="yes"
                ;;
            i)  DEPLOY="yes"
                ;;
            s)  COPY_DIST_TO_DOCS="yes"
                ;;
            c)  CLEAN_ALL="yes"

    esac
    done

    if [[ "$SYNTAX" == "yes" ]]; then
        syntax && die
    fi

    if [[ "$ALL" == "yes" ]]
    then
        for (( i=0; i<NUM_VALID_TARGETS; i++ ))
        do
            if [[ ${TARGET_TYPE[$i]} == "EXECUTABLE" ]]; then
                CMAKE_TARGETS[$NUM_CMAKE_TARGETS]=$i
                ((NUM_CMAKE_TARGETS++))
            fi
        done
    fi

}

die() {
    builtin echo $@
    exit 1
}

main() {
     local TARGET
     local i
     parse $@

     if [[ "$DO_PIPENV_INSTALL" == "yes" ]]
     then
         if [[ "$CLEAN_BEFORE_BUILD" == "yes" ]]
         then
             do_pipenv_clean
         fi

         do_pipenv_install
     fi

     if [[ "$CLEAN_ALL" == "yes" ]]
     then
         clean_all
     fi

     echo Valid Targets: "${VALID_TARGETS[*]}"

     for (( i=0; $i<$NUM_CMAKE_TARGETS; i++ ))
     do
         TARGET=${CMAKE_TARGETS[$i]}
         if [[ "$CLEAN_BEFORE_BUILD" == "yes" ]]
         then
             clean_arch ${VALID_TARGETS[$TARGET]}
         fi
         build_arch ${VALID_TARGETS[$TARGET]} ${TARGET_TYPE[$TARGET]}
         if [[ "$DEPLOY" == "yes" ]]
         then
             deploy_arch ${VALID_TARGETS[$TARGET]}
         fi
     done

     if [[ $COPY_DIST_TO_DOCS == "yes" && -d "$INSTALL_DIR" ]]
     then
         cp -av "$INSTALL_DIR"/* docs/source
     fi

}


main $@

exit 0


