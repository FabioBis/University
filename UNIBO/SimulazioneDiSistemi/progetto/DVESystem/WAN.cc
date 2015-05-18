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
    ACKMsg* ack_msg = dynamic_cast<ACKMsg*>(msg);
    if (ack_msg != 0)
    {
        bubble("ACK!");
        handleACKMessage(msg);
        return;
    }
    delete msg;
}

void
WAN::handleLoginMessage(cMessage *msg)
{
    LoginMsg* l_msg = check_and_cast<LoginMsg*>(msg);
    cGate* gate = msg->getArrivalGate();
    if (gate != NULL)
    {
        const char* gateName = gate->getName();
        if (strcmp(gateName, "toClient$i") == 0)
        {
            sendDelayed(l_msg, exponential(0.10), "toMainServer$o");
        }
        else if (strcmp(gateName,"toMainServer$i") == 0)
        {
            sendDelayed(l_msg, exponential(0.10), "toClient$o", l_msg->getID());
        }
        else {
            // DBG
            bubble(gateName);
            EV << "Gate name error.";
        }
    }
    else {
        // DBG
        EV << "Null Gate " <<gate->getName() <<endl;
    }
}

void
WAN::handleUpdateMessage(cMessage * msg)
{
    cGate* gate = msg->getArrivalGate();
    if (gate != NULL)
    {
        // Update message from a client: forward to servers.
        ServerUpdateMsg* su_msg = check_and_cast<ServerUpdateMsg*>(msg);
        const char* gateName = gate->getName();
        if (strcmp(gateName, "toClient$i") == 0)
        {
            sendDelayed(msg, exponential(0.10), "toServer$o", su_msg->getServerID());
        }
        else if (strcmp(gateName,"toServer$i") == 0)
        {
            EV <<"server side" <<endl;
            // ACK message from a server: notify the client.
            sendDelayed(su_msg, exponential(0.10), "toClient$o", su_msg->getClientDest());
        }
        else
        {
            // DBG
            EV << "Client " << su_msg->getClientDest() <<"\t";
            EV << "WAN: Name Gate Error! " <<gate->getName() <<endl;
        }
    }
    else
    {
        // DBG
        EV << "WAN: Arrival Gate Error! "  <<gate->getName() <<endl;
    }
}

void
WAN::handleMoveMessage(cMessage *msg)
{
    cGate* gate = msg->getArrivalGate();
    if (gate != NULL)
    {
        MoveMsg* m_msg = check_and_cast<MoveMsg*>(msg);
        const char* gateName = gate->getName();
        if (strcmp(gateName, "toClient$i") == 0)
        {
            // Move message from a client: forward to servers.
            sendDelayed(m_msg, exponential(0.10), "toServer$o", m_msg->getServerID());
        }
        else if (strcmp(gateName,"toServer$i") == 0)
        {
//            // Move message from a server: notify all client within AoI.
//            unsigned int size = m_msg->getAoiArraySize();
//            for (unsigned int i = 0; i < size; i++)
//            {
//                MoveMsg* notify = new MoveMsg();
//                notify->setClientID(m_msg->getClientID());
//                sendDelayed(notify, par("delay"), "toClient$o", m_msg->getAoi(i));
//            }
            MoveMsg* notify = new MoveMsg();
            notify->setClientID(m_msg->getClientID());
            sendDelayed(notify, exponential(0.10), "toClient$o", m_msg->getClientDest());
            delete msg;
        }
        else
        {
            // DBG
            bubble(gateName);
            EV << "WAN: Name Gate Error!";
            delete msg;
        }
    }
    else
    {
        // DBG
        bubble("Arrival Gate Error!");
        EV << "WAN: Arrival Gate Error!";
        delete msg;
    }
}

void
WAN::handleUpdateAoIMessage(cMessage *msg)
{
    cGate* gate = msg->getArrivalGate();
    if (gate != NULL)
    {
        // ACK message from a client: forward to servers.
        UpdateAoIMsg* aoi_msg = check_and_cast<UpdateAoIMsg*>(msg);
        const char* gateName = gate->getName();
        if (strcmp(gateName, "toClient$i") == 0)
        {
            sendDelayed(aoi_msg, exponential(0.10), "toServer$o", aoi_msg->getServerID());
        }
        else if (strcmp(gateName,"toServer$i") == 0)
        {
            // ACK message from a server: notify the client.
            sendDelayed(aoi_msg, exponential(0.10), "toClient$o", aoi_msg->getClientDest());
        }
        else
        {
            // DBG
            bubble(gateName);
            EV << "WAN: Name Gate Error!";
            delete msg;
        }
    }
    else
    {
        // DBG
        bubble("Arrival Gate Error!");
        EV << "WAN: Arrival Gate Error!";
        delete msg;
    }
}

void
WAN::handleACKMessage(cMessage *msg)
{
    cGate* gate = msg->getArrivalGate();
    if (gate != NULL)
    {
        // ACK message from a client: forward to servers.
        ACKMsg* ack_msg = check_and_cast<ACKMsg*>(msg);
        const char* gateName = gate->getName();
        if (strcmp(gateName, "toClient$i") == 0)
        {
            sendDelayed(ack_msg, exponential(0.10), "toServer$o", ack_msg->getServerID());
        }
        else if (strcmp(gateName,"toServer$i") == 0)
        {
            // ACK message from a server: notify the client.
            sendDelayed(ack_msg, exponential(0.10), "toClient$o", ack_msg->getMovedID());
        }
        else
        {
            // DBG
            bubble(gateName);
            EV << "WAN: Name Gate Error!";
            delete msg;
        }
    }
    else
    {
        // DBG
        bubble("Arrival Gate Error!");
        EV << "WAN: Arrival Gate Error!";
        delete msg;
    }
}
