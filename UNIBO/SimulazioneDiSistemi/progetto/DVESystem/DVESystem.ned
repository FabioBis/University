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

package dvesystem;

import org.omnetpp.queueing.SourceOnce;


network DVESystem
{
    parameters:
        int numOfServer;
        int numOfClient;
    submodules:
        mainServer: MainServer {
            @display("p=240,35");
        }
        server[numOfServer]: DVEServer {
            @display("p=52,44,ri");
        }
        client[numOfClient]: DVEClient {
            @display("p=240,217,x");
        }
        wan: WAN {
            @display("p=240,128");
        }
    connections:
        // Server Connections.
        mainServer.lanOut++ --> server[0].lanIn++;
        //mainServer.wanIO <--> wan.toServer++;
        wan.toMainServer <--> mainServer.wanIO;
        for i=0..sizeof(server) - 2 {
            server[i].lanOut++ --> server[i + 1].lanIn++;
        }
        server[sizeof(server) - 1].lanOut++ --> mainServer.lanIn++;
        for i=0..sizeof(server) - 1 {
            server[i].wanIO <--> wan.toServer++;
        }
        // Client connections.
        for j=0..sizeof(client) - 1 {
            client[j].wanIO <--> wan.toClient++;
        }
}
