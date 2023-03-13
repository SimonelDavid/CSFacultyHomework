package examen.restantasimonel;

import examen.restantasimonel.controller.ProfesorController;
import examen.restantasimonel.controller.StudentController;
import examen.restantasimonel.domain.Intrebare;
import examen.restantasimonel.domain.Testul;
import examen.restantasimonel.repository.Repository;
import examen.restantasimonel.repository.factory.RepositoryFactory;
import examen.restantasimonel.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

import static examen.restantasimonel.repository.factory.RepositoryEntity.*;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {

        final Parameters params = getParameters();
        final List<String> parameters = params.getRaw();
        Repository<Integer, Testul> testRepository = RepositoryFactory.getInstance().createRepository(TEST);
        Repository<Integer, Intrebare> intrebareRepository = RepositoryFactory.getInstance().createRepository(INTREBARE);
        Service service = new Service(testRepository,intrebareRepository);
        Integer idTest = service.idTestNou();

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("profesor.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400);

        ProfesorController profesorController = fxmlLoader.getController();
        profesorController.setTest(idTest);
        profesorController.setService(service);

        stage.setTitle("evaluator");
        stage.setScene(scene);
        stage.show();



        parameters.forEach(student ->{
            FXMLLoader s_loader = new FXMLLoader(HelloApplication.class.getResource("student.fxml"));
            Stage s_stage = new Stage();
            Scene s_scene;
            try {
                s_scene = new Scene(s_loader.load(), 600, 400);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            StudentController studentController = s_loader.getController();
            studentController.setStudent(student);
            studentController.setTest(idTest);
            studentController.setService(service);

            s_stage.setTitle(student);
            s_stage.setScene(s_scene);
            s_stage.show();
        });

    }

    public static void main(String[] args) {
        launch(args);
    }
}