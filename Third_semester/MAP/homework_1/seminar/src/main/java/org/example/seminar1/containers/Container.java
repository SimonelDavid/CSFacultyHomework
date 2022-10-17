<<<<<<< HEAD
package org.example.seminar1.containers;

import org.example.seminar1.models.Task;
=======
package main.java.org.example.seminar1.containers;


import main.java.org.example.seminar1.models.Task;
>>>>>>> dd91ed8 (homerowrk prep)

public interface Container {
    Task remove();

    void add(Task task);

    int size();

    boolean isEmpty();
}
