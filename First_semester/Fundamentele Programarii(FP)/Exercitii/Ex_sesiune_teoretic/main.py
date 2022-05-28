def f(l):
    if l == None or l == []:
        raise ValueError
    aux = l[0]+1

    for i in l:
        if i-aux >= 0:
            return False
        aux = i
    return True

l = [5,4,3,2,1]
assert f(l) == True

l1 = [5,5,4,3,2,1]
assert f(l1) == False

l2 = []

try:
    f(l2)
    assert False
except Exception as ex:
    assert (ex == ValueError)
