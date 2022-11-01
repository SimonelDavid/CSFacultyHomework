package domain;

import java.util.Objects;

public class Friendship {
    /**
     * relație de prietenie dintre doi useri
     */
    String user1;
    String user2;

    public Friendship(String user1, String user2) {
        this.user1 = user1;
        this.user2 = user2;
    }

    public String getUser1() {
        return user1;
    }

    public void setUser1(String user1) {
        this.user1 = user1;
    }

    public String getUser2() {
        return user2;
    }

    public void setUser2(String user2) {
        this.user2 = user2;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return Objects.equals(user1, that.user1) && Objects.equals(user2, that.user2) ||
                Objects.equals(user2, that.user1) && Objects.equals(user1, that.user2);
    }

    @Override
    public String toString() {
        return user1 + " este prieten cu " + user2;
    }

    @Override
    public int hashCode() {
        return Objects.hash(user1, user2);
    }
}
