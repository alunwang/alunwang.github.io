# Environment
- Ubuntu on WSL2
- Vscode
- imx8 board
- Source code in Ubuntu and opened with Vscode


# Need to install
- Remote-SSH extension on Vscode
- Cross gdb client aarch64-none-linux-gnu-gdb on Ubuntu. The cross gdb is downloaded from [here](https://developer.arm.com/downloads/-/gnu-a)
- Native gdbserver on imx8 boar


# Configuration on Vscode
- F1 ->Remote-SSH: Open SSH Configuration File... ->Select SSH configuration file to dupate ->Select "C:\Users\lunshneg.wang\.ssh\config", update its content with:
Host imx8 # Target name, can be any
    HostName 172.16.0.2 # imx8 board's IP
    User root   # The account used to connect to imx8
- Configure launch.json file for the project with:
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "/home/alan/vStream/build/vStream",  // The program to debug on imx8
            "args": [],
            "stopAtEntry": false,
            "miDebuggerPath": "/home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gdb", // Cross debug in PC
            "miDebuggerServerAddress": "172.16.0.2:1234",   // imx8's IP:Port
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Set Disassembly Flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}

# Initiate remote debugging
- On imx8: # gdbserver :1234 vStream
- On Vscode: F5 (Start Debugging)
