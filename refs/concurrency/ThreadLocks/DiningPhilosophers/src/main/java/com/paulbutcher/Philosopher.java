public Philosopher extends Thread {
    private Chopstick left, right;
    private Random random;

    public Philosopher(Chopstick left, Chopstick right) {
        this.left = left;
        this.right = right;
        random = new Random();
    }

    public void run() {
        try {
            while (true) {
                Thread.sleep(random.nextInt(1000));         // Thinking
                synchronized(left) {                        // pick up left chopstick
                    synchronized(right) {                   // pick up right chopstick
                        Thread.sleep(random.nextInt(1000)); // Eating
                    }
                }
            }
        } catch (InterruptedException e) {}
    }
}
