package org.example.seminar1.models;

import org.example.seminar1.sort.AbstractSorter;
import org.example.seminar1.sort.SorterFactory;
import org.example.seminar1.utils.SortingStrategy;

public class SortingTask extends Task
{
    private int[] arr;
    private SortingStrategy strategy;
    private AbstractSorter sorter;
    public SortingTask(String taskId, String description, SortingStrategy strategy, int[] arr) {
        super(taskId, description);
        this.strategy=strategy;
        this.arr = arr;
    }

    @Override
    public void execute() {
        sorter= SorterFactory.getInstance().createSorter(strategy);
        int[] sortedArr=sorter.sort(arr);
        for(int i:sortedArr){
            System.out.println(i);
        }
    }
}