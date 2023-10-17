package org.example;

import java.util.function.Predicate;

public class AngajatService {
    private AngajatDBRepository angajatDBRepository;

    public AngajatService(AngajatDBRepository angajatDBRepository) {
        this.angajatDBRepository = angajatDBRepository;
    }

    public Angajat findOneByPredicate(Predicate<Angajat> pred) throws Exception {
        Angajat angajat = angajatDBRepository.findByPredicate(pred);
        if(angajat == null)
            throw new Exception("Angajat inexistent!");
        return angajat;
    }

    public Angajat findOneByNamePassword(String name, String password) throws Exception {
        Angajat angajat = angajatDBRepository.findByNumeParola(name, password);
        if(angajat == null)
            throw new Exception("Angajat inexistent!");
        return angajat;
    }
}
