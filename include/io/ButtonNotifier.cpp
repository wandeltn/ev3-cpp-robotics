#include "ButtonNotifier.hpp"

std::ifstream ButtonNotifier::_ifstream = std::ifstream{};
__u16 ButtonNotifier::_previous_key;
std::mutex ButtonNotifier::_mutex;
std::unique_ptr<ButtonNotifier> ButtonNotifier::_pinstance;

ButtonNotifier::ButtonNotifier()
{
    _ifstream.open(EVENT_PATH, std::ios::in|std::ios::binary);
    if (!_ifstream.is_open()) {
        throw(new std::invalid_argument{"Error while opening /dev/input/by-path/platform-gpio_keys-event!"});
    }
}

std::unique_ptr<ButtonNotifier>& ButtonNotifier::GetInstance()
{
    std::lock_guard<std::mutex> lock(_mutex);
        if (_pinstance == nullptr)
    {
        _pinstance = std::unique_ptr<ButtonNotifier>(new ButtonNotifier());
    }
    return _pinstance;
}

void ButtonNotifier::Dispatcher()
{
    struct input_event ie;
    

    _ifstream.read((char*)&ie, sizeof(ie));
    std::cout << "code: " << ie.code << std::endl;
    std::cout << "time: " << ie.time.tv_sec << std::endl;
    std::cout << "type: " << ie.type << std::endl;
    std::cout << "value: " << ie.value << std::endl;

    switch (ie.code)
    {
    case KEY_BACK:  onButtonBackPressed();  break;
    case KEY_ENTER: onButtonEnterPressed(); break;
    case KEY_UP:    onButtonUpPressed();    break;
    case KEY_DOWN:  onButtonDownPressed();  break;
    case KEY_LEFT:  onButtonLeftPressed();  break;
    case KEY_RIGHT: onButtonRightPressed(); break;
    case KEY_RESERVED:
        switch (_previous_key)
        {
        case KEY_BACK:  onButtonBackReleased();     break;
        case KEY_ENTER: onButtonEnterReleased();    break;
        case KEY_UP:    onButtonUpReleased();       break;
        case KEY_DOWN:  onButtonDownReleased();     break;
        case KEY_LEFT:  onButtonLeftReleased();     break;
        case KEY_RIGHT: onButtonRightReleased();    break;   
        default:
            break;
        }
    default:
        break;
    }
    _previous_key = ie.code;
}

void ButtonNotifier::onButtonBackPressed()
{
}

void ButtonNotifier::onButtonEnterPressed()
{
    
}

void ButtonNotifier::onButtonUpPressed()
{
    
}

void ButtonNotifier::onButtonDownPressed()
{
    
}

void ButtonNotifier::onButtonLeftPressed()
{
    
}

void ButtonNotifier::onButtonRightPressed()
{
    
}

void ButtonNotifier::onButtonBackReleased()
{
    
}

void ButtonNotifier::onButtonEnterReleased()
{
    
}

void ButtonNotifier::onButtonUpReleased()
{
    
}

void ButtonNotifier::onButtonDownReleased()
{
    
}

void ButtonNotifier::onButtonLeftReleased()
{
    
}

void ButtonNotifier::onButtonRightReleased()
{
    
}
