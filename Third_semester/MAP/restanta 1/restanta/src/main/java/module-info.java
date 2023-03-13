module examen.examensimon {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    //requires com.almasb.fxgl.all;
    requires java.sql;

    opens examen.examensimon to javafx.fxml;
    exports examen.examensimon;
    opens examen.examensimon.domain to javafx.fxml;
    opens examen.examensimon.controller to javafx.fxml;
    exports examen.examensimon.service;
    exports examen.examensimon.domain;
    exports examen.examensimon.repository;
    exports examen.examensimon.controller;
    exports examen.examensimon.utils.utils;
    exports examen.examensimon.utils.observer;
}