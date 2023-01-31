import java.util.*;

public class Assign1 {
    int n;
    int gr[][];
    int visited1[];
    int visited2[];
    Queue<Integer> q;

    Assign1(int n) {
        this.n = n;
        gr = new int[n][n];
        visited1 = new int[n];
        visited2 = new int[n];
        q = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            visited1[i] = 0;
            visited2[i] = 0;
            for (int j = 0; j < n; j++) {
                gr[i][j] = 0;
            }
        }
    }

    void create(int edge, Scanner sc) {
        int s, d;
        for (int i = 0; i < n; i++) {
            System.out.println("Enter source " + (i + 1));
            s = sc.nextInt();
            System.out.println("Enter destination " + (i + 1));
            d = sc.nextInt();
            gr[s][d] = 1;
            gr[d][s] = 1;
        }
    }

    void display() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(gr[i][j] + " ");
            }
            System.out.println();
        }
    }

    void dfs(int v1) {
        boolean[] visited = new boolean[n];
        for (int i = 0; i < n; i++) {
            visited[i] = false;
        }
        Stack<Integer> ss = new Stack<>();
        ss.push(v1);
        while (!ss.isEmpty()) {
            int a = ss.pop();
            if (!visited[a]) {
                System.out.print(a + " ");
                visited[a] = true;
            }
            for (int v2 = 0; v2 < n; v2++) {
                if (gr[a][v2] == 1 && !visited[v2]) {
                    ss.push(v2);
                }
            }
        }
    }

    void dfsr(int v1) {
        System.out.print(v1 + " ");
        visited1[v1] = 1;
        for (int v2 = 0; v2 < n; v2++) {
            if (gr[v1][v2] == 1 && visited1[v2] == 0) {
                dfsr(v2);
            }
        }
    }

    void bfs(int v1) {
        boolean visited[] = new boolean[n];
        Queue<Integer> q1 = new LinkedList<>();
        q1.add(v1);
        visited[v1] = true;
        while (!q1.isEmpty()) {
            int a = q1.remove();
            System.out.print(a + " ");
            for (int v2 = 0; v2 < n; v2++) {
                if (gr[a][v2] == 1 && !visited[v2]) {
                    q1.add(v2);
                    visited[v2] = true;
                }
            }
        }
    }

    void bfsr(int v1) {
        System.out.print(v1 + " ");
        visited2[v1] = 1;
        for (int v2 = 0; v2 < n; v2++) {
            if (gr[v1][v2] == 1 && visited2[v2] == 0) {
                q.add(v2);
                visited2[v2] = 1;
            }
        }
        if (q.isEmpty()) {
            return;
        }
        int x = q.peek();
        q.poll();
        bfsr(x);
    }

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of vertices: ");
        int v = sc.nextInt();
        System.out.println("Enter number of edges: ");
        int e = sc.nextInt();
        Assign1 a = new Assign1(v);
        a.create(e, sc);
        while (true) {
            System.out.println("1. Display Graph");
            System.out.println("2. DFS");
            System.out.println("3. BFS");
            System.out.println("4. Exit");
            System.out.println("Enter Choice: ");
            int ch = sc.nextInt();
            switch (ch) {
                case 1:
                    System.out.println("Entered Graph is: ");
                    a.display();
                    System.out.println();
                    break;
                case 2:
                    System.out.println("Enter node to start dfs from: ");
                    int n1 = sc.nextInt();
                    System.out.println("Recursive DFS: ");
                    a.dfsr(n1);
                    System.out.println();
                    System.out.println("Non - Recursive DFS: ");
                    a.dfs(n1);
                    System.out.println();
                    break;
                case 3:
                    System.out.println("Enter node to start bfs from: ");
                    int n2 = sc.nextInt();
                    System.out.println("Recursive BFS: ");
                    a.bfsr(n2);
                    System.out.println();
                    System.out.println("Non - Recursive BFS: ");
                    a.bfs(n2);
                    System.out.println();
                    break;
                case 4:
                    sc.close();
                    System.exit(0);
                default:
                    System.out.println("Enter correct choice!!");
                    break;
            }
        }
    }
}