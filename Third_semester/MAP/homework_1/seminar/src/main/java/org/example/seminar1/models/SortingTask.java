package main.java.org.example.seminar1.models;


import main.java.org.example.seminar1.sort.AbstractSorter;
import main.java.org.example.seminar1.sort.SorterFactory;
import main.java.org.example.seminar1.utils.SortingStrategy;

public class SortingTask extends Task
{
    private int[] numbers;
    private AbstractSorter sorter;

    protected SortingTask(int[] array, SortingStrategy strategy)
    {
        this.numbers = array;
        this.sorter = SorterFactory.getInstance().createSorter(strategy);
    }

    @Override
    public void execute()
    {
        this.sorter.sort(this.numbers);
    }

    @Override
    public String toString()
    {
        StringBuilder s = new StringBuilder();
        for(int i = 0; i < this.numbers.length - 1; i++)
            s.append(this.numbers[i]).append(", ");
        s.append(this.numbers[this.numbers.length - 1]);
        return s.toString();
    }
}