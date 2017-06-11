import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Scanner;

public class DijkWithList
{
	public static final long LongInf = Long.MAX_VALUE / 2 - 2;
	public static final int IntegerInf = Integer.MAX_VALUE / 2 - 2;

	private static void initial(GraphNode nodes[], int s, long dist[])
	{
		for (int i = 0; i < nodes.length; ++i)
		{
			dist[i] = LongInf;
		}
		dist[s] = 0;
	}

	private static int w(GraphNode nodes[], int u, int v)
	{
		if (nodes[u].adj.containsKey(v))
		{
			return nodes[u].adj.get(v);
		}
		return IntegerInf;
	}

	private static boolean relax(int u, int v, GraphNode nodes[], long dist[])
	{
		if (dist[v] > dist[u] + w(nodes, u, v))
		{
			dist[v] = dist[u] + w(nodes, u, v);
			return true;
		}
		return false;
	}

	public static long dijkstra(int s, int t, GraphNode nodes[])
	{
		long dist[] = new long[nodes.length];
		initial(nodes, s, dist);
		PriorityQueue<long[]> Q = new PriorityQueue<>(new Comparator<long[]>()
		{
			@Override
			public int compare(long[] o1, long[] o2)
			{
				if (o1[1] < o2[1])
				{
					return -1;
				}
				if (o1[1] > o2[1])
				{
					return 1;
				}
				return 0;
			}
		});
		Q.add(new long[] { s, 0 });
		while (!Q.isEmpty())
		{
			long pair[] = Q.poll();
			int u = (int) pair[0];
			if (pair[1] != dist[u])
			{
				continue;
			}
			if (u == t)
			{
				return pair[1];
			}
			for (int v : nodes[u].adj.keySet())
			{
				if (relax(u, v, nodes, dist))
				{
					Q.add(new long[] { v, dist[v] });
				}
			}
		}
		return -1;
	}
}

class GraphNode
{
	public int index;
	public HashMap<Integer, Integer> adj;

	public GraphNode(int index)
	{
		this.index = index;
		adj = new HashMap<>();
	}

	public void addEdge(int index, int weight)
	{
		if (adj.containsKey(index) && adj.get(index) <= weight)
		{
			return;
		}
		adj.put(index, weight);
	}
}