package repo;

import domain.User;
import exceptions.RepoException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.Objects;
import java.util.Scanner;
import java.util.Set;

public class UserRepo {
    /**
     * repo pentru useri
     */
    private final Set<User> users = new HashSet<>();
    private String filePath;

    /**
     * Obține toți userii din aplicație
     * @return o mulțime cu userii care se găsesc în aplicație
     */
    public Set<User> getUsers() {
        return users;
    }

    /**
     * constructor
     * @param filePath fișierul din care se preiau toți userii salvați
     */
    public UserRepo(String filePath) {
        this.filePath = filePath;
        getUsersFromFile();
    }

    /**
     * preia userii din fișier
     */
    private void getUsersFromFile() {
        users.clear();
        try {
            File file = new File(filePath);
            Scanner myReader = new Scanner(file);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                String[] split = data.split(",");
                User newUser = new User(split[0], split[1]);
                users.add(newUser);
                ///System.out.println(newUser);
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("Nu s-a putut găsi fișierul de import");
            e.printStackTrace();
        }
    }

    /**
     * Caută un user în repo
     * @param user userul care trebuie căutat
     * @return true dacă userul a fost găsit
     */
    public User find(User user) {
        for (User user1 : users) {
            if (Objects.equals(user1, user))
                return user1;
        }
        return null;
    }

    /**
     * salvează toți userii în fișier
     */
    private void saveUsersInFile() {
        try {
            FileWriter myWriter = new FileWriter(filePath);
            for (User user : users) {
                myWriter.write(user.getUserName()
                        + ","
                        + user.getPassword()
                        + ",\n");
            }
            myWriter.close();
        } catch (IOException e) {
            System.out.println("Nu s-au putut salva datele în fișier");
            e.printStackTrace();
        }
    }

    /**
     * adaugă un utilizator în aplicație
     * @param user utilizatorul care ar trebui adăugat
     * @throws RepoException dacă utilizatorul există deja
     */
    public void addUser(User user) throws RepoException {
        if (!users.add(user)) {
            throw new RepoException("Userul există deja\n");
        }
        saveUsersInFile();
    }

    /**
     * șterge un utilizator din aplicație
     * @param user utilizatorul care trebuie șters
     * @throws RepoException dacă utilizatorul nu există
     */
    public void removeUser(User user) throws RepoException {
        if (!users.remove(user)) {
            throw new RepoException("Userul nu există\n");
        }
        saveUsersInFile();
    }

}
