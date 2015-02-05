/*
 * Avatar.h
 *
 *  Created on: 18/gen/2015
 *      Author: Fabio Biselli
 */

#ifndef AVATAR_H_
#define AVATAR_H_

#include <vector>

class Avatar {
private:
    // Unique id.
    int ID_;
    // x coordinate value.
    int x_;
    // y coordinate value.
    int y_;
    // A vector of avatar's ID within *this* Avatar AoI.
    std::vector<int> aoi_;
public:
    Avatar(int id, int x, int y);
    int GetID();
    void move(int x, int y);
    void updateAOI(int* newAoI, int aoiSize);
};

#endif /* AVATAR_H_ */
