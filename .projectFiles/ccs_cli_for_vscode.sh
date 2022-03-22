#!/bin/bash

# Make sure this program only executes within the repo's root directory
SCRIPT_ABS_PATH="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
if [[ "$(basename ${SCRIPT_ABS_PATH})" != ".projectFiles" ]]; then
    echo "This script cannot run from \"${SCRIPT_ABS_PATH}\". It must be stored in and ran from \"\${REPO_DIR}/.projectFiles\"."
    exit 1
fi

PROJ_CONFIG="Debug"
PROJ_WORKSPACE="${SCRIPT_ABS_PATH%/*/*}"
PROJ_NAME="$( basename -- "${SCRIPT_ABS_PATH%/*}" )"
# echo "PROJ_WORKSPACE=$PROJ_WORKSPACE"
# echo "PROJ_NAME=$PROJ_NAME"
# exit 0

function usage() {
    echo -e "Usage:\t ${0} [options]" >&2
    echo -e "Options:" >&2
    echo -e "\t -h | --help                                     print this help prompt" >&2
    echo -e "\t -c | --clean                                    clean project [before build if added with -b]" >&2
    echo -e "\t -n | --no_erpc_gen                              do not auto-generate eRPC code" >&2
    echo -e "\t -f <Build Type> | --config <Build Type>         selects which build configuration to use [dfaults to ${PROJ_CONFIG}]" >&2
    echo -e "\t -p <path/to/dir>   | --project <path/to/dir>    use provided project name to build [defaults to ${PROJ_NAME}]" >&2
    echo -e "\t -w <path/to/dir>   | --workspace <path/to/dir>  use provided path to workspace directory [defaults to ${PROJ_WORKSPACE}]" >&2
    echo -e "\t -a <path/to/dir>   | --args_file <path/to/dir>  use provided file for extra Code Composer Studio arguments during compilation" >&2
    echo -e "\t -k <path/to/dir>   | --check <path/to/dir>      use provided path to override project's hardcoded TivaWare drivers & libraries location" >&2
    exit $1
    echo "Uh oh... \"usage\" exiting with 2" && exit 2
}

PROJ_TIVA_CHECK=0
TIVA_LOC=""
OLD_TIVA_LOC="${HOME}/Downloads/TI/TivaWare_C_Series-2.1.4.178"
PROJECT_LOC="${SCRIPT_ABS_PATH%/*}"
function check_project_settings() {
    # Path should only be the 1st argument passed, any other arguments == failure
    (( $# == 1 )) && TIVA_LOC="$1"

    # If path variable "TIVA_LOC" is empty, something went wrong
    if [[ -z "${TIVA_LOC}" ]]; then
        echo "Script was not given path to local TivaWare libraries"
        usage 1
    else
        # Remove existing project files
        rm -rf "${PROJECT_LOC}/.settings/"
        rm -f "${PROJECT_LOC}/.project"
        rm -f "${PROJECT_LOC}/.cproject"
        rm -f "${PROJECT_LOC}/.ccsproject"

        # Copy the project definitions to project location
        cp -rf "${SCRIPT_ABS_PATH}/.settings/" "${PROJECT_LOC}/"
        cp -rf "${SCRIPT_ABS_PATH}/.project" "${PROJECT_LOC}/"
        cp -rf "${SCRIPT_ABS_PATH}/.cproject" "${PROJECT_LOC}/"
        cp -rf "${SCRIPT_ABS_PATH}/.ccsproject" "${PROJECT_LOC}/"

        # Copy git tracked project definitions to temporary file
        cat "${SCRIPT_ABS_PATH}/.project" > "${SCRIPT_ABS_PATH}/tmp"
        # Replace hardcoded with local system's path
        sed -i 's,'${OLD_TIVA_LOC}','${TIVA_LOC}',g' "${SCRIPT_ABS_PATH}/tmp"
        mkdir -p "${PROJECT_LOC}"
        mv "${SCRIPT_ABS_PATH}/tmp" "${PROJECT_LOC}/.project"
    fi

    return 0
}

CLEAN_PROJ=0
BUILD_HAS_ARG_FILE=0
PROJ_ARG_FILE=""
function clean_project() {
    # Make sure this program can actually find CCS
    CCS=$(find ~/ti -name ccstudio -type f -executable -print -quit)
    if [ -x "${CCS}" ]; then
        echo "Using \"${CCS}\" for CCS CLI"
    else
        echo "ERROR: Could not find any installation of Code Composer Studio"
        return 1
    fi

    ${CCS} -noSplash -data "${PROJ_WORKSPACE}" -application com.ti.ccstudio.apps.projectBuild -ccs.projects "${PROJ_NAME}" -ccs.clean

    return 0
}

function compile_project() {
    # Extra CCS options which could be added later:
    #
    # -ccs.projects <name1>[ <name2>]*
    #     Space-separated list of projects to build.
    #
    # -ccs.workspace - use in lieu of -ccs.projects
    #     Build entire workspace. 
    #
    # -ccs.buildType (incremental | full | clean)
    #     The type of build to perform (optional).
    #     Defaults to 'incremental'.

    # Make sure this program can actually find CCS
    CCS=$(find ~/ti -name ccstudio -type f -executable -print -quit)
    if [ -x "${CCS}" ]; then
        echo "Using \"${CCS}\" for CCS CLI"
    else
        echo "ERROR: Could not find any installation of Code Composer Studio"
        return 1
    fi

    # If there's an argument file to use with CCS, provide it (expands out to nothing otherwise)
    [ ${BUILD_HAS_ARG_FILE} ] && PROJ_ARG_FILE="-ccs.args \"${PROJ_ARG_FILE}\""

    # Execute the build with set options
    ${CCS} -noSplash \
        -data "${PROJ_WORKSPACE}" \
        -application com.ti.ccstudio.apps.projectBuild \
        -ccs.projects "${PROJ_NAME}" \
        -ccs.configuration "${PROJ_CONFIG}" \
        -ccs.listProblems \
        ${BUILD_HAS_ARG_FILE}
    
    return 0
}

function find_n_format () {
    OLD_DIR=$(pwd) && cd "${SCRIPT_ABS_PATH}"

    # Directores & files need to be relative to the .clang-format file; adjust as needed
    REL_PATH=".."

    # list of directories to recursively look for files
    declare -a PROJECT_DIRS=(
        # Add more directories as needed
        ${REL_PATH}/app
        ${REL_PATH}/eRPC/erpc_rsi
    )

    # All found files to be formated will be added to this list
    FILES=()

    for dir in "${PROJECT_DIRS[@]}"; do
        # echo "${dir}"
        FILES+=$(find ${dir} -regex '.*\.\(cpp\|hpp\|cc\|cxx\|c\|h\)')
    done

    echo -n "Formating Project Files"
    cd "${SCRIPT_ABS_PATH}"
    for file in "${FILES[@]}"; do
        # echo "${file}"
        echo -n "."
        clang-format -style=file -i ${file}
    done
    cd ${OLD_DIR}
}

# Parse arguments
while : ; do
    case "$1" in
        -h | --help)
            usage 0
            ;;
        -p | --proj_name)
            PROJ_NAME="$2"
            shift 2
            ;;
        -w | --workspace)
            PROJ_WORKSPACE="$2"
            shift 2
            ;;
        -c | --clean)
            CLEAN_PROJ=1
            shift
            ;;
        -a | --args_file)
            BUILD_HAS_ARG_FILE=1
            PROJ_ARG_FILE="$2"
            shift 2
            ;;
        -f | --config)
            PROJ_CONFIG="$2"
            shift 2
            ;;
        -k | --check)
            PROJ_TIVA_CHECK=1
            TIVA_LOC="$2"
            shift 2
            ;;
        --) # end of options
            shift
            break
            ;;
        -*)
            echo "Error: Unknown option: -${1}" >&2
            usage 1
            ;;
        *)
            break
            ;;
    esac
done

# echo "PROJ_NAME=$PROJ_NAME"
# echo "PROJ_WORKSPACE=$PROJ_WORKSPACE"
# echo "PROJ_TIVA_CHECK=$PROJ_TIVA_CHECK"
# echo "CLEAN_PROJ=$CLEAN_PROJ"
# echo "TIVA_LOC=$TIVA_LOC"
# echo "PROJ_CONFIG=$PROJ_CONFIG"
# echo "PROJ_ARG_FILE=$PROJ_ARG_FILE"
# exit 0

# Perform program operations
find_n_format
if (( ${PROJ_TIVA_CHECK} == 1 )); then
    check_project_settings "${TIVA_LOC}" || exit $?
fi
if (( ${CLEAN_PROJ} == 1 )); then
    clean_project || exit $?
fi
compile_project && exit 0

echo "Uh oh... should not have reached this... exit 2" && exit 2
