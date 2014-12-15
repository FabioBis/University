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

package tictoc2;


simple Toc8
{
    parameters:
        // Whether the module should send out a message on initialization.
        bool sendMsgOnInit = false;
        // Message limit with default value.
        int limit = default(2);
        // Add a default icon.
        @display("i=block/routing");
        @display("i=,gold");
    gates:
        input in;
        output out;
}

simple Tic8
{
    parameters:
        // Whether the module should send out a message on initialization.
        bool sendMsgOnInit = true;
        // Message limit with default value.
        int limit = default(2);
        // Add a default icon.
        @display("i=block/routing");
        @display("i=,cyan");
    gates:
        input in;
        output out;
}


// The network.
network Tictoc8
{
    submodules:
        tic: Tic8;
        toc: Toc8;
    connections:
        tic.out --> { delay = 100ms; } --> toc.in;
        tic.in <-- { delay = 100ms; } <-- toc.out;
}
