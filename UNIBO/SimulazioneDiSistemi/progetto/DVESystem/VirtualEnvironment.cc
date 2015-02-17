/*
 * VirtualEnvironment.cc
 *
 *  Created on: 05/feb/2015
 *      Author: Fabio
 */

#include <VirtualEnvironment.h>

// VirtualEnvironment.

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
VirtualEnvironment::add(VirtualAvatar* avatar) {
    int avatarID = avatar->GetID();
    int x = avatar->GetX();
    int y = avatar->GetY();
    cells_[x][y].insert(std::pair<int, VirtualAvatar*>(avatarID, avatar));
}


void
VirtualEnvironment::remove(VirtualAvatar* avatar)
{
    std::map<int, VirtualAvatar*> cell = cells_[avatar->GetX()][avatar->GetY()];
    std::map<int, VirtualAvatar*>::iterator it;
    it = cell.find(avatar->GetID());
    cell.erase(it);
}


void
VirtualEnvironment::move(VirtualAvatar* avatar, int x, int y)
{
    // See which cell it was in.
    int oldCellX = avatar->GetX();
    int oldCellY = avatar->GetY();
    // If it didn't change cells, we're done.
    if (oldCellX == x && oldCellY == y) return;
    // Else we remove the avatar from that cell.
    remove(avatar);
    // Update the avatar.
    avatar->SetX(x);
    avatar->SetY(y);
    add(avatar);
}


void
VirtualEnvironment::erase(VirtualAvatar* avatar)
{
    remove(avatar);
    delete avatar;
}


void
VirtualEnvironment::GetAvatarAndSizeAt(int x, int y, int* avatars, unsigned int& size)
{
    std::vector<int> clients;
    std::map<int, VirtualAvatar*>::iterator it;
    for (it = cells_[x][y].begin(); it != cells_[x][y].end(); it++)
    {
        clients.push_back(it->first);
    }
    size = clients.size();
    avatars = &clients[0];
}
