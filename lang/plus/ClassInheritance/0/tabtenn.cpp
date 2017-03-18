// tabtenn.cpp -- simple base-class methods

#include <iostream>
#include "tabtenn.h"

TableTennisPlayer::TableTennisPlayer(const std::string &fn,
                                     const std::string &ln,
                                     bool ht)
    : firstname(fn), lastname(ln), hasTable(ht) {}

void TableTennisPlayer::Name() const
{
    std::cout << lastname << ", " << firstname;
}
