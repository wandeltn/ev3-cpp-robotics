#ifndef __FIELD_H__
#define __FIELD_H__

#include <array>

#define FIELD_WIDTH     2000
#define FIELD_HEIGHT    1000

class Field {
    private:
        static std::array<unsigned char, FIELD_WIDTH * FIELD_HEIGHT> _field_map;

    public:
        Field();

        void exportField();
};

#endif // __FIELD_H__