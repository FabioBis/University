//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef VIRTUALENVIRONMENT_H_
#define VIRTUALENVIRONMENT_H_

#include <map>
#include <vector>
#include <VirtualAvatar.h>

class VirtualAvatar;

class VirtualEnvironment {
private:
    // The side size of the grid (square).
    static const int NUM_CELLS = 9;
    // The virtual environment is essentially a grid of virtual avatars.
    std::map<int, VirtualAvatar*> cells_[NUM_CELLS][NUM_CELLS];
public:
    VirtualEnvironment();
    virtual ~VirtualEnvironment();
    int GetIndexMax();
    void add(VirtualAvatar* avatar);
    void remove(VirtualAvatar* avatar);
    void move(VirtualAvatar* avatar, int x, int y);
    void erase(VirtualAvatar* avatar);
    void GetAvatarAndSizeAt(int x, int y, int* avatars[], unsigned int& size);
    unsigned int GetSizeAt(int x, int y);
};

#endif /* VIRTUALENVIRONMENT_H_ */
