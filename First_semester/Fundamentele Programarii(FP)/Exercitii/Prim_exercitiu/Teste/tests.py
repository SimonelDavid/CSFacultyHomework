from Domain.Picturi import Picturi
from Repository.repo_picturi import PicturiRepository


class Teste:

    @staticmethod
    def __test_creeare_obiect():
        id_pictura = 1
        nume_pictura = "Constanta memoriei"
        autor = "Salvador Dali"
        an = 1931
        pictura = Picturi(id_pictura, nume_pictura, autor, an)

        assert pictura.get_id_pictura() == id_pictura
        assert pictura.get_nume_pictura() == nume_pictura
        assert pictura.get_autor() == autor
        assert pictura.get_an() == an

    @staticmethod
    def __test_adugare_repository():
        repo_picturi = PicturiRepository("Tests.txt")

        pictura1 = Picturi(1, "Constanta memoriei", "Salvador Dali", 1931)
        pictura2 = Picturi(2, "Tipatul", "Edvard Munch", 1893)
        pictura3 = Picturi(3, "Nasterea lui Venus", "Sandro Botticelli", 1485)
        pictura4 = Picturi(4, "Femeia care plange", "Pablo Picasso", 1937)

        assert repo_picturi.get_pictura(1) == pictura1
        assert repo_picturi.get_pictura(2) == pictura2
        assert repo_picturi.get_pictura(3) == pictura3
        assert repo_picturi.get_pictura(4) == pictura4

    def run_tests(self):
        self.__test_creeare_obiect()
        self.__test_adugare_repository()
