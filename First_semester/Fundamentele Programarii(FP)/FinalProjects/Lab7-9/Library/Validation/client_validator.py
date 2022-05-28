

class ClientValidator():
    '''

    Clasa de validare a clientilor. Aceasta se ocupa de validarea tuturor atributelor
    care au legatura directa cu clasa Client()

    '''

    def validare_date_client(self, id_client, nume, cnp):

        '''

        Functie de validare a campurilor unui obiect de tip Client().

        :param id_client, numar intreg > 0:
        :param nume, sir de caractere nenul:
        :param cnp, sir de caractere cifre, nenul:
        :return: -, daca toate campurile sunt valide
                :raise Exception, daca unul sau mai multe campuri sunt invalide
        '''

        errors = ""
        if id_client <= 0:
            errors += "id client invalid!\n"

        if len(nume.strip()) == 0:
            errors += "nume invalid!\n"

        if len(cnp.strip()) != 13:
            errors += "cnp invalid!\n"
        else:
            nu_doar_cifre = False
            for ch in cnp:
                if (ch < '0' or ch > '9'): nu_doar_cifre = True
            if nu_doar_cifre: errors += "cnp invalid!\n"

        if len(errors) != 0:
            raise Exception(errors)

    def validare_unicitate(self, client_repository, cnp, id_client):
        '''
                Functia verifica daca cnp si id_client sunt unice, adica nu exista deja in repository asupra
                altui client
                :param client_repository: repository pentru conturile clientilor
                :param cnp: string nevid, contine doar cifre
                :param id_client:  numar intreg pozitiv
                :return: -
                :raises Exception: "cnp-ul exista deja!\n", daca cnp-ul nu e unic
                                   "id-ul exista deja!\n", daca id-ul nu e unic
                '''
        exista_id = False
        exista_cnp = False
        for cont_client in client_repository.get_repository():
            if cont_client.get_client().get_id_client() == id_client: exista_id = True
        for cont_client in client_repository.get_repository():
            if cont_client.get_client().get_cnp() == cnp: exista_cnp = True

        errors = ""
        if exista_id: errors += "id-ul exista deja!\n"
        if exista_cnp: errors += "cnp-ul exista deja!\n"

        if len(errors) != 0:
            raise Exception(errors)

    def validare_id_client(self, id_client):
        '''
        Functia valideaza id_client, numar natural nenul
        :param id_client:
        :return: -
        :raises Exception: "id client invalid!\n", daca id_client <= 0
        '''
        if id_client <= 0:
            raise Exception("id client invalid!\n")

    def validare_nume_client(self, nume):
        '''
        Functia valideaza numele nume, trebuie sa fie nevid
        :param: nume - string nevid
        :return:
        '''
        if len(nume) == 0: raise Exception("nume invalid!\n")

    def validare_cnp_client(self, client_repository, cnp):
        '''
        Functia valideaza string-ul cnp. Trebuie sa fie nevid si sa contina doar cifre, dar si sa fie
        unic
        :param client_repository: repository-ul clientilor
        :param cnp:
        :return:
        '''
        if len(cnp.strip()) != 13:
            raise Exception("cnp invalid!\n")
        else:
            for ch in cnp:
                if (ch < '0' or ch > '9'): raise Exception("cnp invalid!\n")

        for cont_client in client_repository.get_repository():
            if cont_client.get_client().get_cnp() == cnp: raise Exception("cnp-ul exista deja!\n")