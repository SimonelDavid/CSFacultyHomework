def consistent(l):
    """
        Functia consistent(l) are rolul de a verifica daca lista l este una consistenta.
    :param l:
    :return:
    """
    for i in range(len(l)):
        for i1 in range(len(l)):
            if i != i1:
                if l[i] == l[i1]:
                    return False
    return True


def solution(l):
    """
        Functia solution(l) are rolul de a verifica daca lista l este una de tip munte.
    :param l:
    :return:
    """
    climb = 0
    n = len(l)

    while climb < n-1 and l[climb] < l[climb+1]:
        climb = climb + 1

    if climb == 0 or climb == n-1:
        return 0

    while climb < n-1 and l[climb] > l[climb+1]:
        climb = climb+1
    if climb == n-1:
        return 1

def back_mountain_rec(new_list, list):
    """
        Functia bac_mountain_rec(new_list, list) este varinata recursiva a algoritmului de backtracking destintat rezolvarii problemei muntelui unui sir.
    :param new_list:
    :param list:
    :return:
    """
    if len(new_list) == len(list):
        if consistent(new_list):
            if solution(new_list):
                print(new_list)
        return
    new_list.append(0)
    for i in range(len(list)):
        new_list[-1] = list[i]
        back_mountain_rec(new_list, list)
    new_list.pop()

def back_iter_mountain(list):
    """
        Functia bac_iter_mountain(list) este varinata iterativa a algoritmului de backtracking destintat rezolvarii problemei muntelui unui sir.
    :param list:
    :return:
    """
    perm = [-1]
    while len(perm) > 0:
        tried = False
        while not tried and perm[-1] < len(list)-1:
            perm[-1] = perm[-1] + 1
            tried = consistent(perm)
        if tried:
            if len(list) == len(perm):
                sol = []
                for i in perm:
                    sol.append(list[i])
                if solution(sol):
                    print(sol)
            perm.append(-1)
        else:
            perm = perm[:-1]

def main():
    """
        Functia main() are rolul de a citi o lista si de apela functia de backtracking pentru a afla toate posibilitatile listei de a fi munte.
    :return:
    """
    l = []
    try:
        n = int(input("Dati dimensiunea listei: "))
        print("Introduceti elementele din lista: \n")
        for i in range(n):
            x = int(input())
            l.append(x)
        l1 = []
        #back_mountain_rec(l1, l)
        back_iter_mountain(l)
    except ValueError:
        print("introduceti un numar!")


main()
