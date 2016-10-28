#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <queue>
#include <cstring>
#include <map>

#define INF 9999999
using namespace std;



int main(int argc, char const *argv[])
{
	string s;

	freopen("movies.csv", "r", stdin);
	
	vector <pair <int, string>> movies;
	getline(cin, s);
	int k = 0;
	while(getline(cin, s))
	{
		string saux;
		for (int i = 0; i < s.size(); ++i)
		{
			saux.push_back(tolower(s[i]));
			if (s[i+1] == '#')
			{
				movies.push_back(make_pair(k, saux));
				break;
			}
		}
		k++;
	}

	vector <vector < pair<int, int> >> ListaAdj (movies.size());
	for (int i = 0; i < movies.size(); ++i)
	{
		for (int j = 0; j < movies.size() ; ++j)
		{
			string cadena1 = movies[i].second;
			string cadena2 = movies[j].second;
			if (cadena1[cadena1.size()-1] == cadena2[0])
			{
				ListaAdj[i].push_back(make_pair(j, cadena2.size()));
			}
		}
	}

	vector <string> cadenas;
	for (int i = 0; i < ListaAdj.size(); ++i)
	{
		int dist[500];
		int paps[500];
		memset(dist, -1, sizeof(dist));
		memset(paps, 0, sizeof(dist));

		string cadena;
		dist[i] = 0; 
		queue <int> q; 
		q.push(i);
		paps[i] = -1; // Porque es la raíz y no tiene antecesores
		int last;
		while (!q.empty()) 
		{
			int u = q.front(); 
			
			q.pop();//quitar el primer elemento de la cola
			for (int j = 0; j < ListaAdj[u].size(); j++) //para cada vértice
			{												  //adyacente a u					
				pair <int, int> vecino_u = ListaAdj[u][j];
				last = vecino_u.first;
				if (dist[vecino_u.first] == -1) 
				{ 	
					dist[vecino_u.first] = dist[u] + vecino_u.second; //
					paps[vecino_u.first] = u;
					q.push(vecino_u.first);	
				}
			}
		}

		int longindex;
		int maixlong = 0;
		for (int t = 0; t < 200; ++t)
		{
			if (dist[t] != -1)
			{
				maixlong < dist[t] ?  maixlong = dist[t], longindex = t: false; 	
			}
		}
		while (longindex != -1)
		{
			cadena.insert(0, movies[longindex].second);
			longindex = paps[longindex];
		}

		cadenas.push_back(cadena);
	}

	string res = "";
	for (auto s: cadenas)
	{	if (s.size() > res.size())
			{
				res =  s;
				//cout << s << endl;
			}
		}
		cout << res.size() << endl;
		cout << res << endl;


	return 0;
}