package com.example.template.repo;

import java.util.List;

public interface Repo <T>{
    List<T> getAll();
    void getData();
}
