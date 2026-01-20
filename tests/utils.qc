namespace Exported {
    #include <Base, base.qc>
}

namespace Utils {
    int double_value() {
        return Base::getValue() + Base::getValue();
    }
}

namespace UtilsExtra {
    int triple_value() {
        return Base::getValue() + Base::getValue() + Base::getValue();
    }
}