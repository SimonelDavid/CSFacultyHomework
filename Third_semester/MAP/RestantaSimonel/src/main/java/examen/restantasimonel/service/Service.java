package examen.restantasimonel.service;

import examen.restantasimonel.domain.Intrebare;
import examen.restantasimonel.domain.Testul;
import examen.restantasimonel.repository.Repository;
import examen.restantasimonel.repository.database.IntrebareDBRepository;
import examen.restantasimonel.repository.database.TestDBRepository;
import examen.restantasimonel.utils.observer.Observer;
import examen.restantasimonel.utils.utils.ActualEvent;

public class Service {


    private TestDBRepository testDBRepository;
    private IntrebareDBRepository intrebareDBRepository;

    public Service(Repository<Integer, Testul> testDBRepository, Repository<Integer, Intrebare> intrebareDBRepository) {
        this.testDBRepository = (TestDBRepository) testDBRepository;
        this.intrebareDBRepository = (IntrebareDBRepository) intrebareDBRepository;
    }

    public Iterable<Testul> getAllTest() {
        return testDBRepository.getAll();
    }

    public Iterable<Intrebare> getAllIntrebari() {
        return intrebareDBRepository.getAll();
    }

    public Integer idTestNou(){
        return testDBRepository.idTestNou();
    }

    public void addIntrebareToTest(Integer idIntrebare, Integer idTest){
        testDBRepository.addIntrebareToTest(idIntrebare, idTest);
        intrebareDBRepository.addIntrebareToTest(idIntrebare, idTest);
    }


    public void addObservers(Observer<ActualEvent> observer) {
        testDBRepository.addObserver(observer);
        intrebareDBRepository.addObserver(observer);
    }

}
