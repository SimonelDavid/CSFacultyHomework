module com.wms.wmsproject {
    requires javafx.controls;
    requires javafx.fxml;
    requires spring.boot.autoconfigure;
    requires jakarta.persistence;
    requires jakarta.annotation;
    requires spring.boot;
    requires spring.context;
    requires jakarta.transaction;
    requires spring.beans;
    requires spring.data.jpa;


    opens com.wms.wmsproject to javafx.fxml;
    exports com.wms.wmsproject;
}