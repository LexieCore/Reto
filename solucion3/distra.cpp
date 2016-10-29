#include <bits/stdc++.h>
using namespace std;
vector <int> Termina_con[500];
vector < pair<int, int> > Lista[250];
vector <string> Palabras;
int total, n, final;
vector <int > solucion;
int s_v;

int mayor;
void distra(int s)
{
	vector <int> distancia(n, -1), papa(n, -1);
	bitset <200> visitados;
	//priority_queue <pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>>   > cola;
	priority_queue <pair<int, int>   > cola;
	int v, u, w;

	distancia[s] = Palabras[s].size()-1;
	papa[s] = -1;
	cola.push( make_pair(distancia[s],s ) );
	while ( !cola.empty() )	
	{
		pair <int, int> frente = cola.top(); cola.pop();
		v = frente.second;

		if ( visitados[v] ) continue;

		visitados[v] = true;
		for (auto &e:Lista[v] )
		{
			u = e.first; w = e.second;
			if (visitados[u]) continue;
			if ( distancia[u] < distancia[v] + w )
			{
				distancia[u] = distancia[v] + w;
				papa[u] = v;
				cola.push( make_pair(distancia[u], u)  );
			}
		}
	}
	u= v = max_element(distancia.begin(), distancia.end()) - distancia.begin();
	int cosa = 500;
	if ( mayor<distancia[v] )
	{
		mayor=distancia[v];
		solucion = papa;
		s_v = v;
	}
	//else return;
	//while (v!=-1 and cosa--)
	//{
	//	cout<<Palabras[v]<<"\n";
	//	v = papa[v];
	//}
	//cout<<distancia[u]<<endl;
	//printf("\n\n\n\n");
}

void imprinir(int v, bool primera)
{
	if (v!=-1)
	{		
		imprinir( solucion[v], false );
		if (not primera)
			Palabras[v].pop_back();
		cout<<Palabras[v];
	}
}

void imprinir2(int v)
{
	if (v!=-1)
	{		
		imprinir2( solucion[v]);		
		cout<<Palabras[v]<<"\n";
	}
}
int main()
{
	freopen("A.in", "r", stdin);	
	int fin, i, ini;	
	string s;
	i = 0;	
	while ( getline(cin,s) )
	{
		fin = s[ s.size() -1 ] = tolower(s[ s.size() -1 ]);
		if (fin == 'x') continue;
		s[0] = tolower( s[0] );		
		
		Palabras.push_back( s );
		Termina_con[fin].push_back( i );
		++i;
	}

	i = 0;
	for ( auto &s:Palabras )
	{
		ini = s[0];
		for ( auto e:Termina_con[ini] )
			Lista[e].push_back( make_pair(i, Palabras[i].size() - 1) );
		++i;
	}

	/*for (int i = 0; i < Palabras.size(); ++i)
	{
		cout<<Palabras[i]<<"\n";
		for (int j = 0; j < Lista[i].size(); ++j)
			cout<<Palabras[ Lista[i][j] ]<<"\n";
		cout<<"\n\n";
	}*/
	//final = total = 0;
	n=Palabras.size();
	for (int i = 0; i < n; ++i)
		distra(i);
	
	freopen("A2.out", "w", stdout);
	imprinir2(s_v);
	fclose(stdout);

	freopen("A.out", "w", stdout);
	imprinir(s_v, true);
	fclose(stdout);

	fclose(stdin);
	return 0;
}