#include "../../include/models/Payment.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Constructors
Payment::Payment() : paymentId(""), studentId(""), roomId(""), 
                    roomFee(0), electricFee(0), waterFee(0), internetFee(0),
                    totalAmount(0), dueDate(""), paymentDate(""), 
                    status("unpaid"), month("") {}

Payment::Payment(string paymentId, string studentId, string roomId,
                double roomFee, double electricFee, double waterFee, double internetFee,
                string dueDate, string month) 
    : paymentId(paymentId), studentId(studentId), roomId(roomId),
      roomFee(roomFee), electricFee(electricFee), waterFee(waterFee), 
      internetFee(internetFee), dueDate(dueDate), month(month),
      paymentDate(""), status("unpaid") {
    calculateTotal();
}

// Getters
string Payment::getPaymentId() const { return paymentId; }
string Payment::getStudentId() const { return studentId; }
string Payment::getRoomId() const { return roomId; }
double Payment::getRoomFee() const { return roomFee; }
double Payment::getElectricFee() const { return electricFee; }
double Payment::getWaterFee() const { return waterFee; }
double Payment::getInternetFee() const { return internetFee; }
double Payment::getTotalAmount() const { return totalAmount; }
string Payment::getDueDate() const { return dueDate; }
string Payment::getPaymentDate() const { return paymentDate; }
string Payment::getStatus() const { return status; }
string Payment::getMonth() const { return month; }

// Setters
void Payment::setPaymentId(string id) { paymentId = id; }
void Payment::setStudentId(string id) { studentId = id; }
void Payment::setRoomId(string id) { roomId = id; }
void Payment::setRoomFee(double fee) { roomFee = fee; calculateTotal(); }
void Payment::setElectricFee(double fee) { electricFee = fee; calculateTotal(); }
void Payment::setWaterFee(double fee) { waterFee = fee; calculateTotal(); }
void Payment::setInternetFee(double fee) { internetFee = fee; calculateTotal(); }
void Payment::setDueDate(string date) { dueDate = date; }
void Payment::setPaymentDate(string date) { paymentDate = date; }
void Payment::setStatus(string s) { status = s; }
void Payment::setMonth(string m) { month = m; }

// Methods
void Payment::calculateTotal() {
    totalAmount = roomFee + electricFee + waterFee + internetFee;
}

void Payment::markAsPaid() {
    status = "paid";
    // Set payment date to current date (simplified)
    paymentDate = "20/09/2025"; // In real app, use actual current date
}

bool Payment::isOverdue() const {
    // Simplified overdue check - in real app, compare with current date
    return status == "overdue";
}

void Payment::displayInvoice() const {
    cout << "\n========== HOA DON ==========\n";
    cout << "Ma hoa don: " << paymentId << endl;
    cout << "MSSV: " << studentId << endl;
    cout << "Phong: " << roomId << endl;
    cout << "Thang: " << month << endl;
    cout << "----------------------------\n";
    cout << "Tien phong:   " << fixed << setprecision(0) << roomFee << " VND\n";
    cout << "Tien dien:    " << fixed << setprecision(0) << electricFee << " VND\n";
    cout << "Tien nuoc:    " << fixed << setprecision(0) << waterFee << " VND\n";
    cout << "Tien internet:" << fixed << setprecision(0) << internetFee << " VND\n";
    cout << "----------------------------\n";
    cout << "TONG CONG:    " << fixed << setprecision(0) << totalAmount << " VND\n";
    cout << "Han thanh toan: " << dueDate << endl;
    cout << "Trang thai: " << status << endl;
    if (status == "paid" && !paymentDate.empty()) {
        cout << "Ngay thanh toan: " << paymentDate << endl;
    }
    cout << "============================\n";
}

// File I/O
string Payment::toString() const {
    ostringstream oss;
    oss << paymentId << "|" << studentId << "|" << roomId << "|" 
        << roomFee << "|" << electricFee << "|" << waterFee << "|" << internetFee << "|"
        << totalAmount << "|" << dueDate << "|" << paymentDate << "|" 
        << status << "|" << month;
    return oss.str();
}

Payment Payment::fromString(const string& data) {
    Payment p;
    istringstream iss(data);
    string token;
    vector<string> tokens;
    
    while (getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() >= 12) {
        p.paymentId = tokens[0];
        p.studentId = tokens[1];
        p.roomId = tokens[2];
        p.roomFee = stod(tokens[3]);
        p.electricFee = stod(tokens[4]);
        p.waterFee = stod(tokens[5]);
        p.internetFee = stod(tokens[6]);
        p.totalAmount = stod(tokens[7]);
        p.dueDate = tokens[8];
        p.paymentDate = tokens[9];
        p.status = tokens[10];
        p.month = tokens[11];
    }
    
    return p;
}

// Static utilities
vector<Payment> Payment::getPaymentsByStudent(const string& studentId) {
    vector<Payment> payments;
    ifstream file("data/payments.txt");
    string line;
    
    while (getline(file, line)) {
        if (!line.empty()) {
            Payment p = fromString(line);
            if (p.getStudentId() == studentId) {
                payments.push_back(p);
            }
        }
    }
    file.close();
    return payments;
}

vector<Payment> Payment::getUnpaidPaymentsByStudent(const string& studentId) {
    vector<Payment> unpaidPayments;
    vector<Payment> allPayments = getPaymentsByStudent(studentId);
    
    for (const auto& payment : allPayments) {
        if (payment.getStatus() == "unpaid" || payment.getStatus() == "overdue") {
            unpaidPayments.push_back(payment);
        }
    }
    
    return unpaidPayments;
}

bool Payment::savePaymentToFile(const Payment& payment) {
    ofstream file("data/payments.txt", ios::app);
    if (file.is_open()) {
        file << payment.toString() << endl;
        file.close();
        return true;
    }
    return false;
}

bool Payment::updatePaymentInFile(const Payment& updatedPayment) {
    vector<Payment> allPayments;
    ifstream inFile("data/payments.txt");
    string line;
    
    // Read all payments
    while (getline(inFile, line)) {
        if (!line.empty()) {
            Payment p = fromString(line);
            if (p.getPaymentId() == updatedPayment.getPaymentId()) {
                allPayments.push_back(updatedPayment); // Replace with updated
            } else {
                allPayments.push_back(p);
            }
        }
    }
    inFile.close();
    
    // Write all payments back
    ofstream outFile("data/payments.txt");
    if (outFile.is_open()) {
        for (const auto& payment : allPayments) {
            outFile << payment.toString() << endl;
        }
        outFile.close();
        return true;
    }
    return false;
}