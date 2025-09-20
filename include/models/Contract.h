#ifndef CONTRACT_H
#define CONTRACT_H
#include <string>

struct Contract {
    std::string contractId;
    std::string studentId;
    std::string roomId;
    std::string startDate;
    std::string endDate;
    std::string status; // còn hiệu lực, đã kết thúc, v.v.

    std::string toString() const {
        return contractId + "|" + studentId + "|" + roomId + "|" + startDate + "|" + endDate + "|" + status;
    }
    static Contract fromString(const std::string& line) {
        Contract c;
        size_t pos = 0, prev = 0, idx = 0;
        std::string fields[6];
        while ((pos = line.find('|', prev)) != std::string::npos && idx < 5) {
            fields[idx++] = line.substr(prev, pos - prev);
            prev = pos + 1;
        }
        fields[idx] = line.substr(prev);
        c.contractId = fields[0];
        c.studentId = fields[1];
        c.roomId = fields[2];
        c.startDate = fields[3];
        c.endDate = fields[4];
        c.status = fields[5];
        return c;
    }
};
#endif
