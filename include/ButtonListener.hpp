#ifndef __ButtonListener_H__
#define __ButtonListener_H__

class ButtonListener {
    private:

    public:
        ButtonListener();

        virtual void onButtonBackPressed();
        virtual void onButtonEnterPressed();
        virtual void onButtonUpPressed();
        virtual void onButtonDownPressed();
        virtual void onButtonLeftPressed();
        virtual void onButtonRightPressed();
};


#endif // __ButtonListener_H__