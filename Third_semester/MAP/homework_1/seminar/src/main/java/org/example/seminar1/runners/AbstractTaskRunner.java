package org.example.seminar1.runners;

import org.example.seminar1.models.Task;

public abstract class AbstractTaskRunner implements TaskRunner {
    protected final TaskRunner taskRunner;

    public AbstractTaskRunner(TaskRunner taskRunner) {
        this.taskRunner = taskRunner;
    }

    @Override
    public abstract void executeOneTask();

    @Override
    public void executeAll() {
        while (taskRunner.hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        taskRunner.addTask(t);
    }

    @Override
    public boolean hasTask() {
        return taskRunner.hasTask();
    }
}
