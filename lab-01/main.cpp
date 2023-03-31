#include "state.h"


std::vector<int> routes(stations.size(), 1000);  // Массив кратчайших путей до каждой точки, изначально - 1000
std::vector<int> visited(stations.size(), 0);         // Массив исследованных вершин, изначально заполнен нулями
std::vector<int> routesVector(stations.size()); // Массив пройденных станций для восстановления пути


void OneKBFS(const int& from, const int& to) {
  std::vector<std::queue<int> > atDist(4); // Создаём массив очередей станций, по увеличению пути
  atDist[0].push(from);
  routes[from] = 0;
  int pos = 0, kol = 1; // pos - позиция, на которой рассматривается элемент в массиве очередей
                                       // kol - общее количество вершин во всех очередях
  routesVector[from] = -1;
  while (kol > 0 && visited[to] == 0) { // Исполняется, пока конечная вершина не исследована или пока не кончатся вершины в массиве очередей

    while (atDist[pos % 4].empty()) { // Выбираем длину пути, на котором исследуем новые вершины
      ++pos;
    }

    int u = atDist[pos % 4].front(); // Выбираем вершину
    atDist[pos % 4].pop();
    --kol;

    if (visited[u] == 0) {

      visited[u] = 1; // Помечаем как посещённую

      for (std::pair<int, int> station : metro[u]) { // Рассматриваем соседние с ней станции
        if (routes[station.first] > (routes[u] + station.second)) {

          routes[station.first] = routes[u] + station.second;
          routesVector[station.first] = u;

          atDist[routes[station.first] % 4].push(station.first); // Добавлям рассмотренные станции в очередь к исследованию

          ++kol;
        }
      }
    }
  }
}

int main() {
    setlocale(LC_ALL, "Russian");

    for (int i = 0; i < stations.size(); ++i) {  // Вывод станций с индексами
        std::cout << stations[i] << '\t' << i << std::endl;
    }

    int from, to;   // Объявление переменных для индексов станции откуда едем и куда едем

    std::cout << std::endl << "Введите 'из' индекс станции и 'куда' индекс станции:" << std::endl;

    std::cin >> from >> to;  // Ввод

    std::cout << std::endl << "Метод поиска 1-k BFS" << std::endl << std::endl;

    // BFS
    {
        OneKBFS(from, to);  // Запускаем поиск кратчайших путей

        // Выводим
        std::cout << "Из: " << stations[from] << "\tВ: " << stations[to] << std::endl;

        std::cout << routes[to] << " минут(ы)" << std::endl;

        std::vector<int> path;
        for (int v = to; v != -1; v = routesVector[v])
        path.push_back(v);
        std::reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i)
        std::cout << i << ") " << stations[path[i]] << " (" << routes[path[i]] << " минут(ы))" << std::endl;
    }

    return 0;
}

