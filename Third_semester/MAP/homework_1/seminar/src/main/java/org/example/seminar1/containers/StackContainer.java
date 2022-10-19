package main.java.org.example.seminar1.containers;


import main.java.org.example.seminar1.models.Task;

public class StackContainer extends StackQueueContainer implements Container {

    @Override
    public Task remove() {

        return super.tasks.remove(size() - 1);
    }

}
