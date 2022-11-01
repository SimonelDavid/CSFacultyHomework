package service;

public class Validator {
    /**
     * validează numele unui utilizator
     * @param userName numele de utilizator propus pentru validare
     * @return true dacă numele de utilizator contine doar litere și cifre
     */
    public static boolean userNameValidator(String userName){
        return userName.matches("[a-zA-Z0-9]");
    }
}
