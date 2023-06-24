package org.example.utils;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.example.StartRpcServer;
import org.example.ZborDBRepository;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class UtilsGUI<E> {
    public static<E> void showTable(Class<E> the_class, TableView<E> t, List<E> l, Integer mode){
        Field[] fields = the_class.getDeclaredFields();
        List<TableColumn<E, String>> columns = new ArrayList<>();
        for(Field f : fields)
        {
            if(mode == 1 && !f.getName().equals("id")) {
                TableColumn<E, String> column = new TableColumn<>();
                column.setCellValueFactory(new PropertyValueFactory<>(f.getName()));
                columns.add(column);
            } else if (mode == 2 && !f.getName().equals("id") && !f.getName().equals("destinatie") && !f.getName().equals("data") && !f.getName().equals("aeroport")) {
                TableColumn<E, String> column = new TableColumn<>();
                column.setCellValueFactory(new PropertyValueFactory<>(f.getName()));
                columns.add(column);
            }
        }
        t.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        t.getColumns().setAll(columns);
        ObservableList<E> orderModel = FXCollections.observableArrayList();
        //System.out.println(l);
        orderModel.setAll(l);
        t.setItems(orderModel);
    }

    public static void showErrorMessage(Stage owner, String msg, String text) {
        Alert message = new Alert(Alert.AlertType.ERROR);
        message.setHeaderText(msg);
        message.setContentText(text);
        message.initOwner(owner);
        message.showAndWait();
    }

}
