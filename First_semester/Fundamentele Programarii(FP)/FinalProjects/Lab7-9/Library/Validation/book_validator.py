class BookValidator():
    '''
    Clasa BookValidator() verifica corectitudinea datelor introduse pentru o carte
    '''
    def book_data_validator(self, id_carte, titlu, descriere, autor):
        '''
        Functia valideaza daca datele introduse pentrui o carte sunt corecte. id_carte trebuie sa fie numar intreg pozitiv
        titlu trebuie sa fie un string nenul, descriere trebuie sa fie un string nenul. autor trebuie sa contina doar
        litere mici si mari si, eventual, '.'
        :param id_carte: numar intreg > 0
        :param titlu: string, nenul
        :param descriere: string, nenul
        :param autor: string, nenul
        :return:-
        :raise Exception, daca unul sau mai multe din campurile de mai sus sunt invalide
        '''
        errors = ""
        if id_carte <= 0:
            errors += "id carte invalid!\n"
        if len(titlu.strip()) == 0:
            errors += "titlu carte invalid!\n"
        if len(descriere) == 0:
            errors += "descriere carte invalida!\n"
        if len(autor) == 0:
            errors += "nume autor invalid!\n"
        else:
            caractere_valide = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz. "
            caractere_invalide = False
            for ch in autor:
                if ch not in caractere_valide:
                    caractere_invalide = True
            if caractere_invalide: errors += "nume autor invalid!\n"

        if len(errors) != 0:
            raise Exception(errors)

    def validare_unicitate(self, carti_repository, id_carte, titlu, autor):
        '''
        Functia verificam daca combinatia de id_carte este unic sau daca [titlu, autor] nu apare deja in lista
        :param carti_repository: repository-ul cartilor
        :param id_carte: numar natural nenul
        :param titlu: string nevid
        :param autor: string nevid
        :return: -
        :raises Exception: "id deja existent!\n" - daca id-ul introdus apare deja in repository
                           "carte deja existenta!\n" - daca cartea apare deja in repository
        '''
        id_existent = False
        carte_existenta = False
        for carte in carti_repository.get_repository():
            if carte.get_book().get_book_id() == id_carte: id_existent = True
            if carte.get_book().get_titlu() == titlu and carte.get_book().get_autor() == autor: carte_existenta = True

        errors = ""
        if id_existent: errors += "id deja existent!\n"
        if carte_existenta: errors += "carte deja existenta!\n"
        if len(errors) != 0:
            raise Exception(errors)

    def validare_id_carte(self, id_carte):
        '''
        Functia verifica daca numarul id_carte e un id valid
        :param id_carte: numar natural nenul
        :return:
        :raises Exception: "id carte invalid!\n", daca id_carte <= 0
        '''
        if id_carte <= 0:
            raise Exception("id carte invalid!\n")
        
    def book_title_validation(self, title):
        '''
        Functia valideaza titlul title, trebuie sa fie nevid
        :param: nume - string nevid
        :return:
        :raises Exception: "titlu invalid!\n", daca titlu este vid
        '''
        if len(title) == 0: raise Exception("titlu invalid!\n")
    
    def book_author_validation(self, author):
        '''
        Functia valideaza autorul author, trebuie sa fie nevid
        :param: nume - string nevid
        :return:
        :raises Exception: "autor invalid!\n", daca autor este vid
        '''
        if len(author) == 0: raise Exception("autor invalid!\n")

    def book_description_validator(self, description):
        '''
        Functia valideaza descrierea description, trebuie sa fie nevid
        :param: nume - string nevid
        :return:
        :raises Exception: "descriere invalida!\n", daca description este vid
        '''
        if len(description) == 0: raise Exception("descriere invalida!\n")
    
    def book_copies_validation(self, copy):
        '''
        Functia verifica daca numarul de exemplare copy este unul valid
        :param copy: numar natural nenul
        :return:
        :raises Exception: "numar exemplare invalid!\n", daca id_carte <= 0
        '''
        if copy <= 0:
            raise Exception("numar exemplare invalid!\n")