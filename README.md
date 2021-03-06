# FreeRTOS 10.3.0 on TM4C

This repo is a starting point for building FreeRTOS applications on the TM4C (Tiva TM4C123GH6PM (EK-TM4C123GXL) tested).  
`main.cpp` is loaded with a FreeRTOS blinky/switch demo.  

# How To Import (Linux tested)

1. Install TI's `TivaWare_C_Series-2.1.4.178` library or unzip the one I've provided from my Linux system [here](https://drive.google.com/file/d/1_NxkyTxaSYqtyggAIKByv2DX5U_bKC-H/view?usp=sharing) (Linux: recommended directory is `~/ti/TivaWare_C_Series-2.1.4.178`)
2. Import into Code Composure Studio (CCS) (do not automatically copy referenced sources, results may vary if selecting copy source files into workspace).
3. Adjust CCS project definitions as needed (right click on project name or <kbd>alt+enter</kbd>)
4. (Optional/As Needed) Update the CCS flashing/debugging target defintions in `targetConfigs/` if your device differs

# Tools and Extras

Included in `.projectFiles` are some scripts to help adjust project paths and original project defining files (CCS) as a backup.  
`.projectFiles/check_project_settings.sh` is a helpful scipt to setup a the correct paths for variables before importing the CCS project (recommened for windows). You can optionally use it to automatically import the project and launch CCS: `./.projectFiles/check_project_settings.sh -c ~/ti/tivaware`  

There are VS Code configuration files included in `.vscode/` for those like me who prefer VS Code as an IDE. **Make sure you have jq installed** (`sudo apt install -y jq`).  
In order for the VSCode build tasks to work, it needs to nested within a CCS workspace. Feel free to modify the CCS build argument in `.vscode/tasks.json` to point to your workspace if you choose to do it another way.  
The easiest way to get VS Code to be your IDE instead of CCS is to:  
1. Open CCS and import the project, close it after it successfully builds
2. Open VS Code and open the directory that CCS imported (should be this entire repo)
3. Update any paths and versions in `.vscode/c_cpp_properties.json` (should only need to modify the "env" section)
4. Use VS Code's tasks to build! (<kbd>ctrl+shift+p</kbd> tasks: Run Task)

See `.vscode/<CONFIGURATION>_build.log` for any build errors.
