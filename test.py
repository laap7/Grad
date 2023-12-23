pip install sympy
from sympy import *

x = Symbol('x')
func = x**2
func_der = lambdiff(x, func)
tmp1 = func(4)
tmp2 = func_der(4)

print(str(tmp1) + '    ' + str(tmp2))