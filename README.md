# Port Finder
This package finds the port name of a desired device.  
<br />  

## Package Usage Example
```
#include <string>
#include <vector>
#include <port_finder/port_finder.hpp>

using namespace std;

int main(void)
{
    // Information of the device to be searched
    string port_directory = "/dev";
    string ID_VENDOR = "u-blox_AG_-_www.u-blox.com";
    string ID_VENDOR_ID = "1546";
    string ID_MODEL_ID = "01a9";
    string ID_PATH = "pci-0000:00:14.0-usb-0:1:0.0";

    // Port Finder
    PortFinder port_finder;

    // Finding port name of the searched device
    string port_name = port_finder.find_port(port_directory, ID_VENDOR, ID_VENDOR_ID, ID_MODEL_ID, "NO", false);

    return 0;
}
```
### Note for parameters
- **ID_Path:** *ID_Path* should not be used if the device is constantly plugged into different ports. To do this, ***"NO"*** must be sent as argument to *ID_Path* parameter.  
- **keep_search:** If you want to continue searching until the port is found, ***true*** must be sent as argument to the *keep_search* parameter.  
<br />  

## CMakeLists.txt
```
...

find_package(port_finder REQUIRED)

add_executable(example src/main.cpp)
target_link_libraries(example port_finder::port_finder_lib) 
ament_target_dependencies(example port_finder)

...
```
<br />  

## Finding Device Information for Package
#### To find ID Vendor
```
udevadm info --name <port_name> | grep -i ID_VENDOR=
```
#### To find ID Vendor ID
```
udevadm info --name <port_name> | grep -i ID_VENDOR_ID=
```
#### To find ID Model ID
```
udevadm info --name <port_name> | grep -i ID_MODEL_ID=
```
#### To find ID Path
```
udevadm info --name <port_name> | grep -i ID_PATH=
```  

<br />  

### Repository
https://github.com/abdullahdangac/port_finder