import string, sys
letters = string.ascii_lowercase
w = sys.stdout.write
x = input("How many letter combos do you want(1-10)The bigger the longer, 5 = ~10 mins, and it grows exponintialy, 6 will take ~260 mins, 7 will take ~ 6760 min, 8 will take around 175760 min, 9 will take around 4569760 mins, and 10 will take around 118813760 mins. ")
if int(x) > 0:
    y = int(x)
    for a in letters:
        w(f":{a}:")
    if y > 1:
        for a in letters:
            for b in letters:
                w(f":{a}{b}:")
        if y > 2:
            for a in letters:
                for b in letters:
                    for c in letters:
                        w(f":{a}{b}{c}:")
            if y > 3:
                for a in letters:
                    for b in letters:
                        for c in letters:
                            for d in letters:
                                w(f":{a}{b}{c}{d}:")
                if y > 4:
                    for a in letters:
                        for b in letters:
                            for c in letters:
                                for d in letters:
                                    for e in letters:
                                        w(f":{a}{b}{c}{d}{e}:")
                    if y > 5:
                        for a in letters:
                            for b in letters:
                                for c in letters:
                                    for d in letters:
                                        for e in letters:
                                            w(f":{a}{b}{c}{d}{e}:")
                        if y > 6:
                            for a in letters:
                                for b in letters:
                                    for c in letters:
                                        for d in letters:
                                            for e in letters:
                                                for f in letters:
                                                    w(f":{a}{b}{c}{d}{e}{f}:")
                            if y > 7:
                                for a in letters:
                                    for b in letters:
                                        for c in letters:
                                            for d in letters:
                                                for e in letters:
                                                    for f in letters:
                                                        for g in letters:
                                                            w(f":{a}{b}{c}{d}{e}{f}{g}:")
                                if y > 8:
                                    for a in letters:
                                        for b in letters:
                                            for c in letters:
                                                for d in letters:
                                                    for e in letters:
                                                        for f in letters:
                                                            for g in letters:
                                                                for h in letters:
                                                                    w(f":{a}{b}{c}{d}{e}{f}{g}{h}:")
                                    if y > 9:
                                        for a in letters:
                                            for b in letters:
                                                for c in letters:
                                                    for d in letters:
                                                        for e in letters:
                                                            for f in letters:
                                                                for g in letters:
                                                                    for h in letters:
                                                                        for i in letters:
                                                                            w(f":{a}{b}{c}{d}{e}{f}{g}{h}{i}:")
                                        if y > 10:
                                            for a in letters:
                                                for b in letters:
                                                    for c in letters:
                                                        for d in letters:
                                                            for e in letters:
                                                                for f in letters:
                                                                    for g in letters:
                                                                        for h in letters:
                                                                            for i in letters:
                                                                                for j in letters:
                                                                                    w(f":{a}{b}{c}{d}{e}{f}{g}{h}{i}{j}:")