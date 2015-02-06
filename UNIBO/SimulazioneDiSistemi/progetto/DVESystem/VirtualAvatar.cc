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

#include <VirtualAvatar.h>

// VirtualAvatar.

VirtualAvatar::VirtualAvatar(VirtualEnvironment* ve, int id, int x, int y)
{
    this->ve_ = ve;
    this->ID_ = id;
    this->x_ = x;
    this->y_ = y;
}


void
VirtualAvatar::move(int x, int y)
{
    this->ve_->move(this, x, y);
}


int
VirtualAvatar::GetID()
{
    return ID_;
}


int
VirtualAvatar::GetX()
{
    return x_;
}


int
VirtualAvatar::GetY()
{
    return y_;
}


void
VirtualAvatar::SetX(int x)
{
    this->x_ = x;
}


void
VirtualAvatar::SetY(int y)
{
    this->y_ = y;
}



