import re

class ProgramLine:
    def __init__(self, nr: str, code: str) -> None:
        self.nr = nr
        self.code = code

program: list[ProgramLine] = []
program.append(ProgramLine(10, 'a = 5'))
program.append(ProgramLine(20, 'b = 2.7'))
program.append(ProgramLine(30, 'a = 63'))
program.append(ProgramLine(40, 'b = 3.141592653589793'))

bytecode: list[str] = []

for line in program:
    bytecode.append('line ' + str(line.nr))

    # variable = int
    if re.search('^\w+\s*\=\s*\d+\s*$', line.code):
        match = re.match('^(\w+)\s*\=\s*(\d+)\s*$', line.code)
        var_name = match.group(1)
        var_value = match.group(2)
        bytecode.append('declare_int ' + str(var_name))
        bytecode.append('assign_int_val ' + str(var_name) + ' ' + str(var_value))
    
    # variable = float
    if re.search('^\w+\s*\=\s*\d+\.\d+\s*$', line.code):
        match = re.match('^(\w+)\s*\=\s*(\d+\.\d+)\s*$', line.code)
        var_name = match.group(1)
        var_value = match.group(2)
        bytecode.append('declare_float ' + str(var_name))
        bytecode.append('assign_float_val ' + str(var_name) + ' ' + str(var_value))








for code in bytecode:
    print(code)
