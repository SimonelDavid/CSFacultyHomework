package examen.examensimon.service;

import examen.examensimon.domain.Intrebare;
import examen.examensimon.domain.Testul;
import examen.examensimon.repository.Repository;
import examen.examensimon.repository.database.IntrebareDBRepository;
import examen.examensimon.repository.database.TestDBRepository;
import examen.examensimon.utils.observer.Observer;
import examen.examensimon.utils.utils.ActualEvent;

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
