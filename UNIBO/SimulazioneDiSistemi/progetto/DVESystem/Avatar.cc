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

int
Avatar::GetX()
{
    return x_;
}

int
Avatar::GetY()
{
    return y_;
}

unsigned int
Avatar::GetAoISize()
{
    return aoi_.size();
}

int
Avatar::GetAtAoi(unsigned int index)
{
    return aoi_[index];
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
        if (newAoI[i] != ID_)
        {
            // Ensure Avatar AoI does not contains Avatar itself.
            aoi_.push_back(newAoI[i]);
        }
    }
}

void
Avatar::removeFromAOI(int avatarID)
{
    std::vector<int>::iterator it;
    it = std::find(aoi_.begin(), aoi_.end(), avatarID);
    if (it != aoi_.end())
    {
        aoi_.erase(it);
    }
}

void
Avatar::addToAOI(int avatarID)
{
    if (avatarID != ID_)
    {
        // Ensure Avatar AoI does not contains Avatar itself.
        aoi_.push_back(avatarID);
    }
}
