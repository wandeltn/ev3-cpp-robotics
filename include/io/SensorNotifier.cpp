#include "SensorNotifier.hpp"

bool ListenerTableRow::firstRead = true;

std::vector<std::function<void(std::map<subscriber_port, int>, std::map<subscriber_port, int>)>> SensorNotifier::_listeners{};

port_listener_table SensorNotifier::_lookup_table = port_listener_table{
    ListenerTableRow{input_1, "input_port-1"},
    ListenerTableRow{input_2, "input_port-2"},
    ListenerTableRow{input_3, "input_port-3"},
    ListenerTableRow{input_4, "input_port-4"},
    ListenerTableRow{output_A, "output_port-A"},
    ListenerTableRow{output_B, "output_port-B"},
    ListenerTableRow{output_C, "output_port-C"},
    ListenerTableRow{output_D, "output_port-D"}
};


SensorNotifier::SensorNotifier()
{
    readPorts();
}

SensorNotifier::~SensorNotifier()
{
}

std::list<void(*)(int)>::iterator SensorNotifier::subscribeToChange(subscriber_port device_port, void(*callback)(int))
{
    for (ListenerTableRow& row : _lookup_table) {
        if (row.portName == device_port) {
            row.listeners.push_back(callback);
            std::cout << "subscribedToChange(): " << row.deviceIdentifier << "\n";
            return row.listeners.end();
        }
    }
    return std::list<void(*)(int)>::iterator{};
}

void SensorNotifier::subscribeToAllChanges(std::function<void(std::map<subscriber_port, int>, std::map<subscriber_port, int>)> callback)
{
    _listeners.push_back(callback);
}

void SensorNotifier::unsubscribeFromChange(std::list<void(*)(int)>::iterator callback, subscriber_port device_port)
{
    for (ListenerTableRow& row : _lookup_table) {
        if (row.portName == device_port) {
            row.listeners.erase(callback);
        }
    }
    std::cout << "unsubscribing someone from: " << device_port << "\n";
}

int SensorNotifier::Dispatcher(bool dispatch)
{
    std::map<subscriber_port, int> tempMapPrev = {};
    for (ListenerTableRow row : _lookup_table) {
        tempMapPrev[row.portName] = row.previousValue;
    }

    for (ListenerTableRow& device : _lookup_table) {
        if (!device.portName.length()) {
            std::cout << "skipping disconnected device: " << device.deviceIdentifier << std::endl;
            continue;
        }
        // FILE* fp;
        std::ifstream ifs;

        if (device.portName.find("motor") == std::string::npos) {
            ifs.open(device.portName + "/value0");
        } else {
            ifs.open(device.portName + "/position");
        }

        if(!ifs.is_open()){
            std::cout << "skipping device: " << device.deviceIdentifier + "/position" << std::endl;
            continue;
        }

        std::string value{};
        getline(ifs, value);
        int numValue = std::stoi(value);

        if (device.deviceIdentifier == "input_port-3") {
            numValue += gyroValueOffset;
        }

        if (numValue != device.previousValue) {
                if (dispatch) {
                    for (std::function<void(int)> listener : device.listeners) {
                        try
                        {
                            listener(numValue);
                        }
                        catch(const std::exception& e)
                        {
                            std::cerr << e.what() << '\n';
                    }
                }
            }
            device.previousValue = numValue;
        }
    }
    if (dispatch) {
        std::map<subscriber_port, int> tempMap = {};
        for (ListenerTableRow row : _lookup_table) {
            tempMap[row.portName] = row.previousValue;
        }
        for (auto listener : _listeners) {
            listener(tempMap, tempMapPrev);
        }
    } else {
        _lookup_table.begin()->firstRead = false;
    }
    return 1;
}

std::map<std::string, int> SensorNotifier::getCurrentValues()
{
    return static_cast<std::map<std::string, int>>(_lookup_table);
}

const std::map<std::string, std::string> SensorNotifier::getDevices()
{
    return _lookup_table.getFilePaths();
}
