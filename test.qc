struct Thigny {
    int a;
    int b;
  }
Thigny test() {
  return { 123, 123 };
}
int main() {
  
  Thigny thing = {
    0,
    0
  };
  thing = test();
}