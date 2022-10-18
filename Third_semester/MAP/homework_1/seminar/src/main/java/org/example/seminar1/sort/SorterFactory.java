package main.java.org.example.seminar1.sort;

import main.java.org.example.seminar1.utils.SortingStrategy;

public class SorterFactory
{
    private static SorterFactory instance = null;

    private SorterFactory() {}

    public static SorterFactory getInstance()
    {
        if(instance == null)
            instance = new SorterFactory();
        return instance;
    }

    public AbstractSorter createSorter(SortingStrategy strategy)
    {
        return switch (strategy) {
            case QUICK_SORT -> new QuickSort();
            case BUBBLE_SORT -> new BubbleSort();
        };
    }
}