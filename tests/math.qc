namespace Exported {
    #include <Base, base.qc>
    #include <Utils, utils.qc>
}

namespace Math {
    int calculate() {
        return Utils::double_value() + Base::getValue();
    }
}