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

#include <WAN.h>

Define_Module(WAN);

void
WAN::initialize()
{
    ;
}


void
WAN::handleMessage(cMessage *msg)
{
    LoginMsg* l_msg = dynamic_cast<LoginMsg*>(msg);
    if (l_msg != 0)
    {
        bubble("Login MSG!");
        send(l_msg, "toMainServer$o");
    }
    MoveMsg* mvmsg = dynamic_cast<MoveMsg*>(msg);
    if (mvmsg != 0)
    {
        bubble("Move MSG!");
    }
    ServerUpdateMsg* sumsg = dynamic_cast<ServerUpdateMsg*>(msg);
    if (sumsg != 0)
    {
        bubble("Server Update MSG!");

    }
}
