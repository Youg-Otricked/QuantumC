def run_bf(code, input_str):
    cells = [0] * 30000
    point = 0
    inst = 0
    strp = 0
    brk1 = []
    brk2 = []
    output_lst = []
    i = 0
    mapl = {}
    mapr = {}
    ac = ['+', '-', '<', '>', '[', ']', '.', ',']
    while i < len(code):
        if code[i] not in ac:
            raise CharError("You used non + - < > [ ] . , chars")
        if code[i] == "[":
            brk1.append(i)
        if code[i] == "]":
            brk2.append(i)
        i += 1
    while len(brk1) != 0 or len(brk2) != 0:
        l = brk1.pop(0)
        r = brk2.pop()
        mapl[l] = r
        mapr[r] = l
        print(mapl)
        print(mapr)
        
    while inst < len(code):
        cur = code[inst]
        if cur == "+":
            cells[point] = (cells[point] + 1) % 256
        elif cur == "-":
            cells[point] = (cells[point] - 1) % 256
        elif cur == ">" and point < 29999:
            point += 1
        elif cur == "<" and point > 0:
            point -= 1
        elif cur == ".":
            output_lst.append(chr(cells[point]))
        elif cur == ",":
            if strp >= len(input_str):
                cells[point] = 0
            else:
                cells[point] = ord(input_str[strp])
            strp += 1
        elif cur == "[":
            if cells[point] == 0:
                inst = mapl[inst]
        elif cur == "]":
            if cells[point] != 0:
                inst = mapr[inst]
        inst += 1
    return "".join(output_lst)   
# quick_run_tests.py
        
            
        
        
z = input("write your own bf code?(y/n)")
if z.lower() = "y":
    code = input("Write your bf code.(type h for help)")
    if code.lower() = "h":
        print("in bf, you can only use the following charecters and thats it. there is a tape of 30000 cells, and you ad numbers to those to make charecters. what each symbol does: <. moves backwars on the tape unlles you are at zero, then you stay the same. > move forwards on the tape unless you are at 30000. you atart at zero. +. increments the current cell by one. - decrements the current cell by one. both + and - wrap around, so if you + at 255 you go to zero or - at 0 you go to 255. . = adds the current cell as a letter using ascii to the output list. , = adds the current letter in the input list via ascii to a cell then advances to the next charecter on the input list. [. if the current cell is zero, move to the instruciton after teh closing bracket of this bracket. ] if the current cell is not zero, move to hte instruction after the opening bracket of this set.")
        code = input("Write your bf code.")
    string = input("Write the message for your text that is inputed (optional)")
    print("your output is " + run_bf(code, string))
    
    
    
