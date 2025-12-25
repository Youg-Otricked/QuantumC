void just_print() {
  print("hi");
  return;
}
int main() {
  auto add = fn(int a, int b) -> int { return a + b; };
  println(add(1,2));
  just_print();
  just_print();
  string name = "Me";
  int age = 0;
  string msg = f"Hello {name}, you are {age} years old!\n";
  std::qout << '\n' << msg;
  return 0;
}
