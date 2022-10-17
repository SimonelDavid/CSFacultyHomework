<<<<<<< HEAD
package org.example.seminar1;

import org.example.seminar1.factories.Strategy;
import org.example.seminar1.models.Message;
import org.example.seminar1.models.MessageTask;
import org.example.seminar1.models.Task;
import org.example.seminar1.runners.PrinterTaskRunner;
import org.example.seminar1.runners.StrategyTaskRunner;
import org.example.seminar1.runners.TaskRunner;
=======
package main.java.org.example.seminar1;


import main.java.org.example.seminar1.factories.Strategy;
import main.java.org.example.seminar1.models.Message;
import main.java.org.example.seminar1.models.MessageTask;
import main.java.org.example.seminar1.models.Task;
import main.java.org.example.seminar1.runners.PrinterTaskRunner;
import main.java.org.example.seminar1.runners.StrategyTaskRunner;
import main.java.org.example.seminar1.runners.TaskRunner;
>>>>>>> dd91ed8 (homerowrk prep)

import java.time.LocalDateTime;
import java.util.LinkedList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        //testMessage();
        testTaskRunner();

    }

    private static void testMessage() {
        Message message1 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task1 = new MessageTask("1", "d1", message1);

        Message message2 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task2 = new MessageTask("2", "d2", message2);

        Message message3 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task3 = new MessageTask("3", "d3", message3);

        Message message4 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task4 = new MessageTask("4", "d4", message4);

        Message message5 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task5 = new MessageTask("5", "d5", message5);

        List<Task> tasks = new LinkedList<>();
        tasks.add(task1);
        tasks.add(task2);
        tasks.add(task3);
        tasks.add(task4);
        tasks.add(task5);

        for (Task task : tasks) {
            System.out.println(task);
        }
    }
    
    private static void testTaskRunner() {
        Message message1 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task1 = new MessageTask("1", "d1", message1);

        Message message2 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task2 = new MessageTask("2", "d2", message2);

        Message message3 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task3 = new MessageTask("3", "d3", message3);

        Message message4 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task4 = new MessageTask("4", "d4", message4);

        Message message5 = new Message("hello", "mircea", "fenesan", LocalDateTime.now());
        Task task5 = new MessageTask("5", "d5", message5);

        List<Task> tasks = new LinkedList<>();
        tasks.add(task1);
        tasks.add(task2);
        tasks.add(task3);
        tasks.add(task4);
        tasks.add(task5);

        TaskRunner strategyTaskRunner = new StrategyTaskRunner(Strategy.LIFO);
        TaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);

        for (Task task : tasks) {
//            strategyTaskRunner.addTask(task);
            printerTaskRunner.addTask(task);
        }

//        strategyTaskRunner.executeAll();
        printerTaskRunner.executeAll();
    }
}
