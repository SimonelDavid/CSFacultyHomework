package com.example.lab1;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class Lab1Application {

    public static void main(String[] args) throws InterruptedException {

        int n=20000000;
        int p=20;
        int[] vector1=new int[n];
        int[] vector2=new int[n];
        int[] res=new int[n];
        for(int i=0;i<n;i++) {
            vector1[i] = i;
            vector2[i] = i;
        }
        long time1= System.nanoTime();
        calculateSecventialSum(n,vector1,vector2,res);
        long time2= System.nanoTime();

        long time3= System.nanoTime();
        caclulateParallelSum(n,vector1,vector2,res,p);
        long time4= System.nanoTime();

        long time5= System.nanoTime();
        caclulateParallelSumCycling(n,vector1,vector2,res,p);
        long time6= System.nanoTime();

        System.out.println("secvential " + (time2-time1));
        System.out.println("parallel   " + (time4-time3));
        System.out.println("circular   " + (time6-time5));

//        for(int i=0;i<n;i++){
//            System.out.println(res[i]);
//        }
    }
    private static void calculateSecventialSum(int n,int[] vector1,int[] vector2,int[] res){
        for(int i=0;i<n;i++)
            res[i]=vector1[i]+vector2[i];
    }

    private static void caclulateParallelSum(int n, int[] vector1, int[] vector2, int[] res, int p) throws InterruptedException {
        int segmentSize = n/p;
        int rest = n&p;
        Thread[] threads = new Thread[p];
        int startSegment = 0;
        int endSegment;
        for (int i = 0; i < p; i++){
            endSegment = startSegment + segmentSize;
            if(rest > 0){
                endSegment++;
                rest--;
            }
            threads[i] = new MyThread(res, vector1, vector2, startSegment, endSegment);
            threads[i].start();
            startSegment = endSegment;
        }
        for (int i = 0; i < p; i++){
            threads[i].join();
        }
    }
    private static void caclulateParallelSumCycling(int n, int[] vector1, int[] vector2, int[] res, int p) throws InterruptedException {
        Thread[] threads = new Thread[p];
        int startSegment = 0;
        for (int i = 0; i < p; i++){
            threads[i] = new MyThreadCircular(res, vector1, vector2, startSegment, p, n);
            threads[i].start();
            startSegment++;
        }
        for (int i = 0; i < p; i++){
            threads[i].join();
        }
    }
    private static class MyThread extends Thread{
        private int[] res, vector1, vector2;
        private int startSegment, endSegment;
        public MyThread(int[] res, int[] vector1, int[] vector2, int startSegment, int endSegment){
            this.res = res;
            this.vector1 = vector1;
            this.vector2 = vector2;
            this.startSegment = startSegment;
            this.endSegment = endSegment;
        }

        @Override
        public void run(){
            for (int i = startSegment; i < endSegment; i++){
                res[i] = (int) (Math.pow(vector1[i],3)+Math.pow(vector2[i],3));
                res[i] = vector1[i]+vector2[i];
            }
        }
    }

    private static class MyThreadCircular extends Thread{
        private int[] res, vector1, vector2;
        private int startSegment, p, n;
        public MyThreadCircular(int[] res, int[] vector1, int[] vector2, int startSegment, int p, int n){
            this.res = res;
            this.vector1 = vector1;
            this.vector2 = vector2;
            this.startSegment = startSegment;
            this.n = n;
            this.p = p;
        }

        @Override
        public void run(){
            for (int i = startSegment; i < n; i+=p){
                res[i] = (int) (Math.pow(vector1[i],3)+Math.pow(vector2[i],3));
                res[i] = vector1[i]+vector2[i];
            }
        }
    }
}
