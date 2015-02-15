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
    // The message is a Job from Source.
    if(logged)
    {
        // Let's move!
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
        ;
    }
    MoveMsg* move = new MoveMsg();
    move->setX(x);
    move->setY(y);
    move->setClientID(getIndex());
    move->setServerID(serverID);
    send(move, "wanIO");
}
