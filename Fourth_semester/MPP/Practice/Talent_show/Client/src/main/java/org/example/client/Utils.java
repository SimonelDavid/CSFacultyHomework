package org.example.client;

import javafx.scene.control.Alert;

import java.util.Random;

public class Utils {
    public static void showError(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR, message);
        alert.setTitle("error");
        alert.showAndWait();
    }
    public static void showInfo(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION, message);
        alert.setTitle("info");
        alert.showAndWait();
    }

    public static String shuffleString(String input) {
        char[] chars = input.toCharArray();
        Random rand = new Random();

        for (int i = 0; i < chars.length; i++) {
            int randomIndex = rand.nextInt(chars.length);
            char temp = chars[i];
            chars[i] = chars[randomIndex];
            chars[randomIndex] = temp;
        }
        return new String(chars);
    }

    public static int compareStrings(String string1, String string2) {
        int count = 0;
        int minLength = Math.min(string1.length(), string2.length());
        for (int i = 0; i < minLength; i++) {
            if (string1.charAt(i) == string2.charAt(i)) {
                count++;
            }
        }
        return count;
    }
}
