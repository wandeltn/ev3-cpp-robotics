#ifndef __BUTTONNOTIFIABLE_H__
#define __BUTTONNOTIFIABLE_H__

class ButtonNotifiable {
    private:

    public:
        ButtonNotifiable();

        virtual void onButtonBackPressed();
        virtual void onButtonEnterPressed();
        virtual void onButtonUpPressed();
        virtual void onButtonDownPressed();
        virtual void onButtonLeftPressed();
        virtual void onButtonRightPressed();
};


#endif // __BUTTONNOTIFIABLE_H__