#include "port_finder.hpp"


PortFinder::PortFinder()
{
    std::cout << "Port finder has been created.\n";
}

PortFinder::~PortFinder()
{
    std::cout << "Port finder has been deleted.\n";
}

std::string PortFinder::execute_command(std::string command)
{
    memset(command_buffer_, 0, 127);

    std::string command_return = "";

    FILE *pipe = popen(command.c_str(), "r");

    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        exit(1);
    }

    try
    {
        while (fgets(command_buffer_, sizeof(command_buffer_), pipe) != NULL) {
            command_return = command_return + command_buffer_;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        pclose(pipe);
        throw e;
    }

    pclose(pipe);
    
    return command_return;
}

std::vector<std::string> PortFinder::list_all_ports(std::string port_directory)
{
    std::string list_command = "ls -p " + port_directory + " | grep -v /";
    std::string ports = execute_command(list_command);

    std::vector<std::string> port_list;
    std::stringstream ss(ports);
    std::string port;

    while (ss >> port) {
        port_list.push_back(port);
    }

    return port_list;
}

std::string PortFinder::find_id_vendor(std::string port)
{
    std::string find_id_vendor_command = "udevadm info --name " + port + " | grep -i ID_VENDOR=";
    std::string command_return = execute_command(find_id_vendor_command);

    size_t seperator_pos = command_return.find("ID_VENDOR=");
    
    if(seperator_pos == std::string::npos) {
        // Unknown device
        return "";
    }

    std::string id_vendor = command_return.substr(seperator_pos + std::string("ID_VENDOR=").size());

    // remove '\n' from end of id_vendor
    if (!id_vendor.empty()) {
        id_vendor.erase(id_vendor.size() - 1);
    }

    return id_vendor;
}

std::string PortFinder::find_id_vendor_id(std::string port)
{
    std::string find_id_vendor_id_command = "udevadm info --name " + port + " | grep -i ID_VENDOR_ID=";
    std::string command_return = execute_command(find_id_vendor_id_command);

    size_t seperator_pos = command_return.find("ID_VENDOR_ID=");
    
    if(seperator_pos == std::string::npos) {
        // Unknown device
        return "";
    }

    std::string id_vendor_id = command_return.substr(seperator_pos + std::string("ID_VENDOR_ID=").size());

    // remove '\n' from end of id_vendor_id
    if (!id_vendor_id.empty()) {
        id_vendor_id.erase(id_vendor_id.size() - 1);
    }

    return id_vendor_id;
}

std::string PortFinder::find_id_model_id(std::string port)
{
    std::string find_id_model_id_command = "udevadm info --name " + port + " | grep -i ID_MODEL_ID=";
    std::string command_return = execute_command(find_id_model_id_command);

    size_t seperator_pos = command_return.find("ID_MODEL_ID=");
    
    if(seperator_pos == std::string::npos) {
        // Unknown device
        return "";
    }

    std::string id_model_id = command_return.substr(seperator_pos + std::string("ID_MODEL_ID=").size());

    // remove '\n' from end of id_model_id
    if (!id_model_id.empty()) {
        id_model_id.erase(id_model_id.size() - 1);
    }

    return id_model_id;
}

std::string PortFinder::find_id_path(std::string port)
{
    std::string find_id_path_command = "udevadm info --name " + port + " | grep -i ID_PATH=";
    std::string command_return = execute_command(find_id_path_command);

    size_t seperator_pos = command_return.find("ID_PATH=");
    
    if(seperator_pos == std::string::npos) {
        // Unknown device
        return "";
    }

    std::string id_path = command_return.substr(seperator_pos + std::string("ID_PATH=").size());

    // remove '\n' from end of id_path
    if (!id_path.empty()) {
        id_path.erase(id_path.size() - 1);
    }

    return id_path;
}

std::string PortFinder::find_device_name(std::string port)
{
    std::string find_device_name_command = "udevadm info --name " + port + " | grep -i DEVNAME=";
    std::string command_return = execute_command(find_device_name_command);

    size_t seperator_pos = command_return.find("DEVNAME=");
    
    if(seperator_pos == std::string::npos) {
        // Unknown device
        return "";
    }

    std::string device_name = command_return.substr(seperator_pos + std::string("DEVNAME=").size());

    // remove '\n' from end of device_name
    if (!device_name.empty()) {
        device_name.erase(device_name.size() - 1);
    }

    return device_name;
}

std::string PortFinder::find_port(std::string port_directory, std::string id_vendor, std::string id_vendor_id, std::string id_model_id, std::string id_path, bool keep_search)
{
    std::vector<std::string> port_list = list_all_ports(port_directory);
    std::string port_name = "";

    for (const auto port : port_list) {
        if (id_path == "NO") {
            if (find_id_vendor(port) == id_vendor && find_id_vendor_id(port) == id_vendor_id && find_id_model_id(port) == id_model_id) {
                port_name = find_device_name(port);
                std::cout << "Port is founded: " << port_name << std::endl;

                return port_name;
            }
        }
        else {
            if (find_id_vendor(port) == id_vendor && find_id_vendor_id(port) == id_vendor_id && find_id_model_id(port) == id_model_id && find_id_path(port) == id_path) {
                port_name = find_device_name(port);
                std::cout << "Port is founded: " << port_name << std::endl;

                return port_name;
            }
        }
    }

    if (keep_search && port_name.empty()) {
        return find_port(port_directory, id_vendor, id_vendor_id, id_model_id, id_path);
    }

    std::cout << "Cannot found port." << std::endl;
    return port_name;
}