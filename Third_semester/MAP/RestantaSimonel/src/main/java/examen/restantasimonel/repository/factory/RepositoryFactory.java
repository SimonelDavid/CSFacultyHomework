package examen.restantasimonel.repository.factory;

import examen.restantasimonel.domain.Intrebare;
import examen.restantasimonel.domain.Testul;
import examen.restantasimonel.repository.Repository;
import examen.restantasimonel.repository.database.IntrebareDBRepository;
import examen.restantasimonel.repository.database.TestDBRepository;

public class RepositoryFactory {
    private static RepositoryFactory instance = new RepositoryFactory();

    private static Repository<Integer, Intrebare> createLocalitateRepository() {
        return new IntrebareDBRepository("jdbc:postgresql://localhost:5432/restanta",
                "postgres", "postgres");
    }

    private static Repository<Integer, Testul> createRauRepository() {
        return new TestDBRepository("jdbc:postgresql://localhost:5432/restanta",
                "postgres", "postgres");
    }


    public Repository createRepository(RepositoryEntity repositoryEntity) {
        return switch (repositoryEntity) {
            case INTREBARE -> createLocalitateRepository();
            default -> createRauRepository();
        };
    }

    /**
     * Method that retuns the instance of the repository factory
     * @return the repository factory
     */
    public static RepositoryFactory getInstance() {
        return instance;
    }
}
