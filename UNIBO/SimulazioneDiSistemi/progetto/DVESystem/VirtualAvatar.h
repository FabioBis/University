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

#ifndef VIRTUALAVATAR_H_
#define VIRTUALAVATAR_H_

#include <map>
#include <VirtualEnvironment.h>

class VirtualEnvironment;

class VirtualAvatar {
    friend class VirtualEnvironment;
private:
    int x_, y_, ID_;
    VirtualEnvironment* ve_;
public:
    VirtualAvatar(VirtualEnvironment* ve, int id, int x, int y);
    void move(int x, int y);
    int GetID();
    int GetX();
    int GetY();
    void SetX(int x);
    void SetY(int y);
};

#endif /* VIRTUALAVATAR_H_ */
