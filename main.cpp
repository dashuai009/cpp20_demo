import std;

int main() {
    std::vector<int> a{10, 10, 2, 30};
    for (auto i: a) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    return 0;
}