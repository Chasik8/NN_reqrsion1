#include<iostream>
#include<cmath>
#include<vector>
#include<SFML\Graphics.hpp>
#include<random>
#include<tuple>
#include<thread>
#include<ctime>
using namespace std;
typedef long long int lint;
typedef long double ldb;
#define PI 3.141592653589793238462643383279
//lint math_thrad(vector<tuple<sf::CircleShape, vector<ldb>>>& m, lint n, ldb w, ldb h) {
//	lint kol_tt = 4;
//	vector<thread> tt(kol_tt);
//	for (lint a = 0; a < n; a += kol_tt) {
//		lint a1 = a;
//		for (lint i = 0; i < kol_tt; ++i) {
//			a1 = a + i;
//			tt[i] = thread([a1, &m, n, w, h]() {
//				resh1(a1, m, n, w, h);
//				});
//		}
//		for (lint i = 0; i < kol_tt; ++i) {
//			tt[i].join();
//		}
//	}
//	return 0;
//}
lint f(ldb n) {
	if (n >= 0) {
		return 1;
	}
	else {
		return -1;
	}
}
lint math(vector<vector<lint>>&m, vector<vector<ldb>>&world,lint komplekt,lint n) {
	lint ran = rand() % (n * n);
	for (lint k = 0; k < komplekt; ++k) {
		ldb kol = 0;
		for (lint a = 0;a < n * n; ++a) {
			kol += m[k][a] * world[ran][a];
		}
		m[k][ran] = f(kol);
	}
	return 0;
}
void init(vector<lint>& m) {
	lint n = sqrt(m.size());
	for (lint a = 0; a < n; ++a) {
		for (lint b = 0; b < n; ++b) {
			m[a * n + b] = (rand() % 2==0?-1:1);
		}
	}
}
void test1(vector<lint>& m) {
	lint n = sqrt(m.size());
	for (lint a = 0; a < n; ++a) {
		for (lint b = 0; b < n; ++b) {
			m[a * n + b] = ((a+b)%2==1 ? -1 : 1);
		}
	}
}
void test2(vector<lint>& m) {
	lint n = sqrt(m.size());
	for (lint a = 0; a < n; ++a) {
		for (lint b = 0; b < n; ++b) {
			m[a * n + b] = (a == b ? 1 : -1);
		}
	}
}
int run() {
	ldb w = 1920, h = 1080;
	sf::RenderWindow window(sf::VideoMode(lint(w), lint(h)), "test");
	lint n = 8,komplect=2;
	lint sq_komplect = ceil(ldb(sqrt(komplect)));
	//lint n = 2;
	lint kef = w / 2 / n/sq_komplect;
	lint kef_sq = kef * n;
	vector<vector<lint>> m_new(komplect,vector<lint>(n*n)), m(komplect,vector<lint>(n*n));
	for (lint i= 0; i < komplect; ++i) {
		init(m[i]);
	}
	test1(m_new[0]);
	test2(m_new[1]);
	sf::RectangleShape point(sf::Vector2f(0, 0));
	point.setFillColor(sf::Color::Green);
	point.setSize(sf::Vector2f(kef, kef));
	sf::RectangleShape point_init(sf::Vector2f(0, 0));
	point_init.setFillColor(sf::Color::Red);
	point_init.setSize(sf::Vector2f(kef, kef));
	vector<vector<ldb>>world(n*n,vector<ldb>(n*n,0));
	for (lint a = 0; a < n*n; ++a) {
		for (lint b = 0; b < n*n; ++b) {
			for (lint i = 0; i < komplect; ++i) {
				if (a != b) {
					world[a][b] += m_new[i][a] * m_new[i][b];
				}
			}
			world[a][b] /= komplect;
		}
	}
	vector<bool> flag (komplect,true);
	lint tim = clock();
	lint epoch = 1000,ep=0,st_cl=0,max_st_cl=100;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (ep < epoch) {
			if (st_cl == max_st_cl) {
			math(m, world, komplect, n);
			
			++ep;
			st_cl = 0;
		}
		}
		++st_cl;
		window.clear();
		for (lint k1 = 0; k1 < sq_komplect; ++k1) {
			for (lint k2 = 0; k2 < sq_komplect; ++k2) {
				if (k1 * sq_komplect + k2 < komplect) {
					if (m[k1 * sq_komplect + k2] == m_new[k1 * sq_komplect + k2] && flag[k1 * sq_komplect + k2]) {
						cout << "Номер: " << k1 * sq_komplect + k2 << "Кол-во итераций: " << ep << endl;
						flag[k1 * sq_komplect + k2] = false;
					}
				for (lint a = 0; a < n; ++a) {
					for (lint b = 0; b < n; ++b) {
						if (m[k1 * sq_komplect + k2][a * n + b] >= 0) {
							point.setPosition(k1 * kef_sq + a * kef, k2 * kef_sq + b * kef);
							window.draw(point);
						}
						if (m_new[k1 * sq_komplect + k2][a * n + b] >= 0) {
							point_init.setPosition(w / 2 + k1 * kef_sq + a * kef, k2 * kef_sq + b * kef);
							window.draw(point_init);
						}
					}
					}
				}
			}
		}
		window.display();
		//cout << 1/ldb((clock() - tim))*1000 << endl;
		//tim = clock();
	}
	return 0;
}
int main() {
	run();
	return 0;
}