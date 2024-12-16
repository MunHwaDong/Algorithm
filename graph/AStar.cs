public class Astar : MonoBehaviour
{
    private float AStar(List<List<(float, int)>> graph, int st, int des)
    {
        //Open 집합
        Priority_Queue<(float, int)> fSet = new Priority_Queue<(float, int)>();
        
        //Close 집합
        HashSet<int> visited = new HashSet<int>();

        List<float> g = Enumerable.Repeat(float.MaxValue, graph.Count).ToList();

        g[st] = 0;

        fSet.Enqueue((0, st));
        visited.Add(st);
        
        while (!fSet.isEmpty())
        {
            (float, int) cur = fSet.Dequeue();

            if (visited.Contains(cur.Item2)) continue;
            
            visited.Add(cur.Item2);

            if (cur.Item2 == des) return g[cur.Item2];

            if(Mathf.Approximately(g[cur.Item2], cur.Item1))
            {
                foreach (var neighbor in graph[cur.Item2])
                {
                    var tentativeDist = g[cur.Item2] + neighbor.Item1;

                    if (tentativeDist < g[neighbor.Item2])
                    {
                        g[neighbor.Item2] = tentativeDist;

                        float f = tentativeDist + Heuristic(neighbor.Item2, des);
                        
                        fSet.Enqueue((f, neighbor.Item2));
                    }

                }
            }
        }

        if (g[des] == float.MaxValue) return -1;
        else return g[des];
    }

    private float Heuristic(float st, float des)
    {
        return Mathf.Abs(st - des);
    }
}
