module examen.restantasimonel {
    requires javafx.controls;
    requires javafx.fxml;

//    requires org.controlsfx.controls;
//    requires com.dlsc.formsfx;
//    requires org.kordamp.bootstrapfx.core;
//    requires com.almasb.fxgl.all;
    requires java.sql;

    opens examen.restantasimonel to javafx.fxml;
    exports examen.restantasimonel;
    opens examen.restantasimonel.domain to javafx.fxml;
    opens examen.restantasimonel.controller to javafx.fxml;
    exports examen.restantasimonel.service;
    exports examen.restantasimonel.domain;
    exports examen.restantasimonel.repository;
    exports examen.restantasimonel.controller;
    exports examen.restantasimonel.utils.utils;
    exports examen.restantasimonel.utils.observer;
}