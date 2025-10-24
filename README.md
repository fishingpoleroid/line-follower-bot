<img width="1106" height="727" alt="image" src="https://github.com/user-attachments/assets/c4025e2a-8e46-4ace-a1d2-ba168c44e6dd" />

## Line Follower Bot Project

### What I did
I created a line follower bot with PID control (and one without a PID control where I hardcoded the turns, refer to branch main for its code).

### How I did it
I implemented a circuit in Tinkercad comprising of an Arduino UNO, two gearbox-motors, a 9V battery, and 5 push buttons (I didn’t use the IR sensor component in Tinkercad because I couldn’t find a way to trigger them individually, so I used push buttons in place of them).
Based upon this circuit I wrote some code that used a PID controller to follow the line. In my code there is a function that calculates PID value using current or in some cases previous error.

### What I learnt
I had no prior knowledge of PID controllers, upon watching a few YouTube videos, and reading some articles on the web, I came to learn how they work and why, and where they are used.

### What can be done better
In this implementation, I have used a PID controller that needs a few constants, namely proportionality constant, integral constant, and derivative constant. These constants need to be calibrated for every such bot. A function can be implemented that does this calibration on the initial startup of the bot.

I’ve guessed the motor speed values on intuition, and in practice these values can be adjusted according to the particular line follower in order to have the fastest speed.

This line follower is only made to follow lines that don't split or merge, in case of a line that splits we need to implement some logic that decides which path the bot should take.

This line follower cannot solve any mazes, and it doesn’t have any algorithm that keeps track of the map and finds a solution.

### The problems I faced
I couldn’t find a way to trigger the IR sensors in Tinkercad to test my code, so I replaced them with push buttons. In practice we can just replace all the push buttons with IR sensors and take the NOT operator on all the sensor readings in code, and the bot would work the same.

This is the first time I’ve used a motor driver, I was trying to control the motor speeds from the input2, and input4 pinouts (I had the enable pins connected to power source essentially giving them a HIGH input), and later I came to know that I could just input pins to set the direction of rotation, and enable pins to control motor speeds.

---

## Study Report

### Algorithms
I’ve added implementations of these algorithms in C++ to the master branch.

#### A*:
* **Resources used:**
    * https://youtu.be/-L-WgKMFuhE?si=XXvHXZQw9vd-MPF5
    * https://youtu.be/mZfyt03LDH4?si=7hdDB_mI61tPugEo
* **My understanding:**
    * A* uses a set of three data namely, G-cost (distance from starting node), H-cost (distance from target node), and F-cost (sum of G and H costs). The intuition is that it uses these values (G, F, and H costs) to keep track of how much our path is straying away from the straight line connecting the starting and target nodes. To find the fastest path we just need to move as close to this straight line while also avoiding obstruction along the way.

#### Dijkstra:
* **Resources used:**
    * https://youtu.be/EFg3u_E6eHU?si=uknmbdTkCdJD0H_s
* **My understanding:**
    * Dijkstra’s algorithm finds the shortest distance to all the nodes in a graph from a reference node. In this algorithm, we start from the start node and work our way through all the nodes by picking the closest unvisited node each time and updating the shortest distance to all its adjacent unvisited nodes so that we know the updated shortest path from the reference node to each of the adjacent nodes. Once we’ve visited all the nodes, it is guaranteed that we have a data that tells us the shortest distance of each of the node in the graph from the reference node.

#### BFS:
* **Resources used:**
    * https://youtu.be/xlVX7dXLS64?si=rnk2pGKynXtEhVBA
* **My understanding:**
    * Breadth First Search is a graph traversal algorithm (meaning its purpose is to traverse each node in a graph). It approaches this problem by starting from the start node and going through each of its adjacent (or neighbouring) nodes first. Once we have kept a track of all the adjacent nodes, we can do the same for these adjacent nodes one by one that is, we choose one of the unvisited adjacent nodes, mark it as visited, and keep track of all its adjacent nodes. We do this till we have marked every single node as visited.

#### DFS:
* **Resources used:**
    * https://youtu.be/PMMc4VsIacU?si=u11f1nmw__FPAzPV
* **My understanding:**
    * Depth First Search is very similar to BFS as both algorithm’s purposes are the same, the difference is how they go through with the execution. DFS differs from BFS because instead of search each of the neighbouring nodes at a time, it searches through an entire stream of nodes till it reaches a dead end, which is when it backtracks for unvisited streams. This process of backtracking and searching entire streams at once is repeated till the algorithm has gone through every node and marked it as visited.

---

### PID controllers
* **Resources consumed:**
    * https://youtu.be/UR0hOmjaHp0?si=sx-hZhCmsRbznSFl
    * https://youtu.be/XfAt6hNV8XM?si=Tx3VmOdDBG0f0lTP
* **My understanding:**
    * PID controllers use error values to determine how far off a system is from ideal state. Using this insight, we can make adjustments accordingly. The benefit of using PID controllers is that PID controllers can calculate the amount of adjustment required in real-time, thus giving our system very high accuracy.
    * They achieve this by summing up three values:
    1.  **Proportional**
        * P = Kp * e
    2.  **Integral**
        * I = Ki * (sum of all past errors)
    3.  **Derivative**
        * D = Kd * (current error – previous error)
    * Where, Kp, Ki, Kd are constants that need to be tuned for every system. And e is the calculated error (error is the value that corresponds to how far off a system is from a desired state).
    *
    * Integral is the sum of errors throughout the runtime of our system;
    * Derivative is the difference between current and previous error;
    *
    * So, PID value = P + I + D
