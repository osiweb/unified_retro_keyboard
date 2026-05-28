#!/usr/bin/env bash
# Print project version when executed; define asdf_version() when sourced.

asdf_version() {
    local cmake_file
    cmake_file="${1:-$(dirname -- "${BASH_SOURCE[0]}")/CMakeLists.txt}"
    awk '/^[[:space:]]*VERSION[[:space:]]+[0-9]/ { print $2; exit }' "$cmake_file"
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
    asdf_version "$@"
fi
