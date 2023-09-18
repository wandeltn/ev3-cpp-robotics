#include "SensorNotifier.hpp"


std::thread SensorNotifier::_polling_thread;
std::vector<std::function<void(std::map<subscriber_port, int>)>> SensorNotifier::_listeners{};
std::atomic<bool> SensorNotifier::_run_thread;
std::atomic<bool> SensorNotifier::_thread_running;

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
    _run_thread.store(true);
    // auto thread = std::async(std::launch::async, &SensorNotifier::Dispatcher, this);
    _polling_thread = std::thread{&SensorNotifier::Dispatcher, this};
    _polling_thread.detach();
    // Dispatcher();
}

SensorNotifier::~SensorNotifier()
{
    _run_thread.store(false);
    // _polling_thread.join();
}

std::list<void(*)(int)>::iterator SensorNotifier::subscribeToChange(subscriber_port device_port, void(*callback)(int))
{
    for (ListenerTableRow& row : _lookup_table) {
        if (row.portName == device_port) {
            row.listeners.push_back(callback);
            return row.listeners.end();
        }
    }
    return std::list<void(*)(int)>::iterator{};
}

void SensorNotifier::subscribeToAllChanges(std::function<void(std::map<subscriber_port, int>)> callback)
{
    _listeners.push_back(callback);
}

void SensorNotifier::unsubscribeFromChange(std::list<void(*)(int)>::iterator callback)
{
    for (ListenerTableRow& row : _lookup_table) {
        row.listeners.erase(callback);
    }
}

int SensorNotifier::Dispatcher()
{
    _thread_running = true;
    while (_run_thread) {
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
                if (gyroValueOffset == 0) {
                    gyroValueOffset = -numValue;
                    std::cout << "set new offset: " << gyroValueOffset << std::endl;
                }
                numValue += gyroValueOffset;
            }

            if (numValue != device.previousValue) {
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
                device.previousValue = numValue;
            }
        }
        std::map<subscriber_port, int> tempMap = {};
        for (ListenerTableRow row : _lookup_table) {
            tempMap[row.portName] = row.previousValue;
        }
        for (std::function<void(std::map<subscriber_port, int>)> listener : _listeners) {
            listener(tempMap);
        }
    }
    _thread_running = false;
    return 1;
}

void SensorNotifier::stopDispatcher()
{
    _run_thread.store(false);
}

void SensorNotifier::startDispatcher()
{
    _run_thread.store(true);
    _polling_thread = std::thread(&SensorNotifier::Dispatcher, this);
    _polling_thread.detach();
}

void SensorNotifier::waitForThreadStop()
{
    while (_thread_running)
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);
    }
}
