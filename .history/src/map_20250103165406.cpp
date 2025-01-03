#include "map.h"

Map::Map(size_t size_of_sliding_window)
    : size_of_sliding_window_(size_of_sliding_window){}

Map::~Map() {}

size_t Map::sizeOfSlidingWindow() const{
    return size_of_sliding_window_;
}
