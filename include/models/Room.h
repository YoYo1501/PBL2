#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

class Room {
private:
    std::string roomId;
    std::string building;
    int floor;
    int capacity;           // Số người tối đa
    int currentOccupants;   // Số người hiện tại
    std::string status;     // "available", "full", "maintenance"
    double monthlyRent;     // Giá thuê hàng tháng
    std::string roomType;   // "single", "double", "quad"

public:
    // Constructors
    Room();
    Room(std::string roomId, std::string building, int floor, 
         int capacity, std::string roomType, double monthlyRent);

    // Getters
    std::string getRoomId() const;
    std::string getBuilding() const;
    int getFloor() const;
    int getCapacity() const;
    int getCurrentOccupants() const;
    std::string getStatus() const;
    double getMonthlyRent() const;
    std::string getRoomType() const;

    // Setters
    void setRoomId(std::string id);
    void setBuilding(std::string building);
    void setFloor(int floor);
    void setCapacity(int capacity);
    void setCurrentOccupants(int occupants);
    void setStatus(std::string status);
    void setMonthlyRent(double rent);
    void setRoomType(std::string type);

    // Methods
    bool isAvailable() const;
    bool canAccommodate(int additionalPeople = 1) const;
    void addOccupant();
    void removeOccupant();
    void updateStatus();
    void displayRoomInfo() const;

    // File I/O
    std::string toString() const;
    static Room fromString(const std::string& data);

    // Static utilities
    static std::vector<Room> getAllRooms();
    static std::vector<Room> getAvailableRooms();
    static std::vector<Room> getRoomsByBuilding(const std::string& building);
    static Room getRoomById(const std::string& roomId);
    static bool saveRoomToFile(const Room& room);
    static bool updateRoomInFile(const Room& room);
};

#endif