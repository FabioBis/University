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

network DVESystem
{
    parameters:
        int numOfServer;
        int numOfClient;
    submodules:
        mainServer: MainServer {
            @display("p=65,45");
        }
        server[numOfServer]: DVEServer;
        client[numOfClient]: DVEClient {
            @display("p=,,x");
        }
    connections:
        // Server Connections.
        mainServer.out++ --> server[0].in++;
        for i=0..sizeof(server) - 2 {
            server[i].out++ --> server[i + 1].in++;
        }
        server[sizeof(server) - 1].out++ --> mainServer.in++;
        // Client Connections.
        for i=0..sizeof(client) - 1 {
            client[i].main <--> mainServer.wan++;
        }
        // TODO: servers/clients connections.
        // TODO: channels Wan and Lan.
}
