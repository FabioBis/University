/*
 * Avatar.cc
 *
 *  Created on: 18/gen/2015
 *      Author: Fabio Biselli
 */

#include <Avatar.h>


Avatar::Avatar(int id, int x, int y)
: ID_(id), x_(x), y_(y) {
    ; // Nothing else to do.
}

int
Avatar::GetID()
{
    return ID_;
}

void
Avatar::move(int x, int y)
{
    x_ = x;
    y_ = y;
}

void
Avatar::updateAOI(int* newAoI, int aoiSize)
{
    aoi_.clear();
    for (int i = 0; i < aoiSize; i++)
    {
        aoi_.push_back(newAoI[i]);
    }
}
