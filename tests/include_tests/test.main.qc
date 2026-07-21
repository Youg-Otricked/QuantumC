namespace Exported {
    #include<ImImportant, ImUnimportant::IsImportant, ./test.a.qc>
}
int main() {
    `qout("%i, %i", ImImportant::x, ImImportant::add(123, 321));
    ImImportant::C im_a_thing = ImImportant::C();
    `qout("%i", ImUnimportant::IsImportant::uh);
}
