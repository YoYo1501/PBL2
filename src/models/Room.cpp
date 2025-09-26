#include "../../include/models/Room.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Constructors
Room::Room() : roomId(""), building(""), floor(0), capacity(0), 
               currentOccupants(0), status("available"), monthlyRent(0), roomType("") {}

Room::Room(string roomId, string building, int floor, 
           int capacity, string roomType, double monthlyRent)
    : roomId(roomId), building(building), floor(floor), capacity(capacity),
      currentOccupants(0), monthlyRent(monthlyRent), roomType(roomType) {
    updateStatus();
}

// Getters
string Room::getRoomId() const { return roomId; }
string Room::getBuilding() const { return building; }
int Room::getFloor() const { return floor; }
int Room::getCapacity() const { return capacity; }
int Room::getCurrentOccupants() const { return currentOccupants; }
string Room::getStatus() const { return status; }
double Room::getMonthlyRent() const { return monthlyRent; }
string Room::getRoomType() const { return roomType; }

// Setters
void Room::setRoomId(string id) { roomId = id; }
void Room::setBuilding(string b) { building = b; }
void Room::setFloor(int f) { floor = f; }
void Room::setCapacity(int c) { capacity = c; updateStatus(); }
void Room::setCurrentOccupants(int o) { currentOccupants = o; updateStatus(); }
void Room::setStatus(string s) { status = s; }
void Room::setMonthlyRent(double r) { monthlyRent = r; }
void Room::setRoomType(string t) { roomType = t; }

// Methods
bool Room::isAvailable() const {
    return status == "available" && currentOccupants < capacity;
}

bool Room::canAccommodate(int additionalPeople) const {
    return (currentOccupants + additionalPeople) <= capacity && status == "available";
}

void Room::addOccupant() {
    if (currentOccupants < capacity) {
        currentOccupants++;
        updateStatus();
    }
}

void Room::removeOccupant() {
    if (currentOccupants > 0) {
        currentOccupants--;
        updateStatus();
    }
}

void Room::updateStatus() {
    if (currentOccupants >= capacity) {
        status = "full";
    } else if (currentOccupants == 0) {
        status = "available";
    } else {
        status = "partially_occupied";
    }
}

void Room::displayRoomInfo() const {
    cout << "\n========== THONG TIN PHONG ==========\n";
    cout << "Ma phong: " << roomId << endl;
    cout << "Toa nha: " << building << endl;
    cout << "Tang: " << floor << endl;
    cout << "Loai phong: " << roomType << endl;
    cout << "Suc chua: " << capacity << " nguoi" << endl;
    cout << "Dang o: " << currentOccupants << " nguoi" << endl;
    cout << "Con trong: " << (capacity - currentOccupants) << " cho" << endl;
    cout << "Trang thai: " << status << endl;
    cout << "Gia thue: " << fixed << setprecision(0) << monthlyRent << " VND/thang" << endl;
    cout << "===================================\n";
}

// File I/O
string Room::toString() const {
    ostringstream oss;
    oss << roomId << "|" << building << "|" << floor << "|" 
        << capacity << "|" << currentOccupants << "|" << status << "|" 
        << monthlyRent << "|" << roomType;
    return oss.str();
}

Room Room::fromString(const string& data) {
    Room r;
    istringstream iss(data);
    string token;
    vector<string> tokens;
    
    while (getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() >= 8) {
        r.roomId = tokens[0];
        r.building = tokens[1];
        r.floor = stoi(tokens[2]);
        r.capacity = stoi(tokens[3]);
        r.currentOccupants = stoi(tokens[4]);
        r.status = tokens[5];
        r.monthlyRent = stod(tokens[6]);
        r.roomType = tokens[7];
    }
    
    return r;
}

// Static utilities
vector<Room> Room::getAllRooms() {
    vector<Room> rooms;
    ifstream file("data/rooms.txt");
    string line;
    
    while (getline(file, line)) {
        if (!line.empty()) {
            rooms.push_back(fromString(line));
        }
    }
    file.close();
    return rooms;
}

vector<Room> Room::getAvailableRooms() {
    vector<Room> availableRooms;
    vector<Room> allRooms = getAllRooms();
    
    for (const auto& room : allRooms) {
        if (room.isAvailable()) {
            availableRooms.push_back(room);
        }
    }
    
    return availableRooms;
}

vector<Room> Room::getRoomsByBuilding(const string& building) {
    vector<Room> buildingRooms;
    vector<Room> allRooms = getAllRooms();
    
    for (const auto& room : allRooms) {
        if (room.getBuilding() == building) {
            buildingRooms.push_back(room);
        }
    }
    
    return buildingRooms;
}

Room Room::getRoomById(const string& roomId) {
    vector<Room> allRooms = getAllRooms();
    
    for (const auto& room : allRooms) {
        if (room.getRoomId() == roomId) {
            return room;
        }
    }
    
    return Room(); // Return empty room if not found
}

bool Room::saveRoomToFile(const Room& room) {
    ofstream file("data/rooms.txt", ios::app);
    if (file.is_open()) {
        file << room.toString() << endl;
        file.close();
        return true;
    }
    return false;
}

bool Room::updateRoomInFile(const Room& updatedRoom) {
    vector<Room> allRooms;
    ifstream inFile("data/rooms.txt");
    string line;
    
    // Read all rooms
    while (getline(inFile, line)) {
        if (!line.empty()) {
            Room r = fromString(line);
            if (r.getRoomId() == updatedRoom.getRoomId()) {
                allRooms.push_back(updatedRoom); // Replace with updated
            } else {
                allRooms.push_back(r);
            }
        }
    }
    inFile.close();
    
    // Write all rooms back
    ofstream outFile("data/rooms.txt");
    if (outFile.is_open()) {
        for (const auto& room : allRooms) {
            outFile << room.toString() << endl;
        }
        outFile.close();
        return true;
    }
    return false;
}