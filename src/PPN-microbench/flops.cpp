#include <PPN-microbench/flops.hpp>

using std::cout, std::endl;

Flops::Flops() : Microbench("PEAK_PERF", 1) {
    // apparently only works on linux
    // nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    nb_cpus = 1;
    results = new u64[nb_cpus];
    polled_results = new u64*[nb_cpus];
    for (int i = 0; i < nb_cpus; i++) {
        polled_results[i] = new u64[bench_time / poll_interval];
    }
}

Flops::~Flops() {
    delete results;
    for (int i = 0; i < nb_cpus; i++) {
        delete polled_results[i];
    }
    delete polled_results;
}

void Flops::compute(int cpu) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

    u64 ops_per_loop = 25;
    float f[25] = {
        2.675804981625017,  1.7127548609576937, 8.394053602764455,  1.820993044344894,  3.2081009547032,
        9.600025413727275,  7.010938368667033,  4.690678713295635,  3.6011296057149176, 5.609089806126083,
        4.384152016250026,  8.355892348048323,  1.8111681344827124, 4.188242502359115,  2.731348774920066,
        4.508882746565737,  1.354820442048058,  7.583329927093342,  5.390642382894349,  9.237106062978842,
        0.9239440502133589, 0.6979309300791681, 0.1116957016329434, 0.3856552417382597, 0.4839286881420213,
    };

    while (1) {
        f[0] += f[1]  * f[2]  + f[3]  * f[4]  + f[5]  * f[6]  + f[7]  * f[8]  + f[9]  * f[10] + 
                f[11] * f[12] + f[13] * f[14] + f[15] * f[16] + f[17] * f[18] + f[19] * f[20] +
                f[21] * f[22] + f[23] * f[24]; 
        results[cpu] += ops_per_loop;
    }
}

void Flops::run() {
    for (int i = 0; i < 1; i++) {
        executeBench();
    }
}

void Flops::executeBench() {
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

    // Result gathering
    u64 sum = 0;
    for (int i = 0; i < nb_cpus; i++) {
        pthread_cancel(threads[i]); 
        // std::cout << " " << results[i] / time / 1000000 << "Mflops" << std::endl;
        sum += results[i];
    }
    // cout << "total: " << sum / time / 1000000 << "Mflops" << endl;
    
    // Poll pretty print
    for (int j = 0; j < bench_time / poll_interval; j++) {
        for (int i = 0; i < nb_cpus; i++) {
            cout << polled_results[i][j] << "\t";
        }
        cout << endl;
    }

    c = 0;
}

json Flops::getJson() {}