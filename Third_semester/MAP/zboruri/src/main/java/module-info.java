module com.example.zboruri {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens com.example.zboruri to javafx.fxml;
    opens com.example.zboruri.Controller to javafx.fxml;

    exports com.example.zboruri;
    exports com.example.zboruri.Entities;
}