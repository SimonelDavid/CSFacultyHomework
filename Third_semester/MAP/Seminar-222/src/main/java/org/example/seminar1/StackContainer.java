package org.example.seminar1;

import java.util.ArrayList;
import java.util.List;

public class StackContainer implements Container {
    List<Task> tasks = new ArrayList<>();

    @Override
    public Task remove() {
        return tasks.remove(size() - 1);
    }

    @Override
    public void add(Task task) {
        tasks.add(task);
    }

    @Override
    public int size() {
        return tasks.size();
    }

    @Override
    public boolean isEmpty() {
        return tasks.isEmpty();
    }
}
