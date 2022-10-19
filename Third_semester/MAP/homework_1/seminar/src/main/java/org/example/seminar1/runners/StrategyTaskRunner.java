package org.example.seminar1.runners;

import org.example.seminar1.containers.Container;
import org.example.seminar1.factories.Strategy;
import org.example.seminar1.factories.TaskContainerFactory;
import org.example.seminar1.models.Task;

public class StrategyTaskRunner implements TaskRunner {
    private Container container;

    public StrategyTaskRunner(Strategy strategy) {
        container = TaskContainerFactory.getInstance().createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        if (!container.isEmpty()) {
            Task t = container.remove();
            t.execute();
        }
    }

    @Override
    public void executeAll() {
        while (!container.isEmpty()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
