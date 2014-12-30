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

#include <CPURouter.h>

Define_Module(CPURouter);

void
CPURouter::initialize()
{
    ; // Nothing to do.
}

void
CPURouter::handleMessage(cMessage *msg)
{
    double probability = uniform(0.0, 1.0);
    if (probability >= 0.76) // 1.0 - 2.4
    {
        // p7 = 24%.
        send(msg, "out_p7");
    }
    else if (probability >= 0.60) // 0.76 - 0.16
    {
        // p6 = 16%.
        send(msg, "out_p6");
    }
    else if (probability >= 0.40) // 0.60 - 0.20
    {
        // p5 = 20%.
        send(msg, "out_p5");
    }
    else if (probability >= 0.20) // 0.40 - 020
    {
        // p4 = 20%.
        send(msg, "out_p4");
    }
    else // < 0.20
    {
        // p3 = 20%.
        send(msg, "out_t");
    }
}
