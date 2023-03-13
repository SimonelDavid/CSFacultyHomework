package com.example.zboruri.Observer;
import com.example.zboruri.Events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}
