import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Scanner;

public class DijkWithList
{
	public static final long LongInf = Long.MAX_VALUE / 2 - 2;
	public static final int IntegerInf = Integer.MAX_VALUE / 2 - 2;

	private static void initial(int[][] graph, int s, long dist[])
	{
		for (int i = 0; i < graph.length; ++i)
		{
			dist[i] = LongInf;
		}
		dist[s] = 0;
	}

	private static boolean relax(int u, int v, int[][] graph, long dist[])
	{
		if (dist[v] > dist[u] + graph[u][v])
		{
			dist[v] = dist[u] + graph[u][v];
			return true;
		}
		return false;
	}

	public static long dijkstra(int s, int t, int[][] graph, HashMap<Integer, HashSet<Integer>> adj)
	{
		long dist[] = new long[graph.length];
		initial(graph, s, dist);
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
			HashSet<Integer> adjSet = adj.get(u);
			for (int v : adjSet)
			{
				if (relax(u, v, graph, dist))
				{
					Q.add(new long[] { v, dist[v] });
				}
			}
		}
		return -1;
	}
}