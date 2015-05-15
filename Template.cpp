#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int playerCount; // the amount of players (between 2 to 4 )
    int myId; // my player ID (0 or 1)
    int zoneCount; // the amount of zon	es on the map
    int linkCount; // the amount of links between all zones
    cin >> playerCount >> myId >> zoneCount >> linkCount; cin.ignore();
    for (int i = 0; i < zoneCount; i++) {
        int zoneId; // this zone's ID (between 0 and zoneCount-1)
        int resourceType; // Neutral=0 Rhodium=1 Platinum=2 Gold=3 
        int minePower; // Number of resource zone mine has
        cin >> zoneId >> resourceType >> minePower; cin.ignore();
    }
    for (int i = 0; i < linkCount; i++) {
        int zone1;
        int zone2;
        cin >> zone1 >> zone2; cin.ignore();
    }

    // game loop
    while (1) {
        int myRhodium; // your available Rhodium
        int myPlatinum; // your available Platinum
        int myGold; // your available Gold
        cin >> myRhodium >> myPlatinum >> myGold; cin.ignore();
        for (int i = 0; i < zoneCount; i++) {
            int zId; // this zone's ID
            int ownerId; // the player who owns this zone (-1 otherwise)
            int explorerP0; // player 0's Explorers on this zone
            int ninjaP0; // player 0's Ninjas on this zone
            int terminatorP0; // player 0's Terminators on this zone
            int predatorP0; // player 0's Predators on this zone
            int explorerP1; // player 1's Explorers on this zone
            int ninjaP1; // player 1's Ninjas on this zone
            int terminatorP1; // player 1's Terminators on this zone
            int predatorP1; // player 1's Predators on this zone
            int explorerP2; // player 2's Explorers on this zone
            int ninjaP2; // player 2's Ninjas on this zone
            int terminatorP2; // player 2's Terminators on this zone
            int predatorP2; // player 2's Predators on this zone
            int explorerP3; // player 3's Explorers on this zone
            int ninjaP3; // player 3's Ninjas on this zone
            int terminatorP3; // player 3's Terminators on this zone
            int predatorP3; // player 3's Predators on this zone
            cin >> zId >> ownerId >> explorerP0 >> ninjaP0 >> terminatorP0 >> predatorP0 >> explorerP1 >> ninjaP1 >> terminatorP1 >> predatorP1 >> explorerP2 >> ninjaP2 >> terminatorP3 >> predatorP3 >> explorerP3 >> ninjaP3 >> terminatorP3 >> predatorP3; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
	
	cout << "WAIT" << endl; // First line for movement commands
        cout << "WAIT" << endl; // Second line for purchase commands
    }
} 
