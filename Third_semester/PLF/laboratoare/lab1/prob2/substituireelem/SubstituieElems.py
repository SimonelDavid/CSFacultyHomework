class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None

class Lista:
    def __init__(self):
        self.prim = None


'''
crearea unei liste din valori citite pana la 0
'''
def creareLista():
    lista = Lista()
    lista.prim = creareLista_rec()
    return lista

def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareLista_rec()
        return nod

'''
inlocuirea primei liste cu a doua
'''

def inlocuire(lista1, lista2):
    x = lista2.prim
    lista1.prim = inloc_rec()
    return lista1

def inloc_rec():
    

'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tipar_rec(lista.prim)

def tipar_rec(nod):
    if nod != None:
        print (nod.e)
        tipar_rec(nod.urm)


'''
program pentru test
'''

def main():
    list_1 = creareLista()
    print("Ai citit lista 1!")
    list_2 = creareLista()
    print("Ai citit lista 2!")
    tipar(list)

main()

'''

'''