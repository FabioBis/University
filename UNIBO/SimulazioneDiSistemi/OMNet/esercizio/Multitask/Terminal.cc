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

#include <Terminal.h>

Define_Module(Terminal);

void
Terminal::initialize()
{
    servedJobs = 0;
    WATCH(servedJobs);
}

void
Terminal::handleMessage(cMessage *msg)
{
    if (servedJobs < MAXSERVEDJOBS)
    {
        // The served jobs are less than the maximum, simulation continue.
        simtime_t delay = par("delayTime");
        sendDelayed(msg, delay, "out");
        servedJobs++;
    }
    else
    {
        // Maximum jobs served, simulation ends.
        // The user are dropped, when the last User is sinked simulation stop.
        send(msg, "sink");
    }
}
