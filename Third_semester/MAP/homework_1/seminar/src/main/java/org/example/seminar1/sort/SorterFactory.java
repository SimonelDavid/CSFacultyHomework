package org.example.seminar1.sort;

import org.example.seminar1.utils.SortingStrategy;

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
        if(strategy==SortingStrategy.QUICK_SORT){
            return new QuickSort();
        }
        if(strategy==SortingStrategy.BUBBLE_SORT){
            return new BubbleSort();
        }
        return null;
    }
}