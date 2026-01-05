int main() {
    qbool z = qtrue;
    qbool n = both;
    std::qin >> z;
    std::qin >> n;
    std::qout << z &&& n;
    std::qout << z ||| n;
    std::qout << z ^^ n;
    std::qout << "z" === 1;
    std::qout << "z" !== 1;
    std::qout << n;
    std::qout << !!n;
    std::qout << !n;
    std::qout << z |&| !!n;
    std::qout << z &|& n;
}