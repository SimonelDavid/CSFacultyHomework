package org.example.seminar1.runners;

import org.example.seminar1.utils.Utils;

import java.time.LocalDateTime;

public class PrinterTaskRunner extends AbstractTaskRunner {
    public PrinterTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    @Override
    public void executeOneTask() {
        taskRunner.executeOneTask();
        showTimeOfExecution();
    }

    private static void showTimeOfExecution() {
        System.out.println("Task executed at: " + LocalDateTime.now().format(Utils.DATE_TIME_FORMATTER));
    }
}
