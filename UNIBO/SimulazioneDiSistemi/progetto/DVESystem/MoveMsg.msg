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
    // The source of the movement (client index).
	int clientID;
	int clientDest;
	// The server ID that handle client's requests.
	int serverID;
	// The new coordinates.
	int x;
	int y;
	// Destination clients. It refers to an int pointer with an array size
	// aoi_arraysize with getter/setter methods: getAoiArraySize()...
	int aoi[];    
}
