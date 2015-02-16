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
        handleLoginMessage(msg);
        return;
    }
    MoveMsg* mvmsg = dynamic_cast<MoveMsg*>(msg);
    if (mvmsg != 0)
    {
        bubble("Move MSG!");
        handleMoveMessage(msg);
        return;
    }
    ServerUpdateMsg* sumsg = dynamic_cast<ServerUpdateMsg*>(msg);
    if (sumsg != 0)
    {
        bubble("Server Update MSG!");
        handleUpdateMessage(msg);
    }
    ServerUpdateMsg* u_msg = dynamic_cast<ServerUpdateMsg*>(msg);
    if (u_msg != 0)
    {
        bubble("Server Update MSG!");
        handleUpdateMessage(msg);
        return;
    }
    UpdateAoIMsg* aoi_msg = dynamic_cast<UpdateAoIMsg*>(msg);
    if (aoi_msg != 0)
    {
        bubble("Update AoI!");
        handleUpdateAoIMessage(msg);
        return;
    }
}


void
WAN::handleLoginMessage(cMessage *msg)
{
    LoginMsg* l_msg = check_and_cast<LoginMsg*>(msg);
    send(l_msg, "toMainServer$o");
}


void
WAN::handleUpdateMessage(cMessage * msg)
{
    ServerUpdateMsg* su_msg = check_and_cast<ServerUpdateMsg*>(msg);
    // TODO
}


void
WAN::handleMoveMessage(cMessage *msg)
{
    cGate* gate = msg->getArrivalGate();
    if (gate != NULL)
    {
        // Move message from a client: forward to servers.
        MoveMsg* m_msg = check_and_cast<MoveMsg*>(msg);
        const char* gateName = gate->getName();
        if (strcmp(gateName, "toClient"))
        {

            send(m_msg, "toServer$o");
        }
        else if (strcmp(gateName,"toServer"))
        {
            // Move message from a server: notify all client within AoI.
            unsigned int size = m_msg->getAoiArraySize();
            for (unsigned int i = 0; i < size; i++)
            {
                MoveMsg* notify = new MoveMsg();
                notify->setClientID(m_msg->getClientID());
                send(notify, "toClient", m_msg->getAoi(i));
            }
        }
        else
        {
            // DBG
            bubble(gateName);
        }
    }
    else
    {
        // DBG
        bubble("ArrivalGate Error!");
    }
}

void
WAN::handleUpdateAoIMessage(cMessage *msg)
{
    UpdateAoIMsg* aoi_msg = check_and_cast<UpdateAoIMsg*>(msg);
    // TODO
}
