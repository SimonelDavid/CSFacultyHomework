<<<<<<< HEAD
package org.example.seminar1.factories;

import org.example.seminar1.containers.Container;
import org.example.seminar1.containers.StackContainer;
=======
package main.java.org.example.seminar1.factories;


import main.java.org.example.seminar1.containers.Container;
import main.java.org.example.seminar1.containers.StackContainer;
>>>>>>> dd91ed8 (homerowrk prep)

public class TaskContainerFactory implements Factory {
    private final static TaskContainerFactory taskContainerFactory = new TaskContainerFactory();

    private TaskContainerFactory() {
    }

    public static TaskContainerFactory getInstance() {
        return taskContainerFactory;
    }

    @Override
    public Container createContainer(Strategy strategy) {
        if (strategy == Strategy.LIFO) {
            return new StackContainer();
        }

        return null;
    }
}
