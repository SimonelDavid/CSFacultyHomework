package main.java.org.example.seminar1.containers;

import main.java.org.example.seminar1.models.Task;

public class QueueContainer extends StackQueueContainer{
    @Override
    public Task remove() {
        return super.tasks.remove(0);
    }
}
