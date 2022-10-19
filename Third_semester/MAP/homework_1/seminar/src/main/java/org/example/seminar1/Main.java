package org.example.seminar1;

import org.example.seminar1.factories.Strategy;
import org.example.seminar1.models.Message;
import org.example.seminar1.models.MessageTask;
import org.example.seminar1.models.SortingTask;
import org.example.seminar1.models.Task;
import org.example.seminar1.runners.DelayTaskRunner;
import org.example.seminar1.runners.PrinterTaskRunner;
import org.example.seminar1.runners.StrategyTaskRunner;
import org.example.seminar1.runners.TaskRunner;
import org.example.seminar1.utils.SortingStrategy;

import java.time.LocalDateTime;
import java.util.LinkedList;
import java.util.List;

public class Main {

    private static Strategy strategy;

    public static void main(String[] args) {
        System.out.println("TEST MESSAGE\n");
        testMessage();
        if (args.length == 0) {
            System.out.println("strategy LIFO/FIFO");
        }
        String s = args[0].toUpperCase();
        if (!s.equals(Strategy.LIFO.toString()) && !s.equals(Strategy.FIFO.toString())) {
            System.out.println("strategy LIFO/FIFO");
        }
        if (s.equals(Strategy.LIFO.toString())) {
            strategy = Strategy.LIFO;
        } else {
            strategy = Strategy.FIFO;
        }

        System.out.println("TEST TASK RUNNER\n");
        testTaskRunner();
        System.out.println("\n");

        System.out.println("TEST SORTERS\n");
        testSorters();
        System.out.println("\n");
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

        TaskRunner strategyTaskRunner = new StrategyTaskRunner(strategy);
        TaskRunner strategyTaskRunnerPrinter = new StrategyTaskRunner(strategy);
        TaskRunner strategyTaskRunnerDelay = new StrategyTaskRunner(strategy);
        TaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunnerPrinter);
        TaskRunner delayTaskRunner = new DelayTaskRunner(strategyTaskRunnerDelay);

        for (Task task : tasks) {
            strategyTaskRunner.addTask(task);
            printerTaskRunner.addTask(task);
            delayTaskRunner.addTask(task);
        }

        System.out.println("NO DECORATOR\n");
        strategyTaskRunner.executeAll();


        System.out.println("DELAY\n");
        delayTaskRunner.executeAll();

        System.out.println("PRINTER\n");
        printerTaskRunner.executeAll();
    }

    private static void testSorters() {
        System.out.println("MergeSort\n");
        int[] arr1 = {4, 7, 1, 22, 8, 3, 9, 2};
        Task sortingTask1 = new SortingTask("1", "merge sort", SortingStrategy.QUICK_SORT, arr1);
        sortingTask1.execute();
//        for(int i=0;i<=arr1.length-1;i++){
//            System.out.println(arr1[i]);
//            System.out.println(" ");
//        }
        System.out.println("\n");
        System.out.println("BubbleSort\n");
        int[] arr2 = {10, 9, 8, 7, 6, 5};
        Task sortingTask2 = new SortingTask("2", "bubble sort", SortingStrategy.BUBBLE_SORT, arr2);
        sortingTask2.execute();
//        for(int i=0;i<=arr2.length-1;i++){
//            System.out.println(arr2[i]);
//            System.out.println(" ");
//        }
        System.out.println("\n");

    }
}
