/*
 * VirtualEnvironment.h
 *
 *  Created on: 05/feb/2015
 *      Author: Fabio
 */

#ifndef VIRTUALENVIRONMENT_H_
#define VIRTUALENVIRONMENT_H_

#include <map>

class VirtualEnvironment {
private:
    // The side size of the grid (square).
    static const int NUM_CELLS = 10;
    // The virtual environment is essentially a grid of virtual avatars.
    std::map<int, VirtualAvatar*> cells_[NUM_CELLS][NUM_CELLS];
public:
    VirtualEnvironment();
    virtual ~VirtualEnvironment();
    int GetIndexMax();
    void add(int avatarID, int x, int y);
    void remove(int avatarID);
    void move(int avatarID, int x, int y);
};


class VirtualAvatar {
    friend class VirtualEnvironment;
private:
    int x_, y_, ID_;
    VirtualEnvironment* ve_;
public:
    VirtualAvatar(VirtualEnvironment* ve, int id, int x, int y);
    void move(int x, int y);
};

#endif /* VIRTUALENVIRONMENT_H_ */
