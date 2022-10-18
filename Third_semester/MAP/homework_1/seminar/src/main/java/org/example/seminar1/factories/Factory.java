package main.java.org.example.seminar1.factories;

import main.java.org.example.seminar1.containers.Container;

public interface Factory {
    Container createContainer(Strategy strategy);
}
