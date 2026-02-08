sum_val = 0
prod_val = 1
max_outer = 1000
max_inner = 1000

for i in range(max_outer):
    for j in range(1, max_inner):
        if (i * j) % 7 == 0 and (i + j) % 3 != 0:
            sum_val += i**2 + j**3
        elif (i - j) % 5 == 0 or (i + j) % 11 == 0:
            prod_val *= (i + 1)
            if prod_val > 1_000_000_000:
                prod_val %= 1_000_000_000
        else:
            sum_val -= j**2

        # Quantum boolean simulation
        qb = "both"
        if qb == "both":
            sum_val += 1
        else:
            sum_val -= 1

print("Sum:", sum_val)
print("Prod:", prod_val)