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

#include <MainServer.h>

Define_Module(MainServer);

MainServer::~MainServer()
{
    delete partition_;
}

void
MainServer::initialize()
{
    PARTSERVERS = par("numOfServer");
    partition_ = new part_indexes[PARTSERVERS];
    partitioner();
    WATCH(ve_);
    WATCH(partition_);
}


void
MainServer::handleLoginMessage(LoginMsg *msg)
{
    // Insert Virtual Avatar inside the Virtual Environment.
    VirtualAvatar* va = new VirtualAvatar(
            ve_,
            msg->getID(),
            msg->getX(),
            msg->getY());
    ve_->add(va);
    // Insert Virtual Avatar into the map of connected clients.
    connectedAvatars_.insert(std::pair<int, VirtualAvatar*>(msg->getID(), va));
}


void
MainServer::handleUpdateMessage(ServerUpdateMsg * msg)
{
    // TODO
}


void
MainServer::handleMoveMessage(MoveMsg *msg)
{
    // TODO
}

void
MainServer::handleMessage(cMessage *msg)
{
    LoginMsg* l_msg = dynamic_cast<LoginMsg*>(msg);
    if (l_msg != 0)
    {
        bubble("Login MSG!");
    }
    MoveMsg* m_msg = dynamic_cast<MoveMsg*>(msg);
    if (m_msg != 0)
    {
        bubble("Move MSG!");
    }
    ServerUpdateMsg* u_msg = dynamic_cast<ServerUpdateMsg*>(msg);
    if (u_msg != 0)
    {
        bubble("Server Update MSG!");
    }
}


void
MainServer::partitioner()
{
    switch(PARTSERVERS)
    {
    case 1:
        partition_[0].bl = 0;
        partition_[0].el = 8;
        partition_[0].bc = 0;
        partition_[0].ec = 8;
        break;
    case 2:
        partition_[0].bl = 0;
        partition_[0].el = 5;
        partition_[0].bc = 0;
        partition_[0].ec = 5;

        partition_[1].bl = 6;
        partition_[1].el = 8;
        partition_[1].bc = 6;
        partition_[1].ec = 8;
        break;
    case 3:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 8;

        partition_[1].bl = 3;
        partition_[1].el = 5;
        partition_[1].bc = 0;
        partition_[1].ec = 8;

        partition_[2].bl = 6;
        partition_[2].el = 8;
        partition_[2].bc = 0;
        partition_[2].ec = 8;
        break;
    case 4:
        partition_[0].bl = 0;
        partition_[0].el = 4;
        partition_[0].bc = 0;
        partition_[0].ec = 4;

        partition_[1].bl = 0;
        partition_[1].el = 4;
        partition_[1].bc = 5;
        partition_[1].ec = 8;

        partition_[2].bl = 5;
        partition_[2].el = 8;
        partition_[2].bc = 0;
        partition_[2].ec = 4;

        partition_[3].bl = 5;
        partition_[3].el = 8;
        partition_[3].bc = 5;
        partition_[3].ec = 8;
        break;
    case 5:
        partition_[0].bl = 0;
        partition_[0].el = 4;
        partition_[0].bc = 0;
        partition_[0].ec = 4;

        partition_[1].bl = 5;
        partition_[1].el = 8;
        partition_[1].bc = 0;
        partition_[1].ec = 4;

        partition_[2].bl = 0;
        partition_[2].el = 2;
        partition_[2].bc = 5;
        partition_[2].ec = 8;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 5;
        partition_[3].ec = 8;

        partition_[4].bl = 6;
        partition_[4].el = 8;
        partition_[4].bc = 5;
        partition_[4].ec = 8;
        break;
    case 6:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 4;

        partition_[1].bl = 0;
        partition_[1].el = 2;
        partition_[1].bc = 5;
        partition_[1].ec = 8;

        partition_[2].bl = 3;
        partition_[2].el = 5;
        partition_[2].bc = 0;
        partition_[2].ec = 4;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 5;
        partition_[3].ec = 8;

        partition_[4].bl = 6;
        partition_[4].el = 8;
        partition_[4].bc = 0;
        partition_[4].ec = 4;

        partition_[5].bl = 6;
        partition_[5].el = 8;
        partition_[5].bc = 5;
        partition_[5].ec = 8;
        break;
    case 7:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 5;

        partition_[1].bl = 0;
        partition_[1].el = 2;
        partition_[1].bc = 6;
        partition_[1].ec = 8;

        partition_[2].bl = 3;
        partition_[2].el = 5;
        partition_[2].bc = 0;
        partition_[2].ec = 2;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 3;
        partition_[3].ec = 5;

        partition_[4].bl = 3;
        partition_[4].el = 8;
        partition_[4].bc = 6;
        partition_[4].ec = 8;

        partition_[5].bl = 6;
        partition_[5].el = 8;
        partition_[5].bc = 0;
        partition_[5].ec = 2;

        partition_[6].bl = 6;
        partition_[6].el = 8;
        partition_[6].bc = 3;
        partition_[6].ec = 5;
        break;
    case 8:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 5;

        partition_[1].bl = 0;
        partition_[1].el = 2;
        partition_[1].bc = 6;
        partition_[1].ec = 8;

        partition_[2].bl = 3;
        partition_[2].el = 5;
        partition_[2].bc = 0;
        partition_[2].ec = 2;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 3;
        partition_[3].ec = 5;

        partition_[4].bl = 3;
        partition_[4].el = 5;
        partition_[4].bc = 6;
        partition_[4].ec = 8;

        partition_[5].bl = 6;
        partition_[5].el = 8;
        partition_[5].bc = 0;
        partition_[5].ec = 2;

        partition_[6].bl = 6;
        partition_[6].el = 8;
        partition_[6].bc = 3;
        partition_[6].ec = 5;

        partition_[7].bl = 6;
        partition_[7].el = 8;
        partition_[7].bc = 6;
        partition_[7].ec = 6;
        break;
    case 9:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 2;

        partition_[1].bl = 0;
        partition_[1].el = 2;
        partition_[1].bc = 3;
        partition_[1].ec = 5;

        partition_[2].bl = 0;
        partition_[2].el = 2;
        partition_[2].bc = 6;
        partition_[2].ec = 8;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 0;
        partition_[3].ec = 2;

        partition_[4].bl = 3;
        partition_[4].el = 5;
        partition_[4].bc = 3;
        partition_[4].ec = 5;

        partition_[5].bl = 3;
        partition_[5].el = 5;
        partition_[5].bc = 6;
        partition_[5].ec = 8;

        partition_[6].bl = 6;
        partition_[6].el = 8;
        partition_[6].bc = 0;
        partition_[6].ec = 2;

        partition_[7].bl = 6;
        partition_[7].el = 8;
        partition_[7].bc = 3;
        partition_[7].ec = 5;

        partition_[8].bl = 6;
        partition_[8].el = 8;
        partition_[8].bc = 6;
        partition_[8].ec = 6;
        break;
    default:
        throw 401;
        break;
    }
}
