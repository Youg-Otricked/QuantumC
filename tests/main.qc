namespace Exported {
    #include <Advanced, advanced.qc>
    #include <MultiUse, multi_include.qc>
}

int main() {
    std::qout << "Base value: " << Base::getValue() << "\n";
    std::qout << "Utils double: " << Utils::double_value() << "\n";
    std::qout << "UtilsExtra triple: " << UtilsExtra::triple_value() << "\n";
    std::qout << "Math calc: " << Math::calculate() << "\n";
    std::qout << "Advanced: " << Advanced::complex_calc() << "\n";
    std::qout << "MultiUse: " << MultiUse::use_both() << "\n";
    
    return 0;
}