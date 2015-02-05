/*
 * VirtualEnvironment.cc
 *
 *  Created on: 05/feb/2015
 *      Author: Fabio
 */

#include <VirtualEnvironment.h>

VirtualEnvironment::VirtualEnvironment() {
    ;
}

VirtualEnvironment::~VirtualEnvironment() {
    ;
}

int
VirtualEnvironment::GetIndexMax() {
    return this->NUM_CELLS;
}


void
VirtualEnvironment::add(int avatarID, int x, int y) {
    // In a real server implementation we should check the uniqueness of ids.
    VirtualAvatar* newAvatar = new VirtualAvatar(this, avatarID, x, y);
    cells_[x][y].insert(std::pair<avatarID, newAvatar>);
}


void
VirtualEnvironment::remove(int avatarID);


void
VirtualEnvironment::move(int avatarID, int x, int y);
