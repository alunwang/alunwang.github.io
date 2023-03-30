# Purpose


# Usage
Untar the package for this project:
```
$ tar zxvf byte2Json.tar.gz
$ cd byte2Json

$ mkdir build
$ cd build

$ cmake ..

$ make

$ ./src/byte2Json
```
```
{
    "co2":600,
    "errCode":0,
    "errType":0,
    "error":false,
    "reserved":55,
    "id":8,
    "segment":3,
    "reserved2":135
}
{
    "co2":772,
    "errCode":2,
    "errType":0,
    "error":true,
    "reserved":73,
    "id":258,
    "segment":4,
    "reserved2":19
}
```

# Notes
The project is compiled and tested on the environment:
- Ubuntu-22.04 on WSL2
- gcc/g++ 12.1.0
- cmake 3.22.1
- C++20

# Appendix
In the project, two 3rd-party libraries are employed. Both of them are compiled into the project statically:
- [rapidjson](https://github.com/Tencent/rapidjson)
- base64_decode

# Known bug
- Compilation warning:
There are some warning messages  during compilation. These warning messages come from the 3rd-party library rapidjson.