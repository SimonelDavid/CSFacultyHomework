package service;

import domain.Friendship;
import domain.User;
import exceptions.RepoException;
import repo.FriendshipRepo;
import repo.UserRepo;

import java.util.*;

public class UserService {
    /**
     * service pentru useri și relații de prietenii
     */
    UserRepo repo;
    FriendshipRepo friendshipRepo;

    NetworksService networksService;

    /**
     * constructor
     * @param repo repo pentru utilizatori
     * @param friendshipRepo repo pentru relații de prietenie
     */
    public UserService(UserRepo repo, FriendshipRepo friendshipRepo) {
        this.friendshipRepo = friendshipRepo;
        this.repo = repo;
        networksService = new NetworksService(friendshipRepo, repo);
    }

    /**
     * adaugare un utilizator nou
     * @param userName numele utilizatorului
     * @param password parola utilizatorului
     * @throws RepoException dacă utilizatorul există deja
     */
    public void addUser(String userName, String password) throws RepoException {
        repo.addUser(new User(userName, password));
    }

    /**
     * șterge un utilizator
     * @param userName numele utilizatorului care trebuie șters
     * @throws RepoException dacă utilizatorul nu există
     */
    public void removeUser(String userName) throws RepoException {
        repo.removeUser(new User(userName));
        removeFriendships(userName);
    }

    /**
     * toți utilizatorii
     * @return o mulțime cu toți utilizatorii din aplicație
     */
    public Set<User> getUsers() {
        return repo.getUsers();
    }

    /**
     * verifică dacă un nume de utilizator corespunde unui user
     * @param userName numele de utilizator de verificat
     * @return true dacă există un user cu numele userName
     */
    private boolean isUser(String userName) {
        return repo.find(new User(userName)) != null;
    }

    /**
     * verifică dacă două nume de utilizatori corespund unor utilizatori valizi
     * @param user1 nume de utilizator de verificat
     * @param user2 nume de utilizator de verificat
     * @return dacă user1 și user2 corespund unor utilozatori valizi
     */
    private boolean areUsers(String user1, String user2) {
        return isUser(user1) && isUser(user2);
    }

    /**
     * adaugă o relație nouă de prietenie între user1 și user2
     * @param user1 numele primului user
     * @param user2 numele celuilalt user
     * @throws RepoException dacă relația de prietenie există deja
     */
    public void addFriendship(String user1, String user2) throws RepoException {
        if (areUsers(user1, user2)) {
            friendshipRepo.addFriendship(new Friendship(user1, user2));
        }else throw new RepoException("prietenia se leagă doar între useri valizi");
    }

    /**
     * șterge relația de prietenie dintre user1 și user2
     * @param user1 primul utilizator
     * @param user2 celalalt utilizator
     * @throws RepoException dacă relatia de prietenie nu există
     */
    public void removeFriendship(String user1, String user2) throws RepoException {
        if (areUsers(user1, user2)) {
            friendshipRepo.removeFriendship(new Friendship(user1, user2));
        }
    }

    /**
     * șterge toate relațiile de prietenie ale lui user
     * @param user numele de utilizator ale cărui relații trebuie șterse (nu referă neapărat un user valid)
     */
    public void removeFriendships(String user) {
        List<Friendship> friendshipsToBeDeleted = new ArrayList<>();
        for (Friendship friendship : friendshipRepo.getFriendships()) {
            if (Objects.equals(friendship.getUser2(), user) || Objects.equals(friendship.getUser1(), user)) {
                friendshipsToBeDeleted.add(friendship);
            }
        }
        for (Friendship friendship : friendshipsToBeDeleted) {
            try {
                friendshipRepo.removeFriendship(friendship);
            }catch (RepoException ignored){
                ///
            }
        }
    }

    /**
     * toate relațiile de prietenie
     * @return o mulțime cu relații de prietenie
     */
    public Set<Friendship> getFriendships() {
        return friendshipRepo.getFriendships();
    }

    /**
     * lista de prieteni a unui utilizator
     * @param user numele utilizatorului
     * @return lista cu prietenii utilizatorului user
     * @throws RepoException daca user nu referă către un utilizator valid
     */
    public Set<String> getFriends(String user) throws RepoException {
        if(!isUser(user)){
            throw new RepoException(user + " nu este utilizator");
        }
        return networksService.getFriends(user);
    }

    /**
     * Lista tuturor rețelelor din aplicație
     * @return o listă de rețele; o rețea este o mulțime de utilizatori
     */
    public List<Set<User>> getNetworks(){
        return networksService.networks();
    }

    /**
     * obține cea mai lungă comunitate
     * @return o mulțime de useri (un network)
     */
    public Set<User> getLongestNetwork(){
        return networksService.longestNetwork();
    }
}
