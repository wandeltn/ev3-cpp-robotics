#include "UserInterface.hpp"

Window* UserInterface::_window;

UserInterface::UserInterface()
{
    _window = DRM.createWindow(
        USER_INTERFACE_X0,
        USER_INTERFACE_Y0,
        USER_INTERFACE_X1,
        USER_INTERFACE_Y1,
        true
    );
}

void UserInterface::render()
{
    
}

void UserInterface::update()
{

}

