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

There are VS Code configuration files included in `.vscode/` for those like me who prefer VSCode as an IDE. It might be needed to do a build in CCS before these work. Update necessary input variables in `.vscode/tasks.json` to match your specific project paths. See `.vscode/<CONFIGURATION>_build.log` for any build errors.
