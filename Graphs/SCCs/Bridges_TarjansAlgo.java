// There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.

// A critical connection is a connection that, if removed, will make some servers unable to reach some other server.

// Return all critical connections in the network in any order.

// Constraints:

// 2 <= n <= 10^5
// n - 1 <= connections.length <= 10^5
// 0 <= ai, bi <= n - 1
// ai != bi
// There are no repeated connections.

import java.util.*;

class Bridges_TarjansAlgo {
    static List<List<Integer>> graph;
    static int[] tin, low;
    static boolean[] vis;
    static int timer;
    static List<List<Integer>> ans;
    
    public static List<List<Integer>> criticalConnections(int n, List<List<Integer>> connections) {
        graph = new ArrayList<>();
        ans = new ArrayList<>();
        for(int i = 0; i < n; i++){
            graph.add(new ArrayList<>());
        }
        for(List<Integer> conn: connections){
            graph.get(conn.get(0)).add(conn.get(1));
            graph.get(conn.get(1)).add(conn.get(0));
        }
        tin = new int[n]; low = new int[n];
        vis = new boolean[n];
        timer = 1;
        
        tarjansAlgo(0, -1);
        return ans;
    }

    private static  void tarjansAlgo(int node, int par){
        vis[node] = true;
        tin[node] = low[node] = timer++;
        for(int adj: graph.get(node)){
            if(adj == par) continue;
            if(!vis[adj]){
                tarjansAlgo(adj, node);
                low[node] = Math.min(low[node], low[adj]);
                if(low[adj] > tin[node]){
                    ans.add(Arrays.asList(node, adj));
                }
            }
            else low[node] = Math.min(low[node], low[adj]);
        }
    }
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)) {
            int n = sc.nextInt(), m = sc.nextInt();
            List<List<Integer>> connections = new ArrayList<>();
            while(m-- > 0){
                int u = sc.nextInt(), v = sc.nextInt();
                connections.add(Arrays.asList(u, v));
            }   
            ans = criticalConnections(n, connections);
            for(List<Integer> bridge: ans){
                System.out.println(bridge.get(0) + " -> " + bridge.get(1));
            }
        }
    }
}