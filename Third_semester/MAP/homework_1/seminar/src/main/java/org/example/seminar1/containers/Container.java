package main.java.org.example.seminar1.containers;

import main.java.org.example.seminar1.models.Task;

public interface Container {
    Task remove();

    void add(Task task);

    int size();

    boolean isEmpty();
}
