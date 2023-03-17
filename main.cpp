import std;

int main() {
    std::vector<char> a{'c', 'p', 'p', '2', '0'};
    for (auto i: a) {
        std::cout << i;
    }
    std::cout << '\n';
    return 0;
}