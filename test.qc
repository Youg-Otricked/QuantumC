type ApiTier = "Pro" | "Free" | "Basic" | "Enterprise";

int main() {
    ApiTier tier = "Pro";
    std::qout << getRateLimitForTier(tier);
    type Weird = 1 | 2 | "ok" | 'x' | true | qtrue | int;

    Weird a = 1;        // int:1 -> literal match
    Weird b = "ok";     // string:"ok" -> literal match
    Weird c = 'x';      // char:'x' -> literal match
    Weird d = true;     // bool:true -> literal match
    Weird e = qtrue;    // qbool:qtrue -> literal match
    Weird f = 42;       // type union member `int` -> matches actual_type "int"
}

int getRateLimitForTier(ApiTier tier) {
  switch (tier) {
    case "Free":
      return 10;
    case "Basic":
      return 100;
    case "Pro":
      return 1000;
    case "Enterprise":
      return 10000;
  }
}
