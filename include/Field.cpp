#include "Field.hpp"
#include <fstream>


Field::Field()
{
}

void Field::exportField()
{
    std::ofstream file;
    file.open(FIELD_EXPORT_PATH);
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
    }
    
}
