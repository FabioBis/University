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

message MoveMsg
{
    // The source of the movement (index inside server connections).
	int client;
	// The destination server that handle the client messages.
	int server;
	// Destination clients. It refers to an int pointer with an array size
	// aoi_arraysize with getter/setter methods: getAoiArraySize()...
	int aoi[];    
}
