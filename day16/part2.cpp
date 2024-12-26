#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <string>
#include <set>

struct State {
    int cost, r, c, dr, dc;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

struct TupleHash {
    template <typename T1, typename T2, typename T3, typename T4>
    std::size_t operator()(const std::tuple<T1, T2, T3, T4>& t) const {
        return std::hash<T1>()(std::get<0>(t)) ^
               (std::hash<T2>()(std::get<1>(t)) << 1) ^
               (std::hash<T3>()(std::get<2>(t)) << 2) ^
               (std::hash<T4>()(std::get<3>(t)) << 3);
    }
};

int main() {
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(std::cin, line)) {
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    int sr = -1, sc = -1;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 'S') {
                sr = r;
                sc = c;
                break;
            }
        }
        if (sr != -1) break;
    }

    using Key = std::tuple<int, int, int, int>;
    using CostMap = std::unordered_map<Key, int, TupleHash>;
    using BacktrackMap = std::unordered_map<Key, std::set<Key, std::less<>>, TupleHash>;

    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    CostMap lowest_cost;
    BacktrackMap backtrack;

    pq.push({0, sr, sc, 0, 1});
    lowest_cost[{sr, sc, 0, 1}] = 0;

    int best_cost = std::numeric_limits<int>::max();
    std::set<Key> end_states;

    while (!pq.empty()) {
        auto [cost, r, c, dr, dc] = pq.top();
        pq.pop();

        if (cost > lowest_cost[{r, c, dr, dc}]) continue;

        if (grid[r][c] == 'E') {
            if (cost > best_cost) break;
            best_cost = cost;
            end_states.insert({r, c, dr, dc});
        }

        std::vector<std::tuple<int, int, int, int, int>> neighbors = {
            {cost + 1, r + dr, c + dc, dr, dc},
            {cost + 1000, r, c, dc, -dr},
            {cost + 1000, r, c, -dc, dr}
        };

        for (auto [new_cost, nr, nc, ndr, ndc] : neighbors) {
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') continue;
            Key new_key = {nr, nc, ndr, ndc};
            int current_lowest = lowest_cost.count(new_key) ? lowest_cost[new_key] : std::numeric_limits<int>::max();

            if (new_cost > current_lowest) continue;
            if (new_cost < current_lowest) {
                backtrack[new_key] = {};
                lowest_cost[new_key] = new_cost;
            }
            backtrack[new_key].insert({r, c, dr, dc});
            pq.push({new_cost, nr, nc, ndr, ndc});
        }
    }

    std::deque<Key> states(end_states.begin(), end_states.end());
    std::unordered_set<Key, TupleHash> seen(end_states.begin(), end_states.end());

    while (!states.empty()) {
        Key key = states.front();
        states.pop_front();

        for (const Key& last : backtrack[key]) {
            if (seen.count(last)) continue;
            seen.insert(last);
            states.push_back(last);
        }
    }

    std::set<std::pair<int, int>> unique_tiles;
    for (const auto& [r, c, dr, dc] : seen) {
        unique_tiles.insert({r, c});
    }

    std::cout << unique_tiles.size() << std::endl;

    return 0;
}

