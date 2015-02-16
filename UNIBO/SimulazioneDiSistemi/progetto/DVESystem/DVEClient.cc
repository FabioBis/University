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

#include <DVEClient.h>

Define_Module(DVEClient);

DVEClient::DVEClient()
{
    // Set the pointer to NULL, so that the destructor won't crash
    // even if initialize() doesn't get called because of a runtime
    // error or user cancellation during the startup process.
    login = NULL;
}

DVEClient::~DVEClient()
{
    //cancelAndDelete(login);
    //cancelAndDelete(move);
}

void
DVEClient::initialize()
{
    // Assuming the Avatar lives in a 9x9 world, and the staring distribution
    // among world cells is uniform.
    avatar = new Avatar(getIndex(), intuniform(0, 8), intuniform(0, 8));
    logged = false;
}


void
DVEClient::handleMessage(cMessage *msg)
{
    MoveMsg* m_msg = dynamic_cast<MoveMsg*>(msg);
    if (m_msg != 0)
    {
        bubble("Move MSG!");
        handleMoveMessage(msg);
        return;
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
    // The message is a Job from Source.
    if(logged)
    {
        // Let's move!
        bubble("Let's move!");
        makeMove();
    }
    else
    {
        logged = true;
        login = new LoginMsg("login");
        login->setX(avatar->GetX());
        login->setY(avatar->GetY());
        login->setID(avatar->GetID());
        // $o and $i suffix is used to identify the input/output part of a two way gate.
        send(login, "wanIO$o");
    }
}


void
DVEClient::handleMoveMessage(cMessage *msg)
{
    // TODO
}


void
DVEClient::handleUpdateMessage(cMessage * msg)
{
    // TODO
}


void
DVEClient::handleUpdateAoIMessage(cMessage * msg)
{
    // TODO
}


void
DVEClient::makeMove()
{
    int x;
    int y;
    double probability = uniform(0.0, 1.0);
    if (probability > 0.95) // 1.0 - 0.05
    {
        x = intuniform(0, 8);
        y = intuniform(0, 8);
    }
    else
    {
        computeCoordinate(avatar->GetX(), x);
        computeCoordinate(avatar->GetY(), y);
    }
    MoveMsg* move = new MoveMsg();
    move->setX(x);
    move->setY(y);
    move->setClientID(getIndex());
    move->setServerID(serverID);
    if (avatar->GetX() == x && avatar->GetY() == y)
    {
        // No moves.
        return;
    }
    else
    {
        avatar->move(x, y);
        send(move, "wanIO");
    }
}

void
DVEClient::computeCoordinate(int src, int &dest)
{
    switch (src)
    {
    case 0:
        dest = intuniform(0, 1);
        break;
    case 8:
        dest = intuniform(7, 8);
        break;
    default:
        dest = intuniform(src - 1, src + 1);
        break;
    }
}
