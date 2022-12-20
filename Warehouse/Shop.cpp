#include "Shop.h"

std::vector<Product> Shop::GenerateQuery() {
    std::vector<Product> query;
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> gen(10, 10000);
    for (auto item : possible_items_) {
        query.push_back(Product(gen(rng), gen(rng) % 50 + 1,
            gen(rng) % 17 + 1, gen(rng) % 30 + 1));
    }
    return query;
}