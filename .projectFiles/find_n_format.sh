#!/bin/bash

# Make sure this program only executes within the repo's root directory
SCRIPT_ABS_PATH="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
if [[ "$(basename ${SCRIPT_ABS_PATH})" != ".projectFiles" ]]; then
    echo "This script cannot run from \"${SCRIPT_ABS_PATH}\". It must be stored in and ran from \"\${REPO_DIR}/.projectFiles\"."
    exit 1
fi

# Directores & files need to be relative to the .clang-format file; adjust as needed
REL_PATH=".."

# list of directories to recursively look for files
declare -a PROJECT_DIRS=(
    # Add more directories as needed
    ${REL_PATH}/app
)

OLD_DIR=$(pwd) && cd ${SCRIPT_ABS_PATH}
echo -n "Formating Project Files"
for dir in ${PROJECT_DIRS[@]}; do
    FILES=$(find ${dir} -regex '.*\.\(cpp\|hpp\|cc\|cxx\|c\|h\)')
    for file in ${FILES[@]}; do
        echo -n "."
        clang-format -style=file -i ${file}
    done
done

cd ${OLD_DIR}

echo "done"
