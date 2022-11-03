package ui;

import domain.FriendShip;
import domain.User;
import service.Service;
import service.Service0;

import java.util.List;
import java.util.Scanner;
import java.util.UUID;

public class ConsoleUI extends AbstractUI {

    private Scanner cin;
    public ConsoleUI(Service<UUID> srv) {
        super(srv);
        cin = new Scanner(System.in);
    }

    /**
     * starts the console user interface
     * where all the functionalities are represented by an integer
     */
    @Override
    public void start() {
        cin = new Scanner(System.in);

        System.out.println("Functionalitatile sunt : ");
        System.out.println("0 - exit");
        System.out.println("1 - Afiseaza toate functionalitatile");
        System.out.println("2 - Adauga utilizator");
        System.out.println("3 - Sterge un utilizator");
        System.out.println("4 - Adauga prietenie");
        System.out.println("5 - Sterge prietenie");
        System.out.println("6 - Afiseaza toti utilizatorii");
        System.out.println("7 - Afiseaza toate prieteniile");
        System.out.println("8 - Afiseaza numarul de comunitati");
        System.out.println("9 - Afiseaza cea mai sociabila comunitate");
        System.out.println("10 - Adauga valori predefinite");
        System.out.println("11 - Afiseaza toate comunitatile");

        String email1, email2, email;

        while(true)
        {
            System.out.print("Give a command: ");
            int command = cin.nextInt();

            switch (command)
            {
                case 0:
                    cin.close();
                    return;
                case 1:
                    System.out.println("Functionalitatile sunt : ");
                    System.out.println("0 - exit");
                    System.out.println("1 - Afiseaza toate functionalitatile");
                    System.out.println("2 - Adauga utilizator");
                    System.out.println("3 - Sterge un utilizator");
                    System.out.println("4 - Adauga prietenie");
                    System.out.println("5 - Sterge prietenie");
                    System.out.println("6 - Afiseaza toti utilizatorii");
                    System.out.println("7 - Afiseaza toate prieteniile");
                    System.out.println("8 - Afiseaza numarul de comunitati");
                    System.out.println("9 - Afiseaza cea mai sociabila comunitate");
                    System.out.println("10 - Adauga valori predefinite");
                    System.out.println("11 - Afiseaza toate comunitatile");
                    break;

                case 2:
                    User user = readUser();
                    srv.addUser(user);
                    break;

                case 3:
                    email = readEmail();
                    srv.deleteUser(email);
                    break;

                case 4:
                    email1 = readEmail();
                    email2 = readEmail();
                    srv.createFriendship(email1, email2);
                    break;

                case 5:
                    email1 = readEmail();
                    email2 = readEmail();
                    srv.deleteFriendship(email1, email2);
                    break;

                case 6:
                    Iterable<User> it = srv.getAllUsers();
                    it.forEach(System.out::println);
                    break;

                case 7:
                    Iterable<FriendShip> itf = srv.getAllFriendships();
                    itf.forEach(System.out::println);
                    break;

                case 8:
                    System.out.println("The number of communities is: " + srv.numberOfCommunities());
                    break;

                case 9:
                    {
                        List<Iterable<User>> it1 = (List) srv.mostSociableCommunity();
                        if(it1.size() == 1)
                            System.out.println("The most sociable community is:");
                        else
                            System.out.println("The most sociable communities are:");

                        for(var x : it1) {
                            x.forEach(System.out::println);
                            System.out.println("\n");
                        }
                    }
                    break;

                case 10:
                    System.out.print("Choose what iteration of predefined values: ");
                    int i = cin.nextInt();
                    srv.add_Predefined_Values(i);
                    break;

                case 11:
                    System.out.print("Communities:");
                    List<List<User>> l = srv.getAllCommunities();
                    l.stream().forEach(System.out::println);
                    break;
                    
                default:
                    System.out.println("Wrong Command!");
            }
        }
    }

    /**
     * Reads a User from the console and returns it.
     *
     * @return  The User that was read.
     *
     */
    @Override
    public User readUser() {
        System.out.print("Firstname: ");
        String firstname = cin.next();
        System.out.print("Lastname: ");
        String lastname = cin.next();
        System.out.print("email: ");
        String email = cin.next();

        User user = new User(firstname, lastname, email);
        return user;
    }


    /**
     * Reads an email from the console and returns it.
     *
     * @return  The email that was read.
     *
     * @throws
     *
     */

    @Override
    public String readEmail() {
        System.out.print("Give the email: ");
        String email = cin.next();

        return email;
    }


}


