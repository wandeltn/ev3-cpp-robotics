#include "Field.hpp"
#include <fstream>

std::array<unsigned char, FIELD_WIDTH * FIELD_HEIGHT> Field::_field_map = {};

Field::Field()
{
    _field_map.fill(0);    
}

void Field::exportField()
{
    std::ofstream file;
    file.open(FIELD_EXPORT_PATH);
    for (unsigned char tile : _field_map) {
        file << tile << "\n";
    }
    file.close();
}

void Field::importField()
{
    std::ifstream file;
    std::string line;
    uint array_index = 0;
    file.open(FIELD_EXPORT_PATH);
    while (getline(file, line))
    {
        _field_map[array_index++] = static_cast<unsigned char>(line.c_str()[0]);
    }
    
}
