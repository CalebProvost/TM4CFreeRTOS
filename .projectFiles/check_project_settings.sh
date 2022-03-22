#!/bin/bash

# Make sure this program only executes within the repo's root directory
SCRIPT_ABS_PATH="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
if [[ "$(basename ${SCRIPT_ABS_PATH})" != ".projectFiles" ]]; then
    echo "This script cannot run from \"${SCRIPT_ABS_PATH}\". It must be stored in and ran from \"\${REPO_DIR}/.projectFiles\"."
    exit 1
fi

function usage() {
    echo -e "Usage:\t ${0} [options] ~/path/to/tivaware" >&2
    echo -e "Options:" >&2
    echo -e "\t -h | --help             \t print this help prompt" >&2
    echo -e "\t -p | --proj_name <NAME> \t project & directory that CCS will import as" >&2
    echo -e "\t -w | --workspace <NAME> \t workspace directory that CCS will use/create" >&2
    echo -e "\t -c | --open_ccs         \t Auto launch & import project into CCS" >&2
    exit $1
    echo "Uh oh... \"usage\" exiting with 2" && exit 2
}

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
}

OPEN_CCS=0
PROJ_NAME="TM4CFreeRTOS"
PROJ_WORKSPACE="ccs_workspace"
function import_and_launch_ccs() {
    if (( $OPEN_CCS == 1 )); then
        echo
        echo "Note: CCS will create a new workspace in \"${SCRIPT_ABS_PATH%/*}/${PROJ_WORKSPACE}\"."
        echo "Note: It'll then copy all appropriate project contents to it and launch with that location."
        echo "Note: ANY GIT CHANGES IN \"${SCRIPT_ABS_PATH%/*}/ccs_workspace\" WILL NOT BE SEEN!!! CHANGE INTO NEW DIRECTORY!!!"
        echo

        CCS=$(find ~/ti -name ccstudio -type f -executable -print -quit)
        PROJECT_LOC="${PROJECT_LOC}/${PROJ_WORKSPACE}/${PROJ_NAME}"
        mkdir -p "${PROJECT_LOC}"
        check_project_settings "$1"

        cd ${SCRIPT_ABS_PATH%/*}
        cp -rf .projectFiles/ ${PROJECT_LOC}/
        cp -rf .git/ ${PROJECT_LOC}/
        cp -rf app/ ${PROJECT_LOC}/
        cp -rf FreeRTOS/ ${PROJECT_LOC}/
        cp -rf targetConfigs/ ${PROJECT_LOC}/

        if [[ ! -d "${PROJ_WORKSPACE}/.metadata/.plugins/org.eclipse.core.resources/.projects/${PROJ_NAME}" ]]; then
            $CCS -data "${PROJ_WORKSPACE}" -application com.ti.ccstudio.apps.projectImport -noSplash -ccs.location "${PROJ_WORKSPACE}/${PROJ_NAME}"
        fi
        $CCS -data "${PROJ_WORKSPACE}" -ccs.autoImport -ccs.projects "${PROJ_NAME}"
    fi
    return 0
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
        -c | --open_ccs)
            OPEN_CCS=1
            shift
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
# echo "OPEN_CCS=$OPEN_CCS"
# echo "TIVA_LOC=$1"

# Run script
check_project_settings "$1"
import_and_launch_ccs "$1" && exit 0
echo "Uh oh... should not have reached this... exit 2" && exit 2
