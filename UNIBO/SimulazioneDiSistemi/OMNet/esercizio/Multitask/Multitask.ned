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

package multitask;

import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.PassiveQueue;
import org.omnetpp.queueing.Delay;
import org.omnetpp.queueing.Queue;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.Sink;
import org.omnetpp.queueing.Source;
import org.omnetpp.queueing.Router;


network Multitask
{
    parameters:
        @display("i=block/network;bgb=465,364");
    submodules:
        // Terminal Subsystem.
        user: Source {
            @display("p=33,28;i=block/user");
        }
        terminal: Terminal {
            @display("p=164,28;i=device/terminal");
        }
        // Queue2.
        sink: Sink {
            @display("p=353,28");
        }
        // Processor Subsystem.
        allocateQ2: Allocate {
            @display("p=81,220");
        }
        queue3: Queue {
            @display("p=177,313");
        }
        routerCPU: CPURouter {
            @display("p=177,181");
        }
        queue4: Queue {
            @display("p=420,107");
        }
        queue5: Queue {
            @display("p=420,181");
        }
        queue6: Queue {
            @display("p=420,249");
        }
        queue7: Queue {
            @display("p=420,313");
        }
        resourceCPU: ResourcePool {
            @display("p=49,313");
        }
        deallocateQ2: Deallocate {
            @display("p=270,100");
        }
        q2Router: Q2Router {
            @display("p=81,117");
        }
    connections:
        user.out --> terminal.in++;
        queue3.out --> routerCPU.in++;
        routerCPU.out_p4 --> queue4.in++;
        routerCPU.out_p5 --> queue5.in++;
        routerCPU.out_p6 --> queue6.in++;
        routerCPU.out_p7 --> queue7.in++;
        routerCPU.out_t --> deallocateQ2.in++;
        queue4.out --> queue3.in++;
        queue5.out --> queue3.in++;
        queue6.out --> queue3.in++;
        queue7.out --> queue3.in++;
        deallocateQ2.out --> terminal.in++; //dispatcher.in++;
        allocateQ2.out --> queue3.in++;
        terminal.sink --> sink.in++;
        terminal.out --> q2Router.in++;
        q2Router.out --> allocateQ2.in++;
}
