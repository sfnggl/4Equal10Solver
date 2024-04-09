import math,ast,sys,os
import operator as op
import numpy as np
from itertools import permutations, product
from termcolor import colored

# credit: https://stackoverflow.com/a/9558001

operators_str : str = '+-*/'

operators = {
    ast.Add: op.add,
    ast.Sub: op.sub,
    ast.Mult: op.mul,
    ast.Div: op.truediv,
}

def eval_expr(expr : str):
    try:
        tokenized : ast.Module = ast.parse(expr, mode='eval')
    except SyntaxError as syntax:
        raise syntax 
    return eval_(tokenized.body)

def eval_(node : ast.expr):
    match node:
        case ast.Constant(value) if isinstance(value, int):
            return value
        case ast.BinOp(left, op, right):
            try:
                return operators[type(op)](eval_(left), eval_(right))
            except ZeroDivisionError as _:
                return -np.inf
        case ast.UnaryOp(op, operand):
            return operators[type(op)](eval_(operand))
        case _:
            raise TypeError(node)

def plug_parentesis(U : list) -> list:
    full_space : list = []
    for eq in U:
        # may be individually enumerated
        # (A) = A
        full_space.append('(' + eq[:3] + ')' + eq[3:])
        full_space.append('(' + eq[:5] + ')' + eq[5:])
        # full_space.append("(" + eq[:7] + ")" + eq[7:]) # (...) = ...
        full_space.append(eq[:2] + '(' + eq[2:5] + ')' + eq[5:])
        full_space.append(eq[:2] + '(' + eq[2:7] + ')' + eq[7:])
        full_space.append(eq[:4] + '(' + eq[4:7] + ')' + eq[7:])
    return full_space

def concatenate_expr(vals : tuple[str], ops : tuple[str]) -> str:
    res : str = ""
    i : int = 0
    while i < len(vals):
        res += vals[i]
        if i < len(ops) : res += ops[i]
        i += 1
    return res

def solution_space(args_as_string : str) -> list[str] :
    numbers_p : list = list(permutations(args_as_string, len(args_as_string)))
    operators_p : list = list(permutations(operators_str, len(operators_str) - 1))
    equation_space : list = list(product(numbers_p, operators_p))
    for index, eqs in enumerate(equation_space):
        equation_space[index] = concatenate_expr(eqs[0], eqs[1])
    # expand every possible equation with parentesis
    return plug_parentesis(equation_space)

def main():
    # compute search space
    # evaluate each expression
    # returns solution

    input_str : str = sys.argv[1] + sys.argv[2] + sys.argv[3] + sys.argv[4]
    if len(input_str) != 4 : sys.stdout.write("Inconsistent input : {}".format(input_str))
    try:
        for char in input_str:
            int(char)
    except ValueError as e:
        print(f"\n{e}\n")
        sys.exit(0)

    for solution in solution_space(input_str):
        if eval_expr(solution) == 10:
            print(colored("\nFound \t{}\n".format(solution), 'green'))
            sys.exit(1)

    print(colored("\nFound no solution!\n", 'red'))

if __name__ == "__main__":
    main()
