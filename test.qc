void just_print() {
  print("hi");
  return;
}
int main() {
  auto add = fn(int a, int b) -> int { return a + b; };
  println(add(1,2));
  just_print();
  just_print();
  return 0;
}
