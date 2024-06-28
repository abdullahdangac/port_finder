#ifndef PORT_FINDER_HPP
#define PORT_FINDER_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>


class PortFinder {
  public:
    /**
     * Constructor
     */
    PortFinder();

    /**
     * Deconstructor
     */
    ~PortFinder();

    /**
     * Executes the given command
     * 
     * @param command Command to execute
     * @return Return of the executed command
     */
    std::string execute_command(std::string command);

    /**
     * Lists all ports in the given port directory
     * 
     * @param port_directory Port directory containing ports to list
     * @return List of all ports
     */
    std::vector<std::string> list_all_ports(std::string port_directory);

    /**
     * Finds the ID Vendor of the device on the given port
     * 
     * @param port Port to be find ID Vendor
     * @return ID Vendor of given port
     */
    std::string find_id_vendor(std::string port);

    /**
     * Finds the ID Vendor ID of the device on the given port
     * 
     * @param port Port to be find ID Vendor ID
     * @return ID Vendor ID of given port
     */
    std::string find_id_vendor_id(std::string port);

    /**
     * Finds the ID Model ID of the device on the given port
     * 
     * @param port Port to be find ID Model ID
     * @return ID Model ID of given port
     */
    std::string find_id_model_id(std::string port);

    /**
     * Finds the ID Path of the device on the given port
     * 
     * @param port Port to be find ID Path
     * @return ID Path of given port
     */
    std::string find_id_path(std::string port);

    /**
     * Finds the device name of the device on the given port
     * 
     * @param port Port to be find device name
     * @return Port name of given port
     */
    std::string find_device_name(std::string port);

    /**
     * Finds the port name of the device that given its ID Vendor, ID Vendor ID, ID Model ID, ID Path
     * 
     * @param port_directory Port directory to search
     * @param id_vendor ID Vendor of device to find port name
     * @param id_vendor_id ID Vendor ID of device to find port name
     * @param id_model_id ID Model ID of device to find port name
     * @param id_path ID Path of device to find port name (default argument)
     * @param keep_search Flag that determines whether to continue searching until the port is found
     * @return Port name of searched device
     */
    std::string find_port(std::string port_directory, std::string id_vendor, std::string id_vendor_id, std::string id_model_id, std::string id_path="NO", bool keep_search=true);

  private:
    char command_buffer_[128];  //!< Buffer for commands to be executed
};


#endif /* PORT_FINDER_HPP */