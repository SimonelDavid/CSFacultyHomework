package repo;

import domain.Friendship;
import domain.User;
import exceptions.RepoException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class FriendshipRepo {
    /**
     * repo pentru relațiile de prietenie
     */
    private final Set<Friendship> friendships = new HashSet<>();

    private String filePath;

    /**
     * constructor
     * @param filePath fișierul din care se preiau relațiile de prietenie
     */
    public FriendshipRepo(String filePath) {
        this.filePath = filePath;
        readFriendshipsFromFile();
    }

    /**
     * obține mulțimea tuturor relațiilor de prietenie
     * @return o mulțime care conține toate relațiile de prietenie din aplicație
     */
    public Set<Friendship> getFriendships() {
        return friendships;
    }

    /**
     * importă relațiile de prietenie din fișier
     */
    private void readFriendshipsFromFile(){
        friendships.clear();
        try {
            File file = new File(filePath);
            Scanner myReader = new Scanner(file);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                String[] split = data.split(",");
                Friendship newFriendship = new Friendship(split[0], split[1]);
                friendships.add(newFriendship);
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("Nu s-a putut găsi fișierul de import");
            e.printStackTrace();
        }
    }

    /**
     * salvează toate relațiile de prietenie în fișier
     */
    private void saveFriendshipsToFile(){
        try {
            FileWriter myWriter = new FileWriter(filePath);
            for (Friendship friendship : friendships) {
                myWriter.write(friendship.getUser1()
                        + ","
                        + friendship.getUser2()
                        + ",\n");
            }
            myWriter.close();
        } catch (IOException e) {
            System.out.println("Nu s-au putut salva datele în fișier");
            e.printStackTrace();
        }
    }

    /**
     * adaugă o relație de prietenie
     * @param friendship relația de prietenie care trebuie adăugată
     * @throws RepoException dacă relația există deja
     */
    public void addFriendship(Friendship friendship) throws RepoException {
        if(!friendships.add(friendship)){
            throw new RepoException("prietenia exista deja");
        }
        saveFriendshipsToFile();
    }

    /**
     * șterge o relație de prietenie
     * @param friendship relația care ar trebui ștearsă
     * @throws RepoException dacă relația nu există
     */
    public void removeFriendship(Friendship friendship) throws RepoException{
        if(!friendships.remove(friendship)){
            throw new RepoException("prietenia nu există");
        }
        saveFriendshipsToFile();
    }

}
