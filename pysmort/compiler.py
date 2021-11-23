import re

class ProgramLine:
    def __init__(self, nr: str, code: str) -> None:
        self.nr = nr
        self.code = code

program: list[ProgramLine] = []

prgString = '''

goal = 20
player = 5
progress = 0

if player < goal then
    player += 1
    progress += 1
end

'''

ln_number = 10
for line in prgString.strip().split('\n'):
    program.append(ProgramLine(ln_number, line))
    ln_number += 10;

bytecode: list[str] = []

scope_depth = 0

for line in program:
    bytecode.append('line ' + str(line.nr))

    # variable = int
    # a = 5
    # \w+ = \d+
    if re.search('^\s*\w+\s*\=\s*\d+\s*$', line.code):
        match = re.match('^\s*(\w+)\s*\=\s*(\d+)\s*$', line.code)
        var_name = match.group(1)
        var_value = match.group(2)
        bytecode.append('declare_int ' + str(var_name))
        bytecode.append('assign_int_val ' + str(var_name) + ' ' + str(var_value))
    
    # variable = float
    # b = 3.14
    # \w+ = \d+.\d+
    if re.search('^\s*\w+\s*\=\s*\d+\.\d+\s*$', line.code):
        match = re.match('^\s*(\w+)\s*\=\s*(\d+\.\d+)\s*$', line.code)
        var_name = match.group(1)
        var_value = match.group(2)
        bytecode.append('declare_float ' + str(var_name))
        bytecode.append('assign_float_val ' + str(var_name) + ' ' + str(var_value))

    # end
    if re.search('^\s*end\s*$', line.code):
        scope_depth -= 1

    # if name comparator name then
    # if a < b then
    # if \w+ [< > =] \w+ then
    if re.search('^\s*if\s*\w+\s*[<=>]\s*\w+\s*then', line.code):
        match = re.match('^\s*if\s*(\w+)\s*([<=>])\s*(\w+)\s*then', line.code)
        scope_depth += 1
        var_left = match.group(1)
        comparator = match.group(2)
        var_right = match.group(3)
        print('if', var_left, comparator, var_right, 'then')
    
    # while name comparator name do
    # while a < b do
    # while \w+ [< > =] \w+ do
    if re.search('^\s*while\s*\w+\s*[<=>]\s*\w+\s*do', line.code):
        match = re.match('^\s*while\s*(\w+)\s*([<=>])\s*(\w+)\s*do', line.code)
        scope_depth += 1
        var_left = match.group(1)
        comparator = match.group(2)
        var_right = match.group(3)
        print('while', var_left, comparator, var_right, 'do')








for code in bytecode:
    print(code)
