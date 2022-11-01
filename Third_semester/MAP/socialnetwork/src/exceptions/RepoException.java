package exceptions;

public class RepoException extends Exception {
    /**
     * excepție aruncată în cazuri de eroare la repo
     * @param message mesajul erorii
     */
    public RepoException(String message) {
        super(message);
    }
}
