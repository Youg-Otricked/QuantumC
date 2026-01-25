namespace Exported {
    #include <Math, std>
}
int use_math() {
    return to_int(Math::max(0, 1));
}
namespace Exported {
    #include <AdvQBool, std>
}
int main() {
    AdvQBool::AQB qb = AdvQBool::AQB(50);
    return 0;
}