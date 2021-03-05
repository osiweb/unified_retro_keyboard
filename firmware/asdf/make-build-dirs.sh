#!/opt/local/bin/bash


CMAKE_TARGETS=""
VALID_TARGETS=""

add_valid_target() {
    VALID_TARGETS+=" $1 "
}

add_valid_target test
add_valid_target atmega328p
add_valid_target atmega2560

build_arch() {
    echo one: $1 two: $2 three: $3
    echo star: "[$*]"
    echo amp: "[$@]"
    for target_arch in "$@"
    do
        if [[ ! -d "build-$target_arch" ]]
        then
            mkdir  "build-$target_arch"
        fi

        if [[ -d "build-$target_arch" ]]
        then
            (cd "build-$target_arch" && cmake -DARCH=$target_arch ..)
        fi
    done
}

main() {
    parse $@

    echo "Valid: $VALID_TARGETS"
    echo "Selected: $CMAKE_TARGETS"

    run
}

run() {
    echo "$CMAKE_TARGETS"

    build_arch $CMAKE_TARGETS
}


syntax() {
    echo "Usage:"
    echo "  $0 -t target [-t target] ..."
    echo "  $0 -a"
    echo "  $0 -h"
    echo ""
    echo "Options:"
    echo "  -t   add an architecture directory"
    echo "  -h   Display this help message"
    echo "  -a   Add all valid architecture directories"
    echo ""
    echo "Valid targets: $VALID_TARGETS"
}

parse() {
    local SYNTAX=""
    local ALL=""

    while getopts "t:ah" optname
    do
        case "$optname" in
            h)
                SYNTAX="yes"
                ;;
            a)
                ALL="yes"
                ;;
            t)
                # Test that target is valid and not already specified
                if [[ " $VALID_TARGETS " == *" $OPTARG "* ]]
                then
                    if [[ " $CMAKE_TARGETS " != *" $OPTARG "* ]]
                    then
                        CMAKE_TARGETS+=" $OPTARG "
                    fi
                else
                    SYNTAX="yes"
                fi
                ;;
        esac
    done

    if [[ "$SYNTAX" == "yes" ]]; then
        syntax && die
    fi

    if [[ "$ALL" == "yes" ]]
    then
        CMAKE_TARGETS="$VALID_TARGETS"
    fi

    if [[ -z "$CMAKE_TARGETS" ]]
    then
        die "No targets!"
    fi
}

die() {
    builtin echo $@
    exit 1
}

main $@

exit 0


