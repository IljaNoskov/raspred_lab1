#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <atomic>
#include <cstdlib>
#include <chrono>

long trials_count;
std::atomic<long> total_hits(0);
int threads_count;

void find_pi_by_montecarlo(long trials_per_thread) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    long mc_hits = 0;
    for (long i = 0; i < trials_per_thread; i++) {
        double x = dis(gen);
        double y = dis(gen);

        if (x * x + y * y <= 1.0) {
            mc_hits++;
        }
    }

    total_hits += mc_hits; // обновление счетчика
}

int main(int num, char* arr[]) {
  auto start_time = std::chrono::high_resolution_clock::now(); // Запуск таймера
  if (num != 3) {
    std::cerr << "Usage: " << arr[0] << " threads_count trials_count\n";
    return 1;
  }

  threads_count = strtol(arr[1], nullptr, 10);
  trials_count = strtol(arr[2], nullptr, 10);

  std::vector<std::thread> threads;
  long trials_per_thread = trials_count / threads_count;

  // Запуск потоков
  for (int i = 0; i < threads_count; i++) {
    threads.emplace_back(find_pi_by_montecarlo, trials_per_thread);
  }

  // Ожидание завершения всех потоков
  for (auto& thread : threads) {
    thread.join();
  }

  // Вычисляем pi
  double pi = 4.0 * static_cast<double>(total_hits) / static_cast<double>(trials_count);
  std::cout << "Estimated value of pi: " << pi << std::end_timel;

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> total_time = end_time - start_time; // подсчёт времени
  std::cout << "Time taken: " << total_time.count() << " seconds" << std::end_timel;

  return 0;
}
