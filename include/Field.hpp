#ifndef __FIELD_H__
#define __FIELD_H__

#include <array>

#define FIELD_WIDTH     2000
#define FIELD_HEIGHT    1000
#define FIELD_EXPORT_PATH "/home/robot/field_export.txt"

class Field {
    private:
        static std::array<unsigned char, FIELD_WIDTH * FIELD_HEIGHT> _field_map;

        void exportField();
        void importField();

    public:
        Field();

};

#endif // __FIELD_H__