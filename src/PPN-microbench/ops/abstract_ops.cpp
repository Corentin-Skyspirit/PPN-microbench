#include <PPN-microbench/ops/abstract_ops.hpp>

using std::cout, std::endl;

AbstractOps::AbstractOps(std::string name, int rep) : Microbench(name, rep) {
    // apparently only works on linux
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    nb_cpus = 4;
    results = new u64[nb_cpus];
    polled_results = new u64*[nb_cpus];
    for (int i = 0; i < nb_cpus; i++) {
        polled_results[i] = new u64[bench_time / poll_interval];
    }
}

AbstractOps::~AbstractOps() {
    delete results;
    delete[] polled_results;
    // for (int i = 0; i < nb_cpus; i++) {
    //     delete polled_results[i];
    // }
    // delete polled_results;
}

void AbstractOps::run() {
    for (int i = 0; i < 1; i++) {
        executeBench();
    }
}

void AbstractOps::executeBench() {
    pthread_t threads[nb_cpus];
    cpu_set_t sets[nb_cpus];

    // Thread creation and pinning
    for (int i = 0; i < nb_cpus; i++) {
        results[i] = 0;
        CPU_ZERO(&sets[i]);
        CPU_SET(i, &sets[i]);
        pthread_create(&threads[i], NULL, thread_helper, this);
        pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &sets[i]);
    }

    // Sleep and polling
    for (int i = 0; i < bench_time; i += poll_interval) {
        usleep(poll_interval * 1000);
        for (int j = 0; j < nb_cpus; j++) {
            polled_results[j][i / poll_interval] = results[j];
        }
    }

    // Stopping threads
    for (int i = 0; i < nb_cpus; i++) {
        pthread_cancel(threads[i]); 
    }
    
    // Poll pretty print
    for (int j = 0; j < bench_time / poll_interval; j++) {
        for (int i = 0; i < nb_cpus; i++) {
            cout << polled_results[i][j] << "\t";
        }
        cout << endl;
    }

    c = 0;
}

json AbstractOps::getJson() {}