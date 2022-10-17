package org.example.seminar1.factories;

import org.example.seminar1.containers.Container;

public interface Factory {
    Container createContainer(Strategy strategy);
}
