#include "PortsInput.hpp"

Rope PortsInput::_rope = Rope{};
bool PortsInput::_button_thread_registered = false;
std::vector<std::shared_ptr<ButtonListener>> PortsInput::_button_listeners;

PortsInput::PortsInput()
{
    if (!_button_thread_registered) {
        _rope.create(&buttonCallback);
        _button_thread_registered = true;
    }
}

void PortsInput::buttonCallback()
{
    if (_button_back.process_all()) {
        if (_button_enter.process()) {
            for (std::shared_ptr<ButtonListener> listener : _button_listeners) {
                listener->onButtonBackPressed();
            }
        }
    }
}

void PortsInput::registerButtonListener(std::shared_ptr<ButtonListener> listener)
{
    _button_listeners.push_back(listener);    
}
