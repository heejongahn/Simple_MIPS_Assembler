#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <sstream>

#define MAX_SIZE 10000
#define TEXT_START 0x400000
#define DATA_START 0x10000000

// namespace declare
using namespace std;

// opcode map
unordered_map <string, int> opmap = {{"addu", 0}, {"and", 0}, {"nor", 0}, {"or", 0},
    {"sltu", 0}, {"sll", 0}, {"srl", 0}, {"subu", 0}, {"jr", 0}, {"addiu", 9},
    {"andi", 12}, {"lui", 15}, {"ori", 13}, {"sltiu", 11}, {"beq", 4}, {"bne", 5},
    {"lw", 35}, {"sw", 43}, {"j", 2}, {"jal", 3}, {"la", 99}};

// fn map
unordered_map <string, int> fnmap = {{"addu", 0x21}, {"and", 0x24}, {"nor", 0x27},
    {"or", 0x25}, {"sltu", 0x2b}, {"sll", 0}, {"srl", 2}, {"subu", 0x23},
    {"jr", 8}};

// opcoe -> instruction type (0: Rtype, 1: Itype, 2: Jtype)
unordered_map <int, int> typemap;

// reg no -> value
unordered_map <int, int> regmap;

// instruction/data address -> value
unordered_map <int, Instruction> textmap;
unordered_map <int, int> datamap;

int pc = TEXT_START;

// class definition
class Instruction {
    public:
        virtual void SetInfo() = 0;
        virtual string format() = 0;
};

class Rtype : public Instruction {
    private:
        bitset<6> opcode;
        bitset<5> rs;
        bitset<5> rt;
        bitset<5> rd;
        bitset<5> sft;
        bitset<6> fn;
    public:
        void SetInfo(int _opcode, int _rs, int _rt, int _rd, int _sft, int _fn) {
            opcode = bitset<6>(_opcode);
            rs = bitset<5>(_rs);
            rt = bitset<5>(_rt);
            rd = bitset<5>(_rd);
            sft = bitset<5>(_sft);
            fn = bitset<6>(_fn);
        }

        string format() {
            return opcode.to_string() + rs.to_string() + rt.to_string() + rd.to_string() + sft.to_string() + fn.to_string();
        }
    };

class Itype : public Instruction {
    private:
        bitset<6> opcode;
        bitset<5> rs;
        bitset<5> rt;
        bitset<16> imm;
    public:
        void SetInfo(int _opcode, int _rs, int _rt, int _imm)  {
            opcode = bitset<6>(_opcode);
            rs = bitset<5>(_rs);
            rt = bitset<5>(_rt);
            imm = bitset<16>(_imm);
        }

        string format() {
            return opcode.to_string() + rs.to_string() + rt.to_string() + imm.to_string();
        }
    };

class Jtype : public Instruction {
    private:
        bitset<6> opcode;
        bitset<26> target;
    public:
        void SetInfo(int _opcode, int _target) {
            opcode = bitset<6>(_opcode);
            target = bitset<26>(_target);
        }

        string format() {
            return opcode.to_string() + target.to_string();
        }
    };

Instruction parse_inst(string raw_str) {
    int op = atoi(raw_str.substr(6));
    Instruction inst;

    switch (opcode):
        case Rtype:
            int rs = atoi(raw_str.substr(6, 5));
            int rt = atoi(raw_str.substr(11, 5));
            int rd = atoi(raw_str.substr(16, 5));
            int sft = atoi(raw_str.substr(21, 5));
            int fn = atoi(raw_str.substr(26, 6));

            inst = Rtype(op, rs, rt, rd, sft, fn);

        case Itype:
            int rs = atoi(raw_str.substr(6, 5));
            int rt = atoi(raw_str.substr(11, 5));
            int imm = atoi(raw_str.substr(16, 16));

            inst = Itype(op, rs, rt, imm);

        case Jtype:
            int target = atoi(raw_str.substr(6, 26));

            inst = Jtype(op, target);

    return inst;
}

int main(int argc, char* argv[]) {
    string filename = (string) argv[1];
    char input_string[MAX_SIZE];

    int data_section_size, text_section_size;

    int target_address;
    ifstream inFile(filename);

    // Initialize Register
    for (int i = 0; i < 32 ; i++) {
      regmap[i] = 0;
    }


    // Get each section's size info
    inFile.getline(input_string, MAX_SIZE);
    text_section_size = atoi(input_string);

    inFile.getline(input_string, MAX_SIZE);
    data_section_size = atoi(input_string);

    // text section load
    for (i = 0; i < text_section_size ; i+=4) {

    }

    // data section load
    for (i = 0; i < data_section_size ; i+=4) {

    }

    // ----- *-_-* ----- @_@ ----- ^3^ ----- *_* ----- >3< ----- +_+ ----- //

    // run program

    // ----- *-_-* ----- @_@ ----- ^3^ ----- *_* ----- >3< ----- +_+ ----- //
    // write result to stdout



    return 0;
}
