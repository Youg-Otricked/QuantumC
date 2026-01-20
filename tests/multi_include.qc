namespace Exported {
    #include <Utils, utils.qc>
    #include <UtilsExtra, utils.qc>  // Same file, different namespace!
}

namespace MultiUse {
    int use_both() {
        return Utils::double_value() + UtilsExtra::triple_value();
    }
}