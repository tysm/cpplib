from decimal import *

getcontext().prec = 150  # floating precision.

# .200 PI.
PI = Decimal("3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196")


def cos(x):
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 0, 0, 1, 1, 1, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s

def sec(x):
    return 1/cos(x)

def sin(x):
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 1, 0, x, 1, x, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s

def csc(x):
    return 1/sin(x)
     
def atan(x):
    getcontext().prec += 2
    s, last, numer, i = x, -2, x, 0
    while s != last:
        last = s
        i = i + 1
        numer *= x * x * -1
        s += numer / (2 * i + 1)
    getcontext().prec -= 2
    return +s
