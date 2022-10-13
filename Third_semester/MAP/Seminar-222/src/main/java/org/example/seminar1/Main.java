package org.example.seminar1;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        Message message = new Message("message1", "Vancea",
                "Boian", LocalDateTime.now());

        Task task1 = new MessageTask("1", "task1", message);
        Task task2 = new MessageTask("2", "task2", message);
        Task task3 = new MessageTask("3", "task3", message);
        Task task4 = new MessageTask("4", "task4", message);
        Task task5 = new MessageTask("5", "task5", message);

        List<Task> tasks = new ArrayList<>();
        tasks.add(task1);
        tasks.add(task2);
        tasks.add(task3);
        tasks.add(task4);
        tasks.add(task5);

        for (Task task : tasks) {
            System.out.println(task);
        }
    }
}