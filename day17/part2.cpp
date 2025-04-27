#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <set>
#include <string>
#include <vector>

std::vector<int64_t> getNumbersFromString(const std::string& input) {
    std::vector<int64_t> numbers;
    static const std::regex pattern(R"(\d+)");
    auto begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto end   = std::sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        numbers.push_back(std::stoll(it->str()));
    }
    return numbers;
}

int64_t first_output(int64_t A0, const std::vector<int>& prog) {
    int64_t A = A0, B = 0, C = 0;
    size_t ip = 0;
    while (ip + 1 < prog.size()) {
        int opcode  = prog[ip];
        int operand = prog[ip + 1];
        int64_t val;
        if (opcode==0||opcode==2||opcode==5||opcode==6||opcode==7) {
            switch (operand) {
                case 0: case 1: case 2: case 3:
                    val = operand; break;
                case 4: val = A; break;
                case 5: val = B; break;
                case 6: val = C; break;
                default: val = 0; break;
            }
        } else {
            val = operand;
        }
        switch (opcode) {
            case 0: // adv
                A >>= val;
                ip += 2;
                break;
            case 1: // bxl
                B ^= operand;
                ip += 2;
                break;
            case 2: // bst
                B = val % 8;
                ip += 2;
                break;
            case 3: // jnz
                if (A != 0) ip = operand;
                else         ip += 2;
                break;
            case 4: // bxc
                B ^= C;
                ip += 2;
                break;
            case 5: // out → **return** on first output
                return val % 8;
            case 6: // bdv
                B = A >> val;
                ip += 2;
                break;
            case 7: // cdv
                C = A >> val;
                ip += 2;
                break;
            default:
                ip += 2;
                break;
        }
    }
    return -1;
}

int main(){
    std::ifstream in("puzzle_input.txt");
    if(!in){
        std::cerr<<"Could not open puzzle_input.txt\n";
        return 1;
    }
    std::string contents((std::istreambuf_iterator<char>(in)),
                          std::istreambuf_iterator<char>());
    auto nums = getNumbersFromString(contents);

    std::vector<int> program;
    for(size_t i = 3; i < nums.size(); ++i){
        program.push_back(static_cast<int>(nums[i]));
    }

    std::set<int64_t> candidates = { 0 };  // start with suffix = empty
    for(auto it = program.rbegin(); it != program.rend(); ++it){
        int want = *it;
        std::set<int64_t> nextC;
        for(auto c : candidates){
            int64_t base = c << 3;
            for(int d = 0; d < 8; ++d){
                int64_t attempt = base + d;
                if(first_output(attempt, program) == want){
                    nextC.insert(attempt);
                }
            }
        }
        candidates.swap(nextC);
    }

    auto it = std::find_if(candidates.begin(), candidates.end(),
                           [](int64_t x){ return x > 0; });
    if(it != candidates.end()){
        std::cout << *it << "\n";
    } else {
        std::cerr<<"No positive solution found.\n";
        return 2;
    }

    return 0;
}

