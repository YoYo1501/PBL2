#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <vector>

class Payment {
private:
    std::string paymentId;
    std::string studentId;
    std::string roomId;
    double roomFee;         // Tiền phòng
    double electricFee;     // Tiền điện
    double waterFee;        // Tiền nước
    double internetFee;     // Tiền internet
    double totalAmount;     // Tổng tiền
    std::string dueDate;    // Hạn thanh toán (dd/mm/yyyy)
    std::string paymentDate; // Ngày thanh toán thực tế (dd/mm/yyyy)
    std::string status;     // "unpaid", "paid", "overdue"
    std::string month;      // Tháng hóa đơn (mm/yyyy)

public:
    // Constructors
    Payment();
    Payment(std::string paymentId, std::string studentId, std::string roomId,
            double roomFee, double electricFee, double waterFee, double internetFee,
            std::string dueDate, std::string month);

    // Getters
    std::string getPaymentId() const;
    std::string getStudentId() const;
    std::string getRoomId() const;
    double getRoomFee() const;
    double getElectricFee() const;
    double getWaterFee() const;
    double getInternetFee() const;
    double getTotalAmount() const;
    std::string getDueDate() const;
    std::string getPaymentDate() const;
    std::string getStatus() const;
    std::string getMonth() const;

    // Setters
    void setPaymentId(std::string id);
    void setStudentId(std::string id);
    void setRoomId(std::string id);
    void setRoomFee(double fee);
    void setElectricFee(double fee);
    void setWaterFee(double fee);
    void setInternetFee(double fee);
    void setDueDate(std::string date);
    void setPaymentDate(std::string date);
    void setStatus(std::string s);
    void setMonth(std::string m);

    // Methods
    void calculateTotal();  // Tính tổng tiền
    void markAsPaid();      // Đánh dấu đã thanh toán
    bool isOverdue() const; // Kiểm tra quá hạn
    void displayInvoice() const; // Hiển thị hóa đơn
    
    // File I/O
    std::string toString() const;
    static Payment fromString(const std::string& data);
    
    // Static utilities
    static std::vector<Payment> getPaymentsByStudent(const std::string& studentId);
    static std::vector<Payment> getUnpaidPaymentsByStudent(const std::string& studentId);
    static bool savePaymentToFile(const Payment& payment);
    static bool updatePaymentInFile(const Payment& payment);
};

// Invoice là alias cho Payment (cùng một class nhưng khác cách sử dụng)
typedef Payment Invoice;

#endif