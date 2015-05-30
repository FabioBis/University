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
    EV << "Add:: cell size before: "
            <<cells_[avatar->GetX()][avatar->GetY()].size() <<endl; // DBG.
    if(cells_[x][y].insert(std::pair<int, VirtualAvatar*>(avatarID, avatar)).second == false)
    {
        EV <<"Insertion failed. Key was present" <<endl; // DBG.
    }
    else
    {
        EV <<"Insertion of Avatar " <<avatarID <<" completed." <<endl; // DBG.
    }
    EV << "Add:: cell size after: "
            <<cells_[avatar->GetX()][avatar->GetY()].size() <<endl; // DBG.
}

void
VirtualEnvironment::remove(VirtualAvatar* avatar)
{
    EV << "Removing Avatar " <<avatar->GetID() <<"." <<endl; // DBG
    EV << "Erase:: cell size before: "
            <<cells_[avatar->GetX()][avatar->GetY()].size() <<endl; // DBG.
    cells_[avatar->GetX()][avatar->GetY()].erase(avatar->GetID());
    EV << "Erase:: cell size after: "
            <<cells_[avatar->GetX()][avatar->GetY()].size() <<endl; // DBG.
}

void
VirtualEnvironment::move(VirtualAvatar *avatar, int x, int y)
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
VirtualEnvironment::GetAvatarAndSizeAt(int x, int y, int *avatars[], unsigned int& size)
{
    unsigned int aoiSize = cells_[x][y].size();
    *avatars = new int[aoiSize];
    std::map<int, VirtualAvatar*>::iterator it;
    unsigned int i = 0;
    for (it = cells_[x][y].begin(); it != cells_[x][y].end(); it++)
    {
        (*avatars)[i] = it->first;
        i++;
    }
    size = aoiSize;
}

unsigned int
VirtualEnvironment::GetSizeAt(int x, int y) {
    return cells_[x][y].size();
}
