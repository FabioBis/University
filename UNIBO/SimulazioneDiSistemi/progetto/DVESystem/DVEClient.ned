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


simple DVEClient
{
    parameters:
        
        @signal[sysResponse](type="simtime_t");
        @statistic[dveResponse](title="DVE response time"; source="sysResponse"; record=vector,stats; interpolationmode=none);
    	
    	@signal[moveLost](type="int");
    	@statistic[clientMovesLost](title="Moves lost"; source="moveLost"; record=vector,stats; interpolationmode=none);
    	
    	@signal[noMove](type="int");
    	@statistic[clientNoMoves](title="No moves"; source="noMove"; record=vector,stats; interpolationmode=none);
    	
    	@signal[move](type="int");
    	@statistic[clientMoves](title="Moves"; source="move"; record=vector,stats; interpolationmode=none);
    	
    	@signal[presenceFactor](type="unsigned int");
    	@statistic[clientPresenceFactor](title="Presence Factor"; source="presenceFactor"; record=vector,stats; interpolationmode=none);
    	
    	@display("i=device/pc");
    gates:
        inout wanIO;
        input fromSource;
}
