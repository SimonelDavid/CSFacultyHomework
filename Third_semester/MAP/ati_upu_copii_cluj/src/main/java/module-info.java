module com.example.template {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens com.example.template to javafx.fxml;
    exports com.example.template;
    exports com.example.template.service;
    opens com.example.template.service to javafx.fxml;
}