package org.example.seminar1.containers;

import org.example.seminar1.models.Task;

public interface Container {
    Task remove();

    void add(Task task);

    int size();

    boolean isEmpty();
}
