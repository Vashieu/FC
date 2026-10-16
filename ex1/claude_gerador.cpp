// Linear Congruential Generator (LCG)
//
//   X_{n+1} = (a * X_n + c) mod m
//
// Scope chosen: 64-bit state, m = 2^64.
// Using uint64_t makes the "mod 2^64" free, because unsigned overflow in C++
// is defined to wrap around modulo 2^64.
//
// Constants are Knuth's MMIX parameters:
//   a = 6364136223846793005
//   c = 1442695040888963407
// They satisfy the Hull-Dobell theorem (c odd, a-1 divisible by 4),
// so the generator has the full period of 2^64.

#include <cstdint>
#include <iostream>
#include <iomanip>

class LCG {
public:
    using state_t = std::uint64_t;

    static constexpr state_t A = 6364136223846793005ULL;
    static constexpr state_t C = 1442695040888963407ULL;
    // m = 2^64 (implicit via unsigned wraparound)

    explicit LCG(state_t seed = 1) : state_(seed) {}

    // Advance the generator and return the full 64-bit state.
    state_t next_raw() {
        state_ = A * state_ + C;  // wraps mod 2^64
        return state_;
    }

    // LCGs with a power-of-two modulus have weak LOW bits (bit k has period
    // 2^(k+1)), so we return the HIGH 32 bits as the output.
    std::uint32_t next_u32() {
        return static_cast<std::uint32_t>(next_raw() >> 32);
    }

    // Uniform integer in [lo, hi] (inclusive), using rejection sampling
    // to avoid modulo bias.
    std::uint32_t next_in_range(std::uint32_t lo, std::uint32_t hi) {
        const std::uint64_t span = static_cast<std::uint64_t>(hi) - lo + 1;
        const std::uint64_t limit = (1ULL << 32) - ((1ULL << 32) % span);
        std::uint64_t r;
        do {
            r = next_u32();
        } while (r >= limit);
        return static_cast<std::uint32_t>(lo + (r % span));
    }

    // Uniform double in [0, 1), using the top 53 bits of the state.
    double next_double() {
        return static_cast<double>(next_raw() >> 11) * (1.0 / 9007199254740992.0); // 2^53
    }

private:
    state_t state_;
};

int main() {
    LCG rng(42);

    std::cout << "Raw 64-bit states:\n";
    for (int i = 0; i < 3; ++i)
        std::cout << "  " << rng.next_raw() << '\n';

    rng = LCG(42);
    std::cout << "\nTop-32-bit outputs:\n";
    for (int i = 0; i < 5; ++i)
        std::cout << "  " << rng.next_u32() << '\n';

    std::cout << "\nDice rolls (1-6):";
    for (int i = 0; i < 10; ++i)
        std::cout << ' ' << rng.next_in_range(1, 6);

    std::cout << "\n\nDoubles in [0,1):\n" << std::fixed << std::setprecision(6);
    for (int i = 0; i < 5; ++i)
        std::cout << "  " << rng.next_double() << '\n';

    return 0;
}