#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

typedef long long ll;
std::unordered_map<char, std::string> bits = {
    {'0', "0000"},
    {'1', "0001"},
    {'2', "0010"}, 
    {'3', "0011"},
    {'4', "0100"},
    {'5', "0101"},
    {'6', "0110"},
    {'7', "0111"},
    {'8', "1000"},
    {'9', "1001"},
    {'A', "1010"},
    {'B', "1011"},
    {'C', "1100"},
    {'D', "1101"},
    {'E', "1110"},
    {'F', "1111"},
};

enum OP {
    SUM,
    PRODUCT,
    MINIMUM,
    MAXIMUM,
    LITERAL, // 4
    GREATER_THAN,
    LESS_THAN,
    EQUAL_TO,
};
enum PacketType { PACKET_LITERAL, PACKET_OPERATOR };

void print(std::vector<ll> v) {
    for(int i = 0; i < v.size(); i++) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

ll bitToInt(std::string bits) {
    ll bitSize = bits.size();
    ll result = 0;
    for(int i = 0; i < bitSize; i++) {
        result += ((ll)(bits[i] - '0') << (bitSize - i - 1));
    }
    return result;
}

PacketType getPacketType(std::string packet) {
    PacketType packet_type;
    if(bitToInt(packet.substr(3, 3)) == 4) packet_type = PACKET_LITERAL;
    else packet_type = PACKET_OPERATOR;

    return packet_type;
}

// ---------part1---------- //
namespace part1 {
    int verSum;
    void parsePacket(std::string packet);

    void processLiteral(std::string packet) { //return end index
        int ver = bitToInt(packet.substr(0, 3));
        verSum += ver;

        int idx = 6; // 6번째부터 literal값 내용 시작
        char leading0;
        std::string bits;
        while(true) {
            leading0 = packet[idx];
            bits.append(packet.substr(idx + 1, 4));
            idx += 5;

            if(leading0 == '0') break;
        }

        if(idx == packet.size()) return;
        parsePacket(packet.substr(idx));
    }

    void processOperator(std::string packet) {
        int ver = bitToInt(packet.substr(0, 3));
        verSum += ver;
        char ID = packet[6];

        if(ID == '0') { // 다음 15비트가 sub-packet들의 비트 수의 합
            int bitSum = bitToInt(packet.substr(7, 15));
            std::string subpkt = packet.substr(22);
            parsePacket(subpkt);        
        } else { // 다음 11비트가 sub-packet들의 개수
            int pktCnt = bitToInt(packet.substr(7, 11));
            std::string subpkt = packet.substr(18);
            parsePacket(subpkt);
        }
    }

    void parsePacket(std::string packet) { // 전체 패킷(맨뒤 필요없는거 포함)
        // std::cout << packet << '\n';
        if(packet.size() < 11) return; // 마지막 버리는 패킷
        PacketType packet_type = getPacketType(packet);

        if (packet_type == PACKET_LITERAL) processLiteral(packet);
        else processOperator(packet);
    }

    void solve() {
        std::ifstream file("16_input.txt");
        std::string hex;
        std::string packet = "";

        std::getline(file, hex);

        for(int i = 0; i < hex.size(); i++) {
            packet.append(bits[hex[i]]);
        }

        part1::parsePacket(packet);
        std::cout << part1::verSum << '\n';
    }
}

// ---------part2---------- //
namespace part2{
    std::string packet;
    int nowIdx;

    ll calc(std::vector<ll> val, OP op) {
        switch(op) {
            case SUM: {
                ll sum = 0;
                for(int i = 0; i < val.size(); i++) sum += val[i];
                return sum;
            }
            case PRODUCT: {
                ll mul = 1;
                for(int i = 0; i < val.size(); i++) mul *= val[i];
                return mul;
            }
            case MINIMUM: {
                ll min = *std::min_element(val.begin(), val.end());
                return min;
            }
            case MAXIMUM: {
                ll max = *std::max_element(val.begin(), val.end());
                return max;
            }
            case GREATER_THAN: {
                return val[0] > val[1];
            }
            case LESS_THAN: {
                return val[0] < val[1];
            }
            case EQUAL_TO: {
                return val[0] == val[1];
            }
        }
    }

    void processLiteral(std::vector<ll>& literals) {
        nowIdx += 6; // 6번째부터 literal값 내용 시작
        char leading0;
        std::string bits;
        while(true) {
            leading0 = packet[nowIdx];
            bits.append(packet.substr(nowIdx + 1, 4));
            nowIdx += 5;

            if(leading0 == '0') break;
        }

        literals.push_back(bitToInt(bits));
    }

    ll processSubpktByBits(ll bitSize, OP op);
    ll processSubpktByNum(ll packetNum, OP op);

    ll processOperator() {
        char ID = packet[nowIdx + 6];
        OP op = static_cast<OP>(bitToInt(packet.substr(nowIdx + 3, 3)));

        if (ID == '0') {
            ll bitSize = bitToInt(packet.substr(nowIdx + 7, 15));
            nowIdx += 22;
            return processSubpktByBits(bitSize, op);
        } else {
            ll packetNum = bitToInt(packet.substr(nowIdx + 7, 11));
            nowIdx += 18;
            return processSubpktByNum(packetNum, op);
        }
    }

    // subPkt들의 비트 수가 주어졌을 때(Operator)
    ll processSubpktByBits(ll bitSize, OP op) { // packet는 subpkt포함 뒤에 모든 bits 포함
        std::vector<ll> literals;
        ll endPoint = nowIdx + bitSize;

        while(nowIdx < endPoint) {
            
            PacketType packetType = getPacketType(packet.substr(nowIdx));
            
            if(packetType == PACKET_LITERAL) {
                processLiteral(literals);
            } else {
                literals.push_back(processOperator());
            }
        }

        std::cout << "OP: " << op << '\n';
        std::cout << "Literals: ";
        print(literals);
        std::cout << calc(literals, op) << '\n';
        return calc(literals, op);
    }

    // subPkt들의 패킷 수가 주어졌을 때(Operator)
    ll processSubpktByNum(ll packetNum, OP op) {
        std::vector<ll> literals;
        ll pktCnt = 0;

        while(pktCnt < packetNum) {
            PacketType packetType = getPacketType(packet.substr(nowIdx));

            if(packetType == PACKET_LITERAL) {
                processLiteral(literals);
                pktCnt++;
            } else {
                literals.push_back(processOperator());
                pktCnt++;
            }
        }

        std::cout << "OP: " << op << '\n';
        std::cout << "Literals: ";
        print(literals);
        std::cout << calc(literals, op) << '\n';
        return calc(literals, op);
    }

    void solve() {
        std::ifstream file("16_input.txt");
        std::string hex;

        std::getline(file, hex);

        for(int i = 0; i < hex.size(); i++) {
            packet.append(bits[hex[i]]);
        }

        nowIdx = 0;
        std::cout << processOperator() << '\n';

        // part2::parsePacket(packet);
    }
}


int main() {
    //part1::solve();
    part2::solve();
    //std::cout << part2::processSubpktByBits("110100010100101001000100100", 27, OP::SUM);

    return 0;
}