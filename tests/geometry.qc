// Geometry - depends on Math (which depends on Utils)

namespace Exported {
    #include <Math, math.qc>
}

namespace Geometry {
    int area(int side) {
        return Math::square(side);
    }
}