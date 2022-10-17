package main.java.org.example.seminar1.factories;

import main.java.org.example.seminar1.containers.Container;
import main.java.org.example.seminar1.containers.StackContainer;

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
