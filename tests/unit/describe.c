#include <bitset.h>
#include <traits/traits.h>
#include <traits-unit/traits-unit.h>

Feature(checkBitsOnOff) {
    {
        const uint64_t bitset = 0;

        for (unsigned i = 0; i < 64; i++) {
            assert_false(bitset_isOn(bitset, i));
            assert_true(bitset_isOff(bitset, i));
        }
    }

    {
        const uint64_t bitset = UINT64_MAX;

        for (unsigned i = 0; i < 64; i++) {
            assert_true(bitset_isOn(bitset, i));
            assert_false(bitset_isOff(bitset, i));
        }
    }

    {
        const uint64_t bitset = 0;
        const size_t sigCounter = traits_unit_get_wrapped_signals_counter();

        traits_unit_wraps(SIGABRT) {
            bitset_isOn(bitset, 64);
        }
        assert_equal(sigCounter + 1, traits_unit_get_wrapped_signals_counter());

        traits_unit_wraps(SIGABRT) {
            bitset_isOff(bitset, 64);
        }
        assert_equal(sigCounter + 2, traits_unit_get_wrapped_signals_counter());
    }
}

Feature(setOn) {
    {
        const uint64_t bitset = 0;
        for (unsigned i = 0; i < 64; i++) {
            assert_equal(1UL << i, bitset_setOn(bitset, i));
        }
    }

    {
        const uint64_t bitset = 0;
        const size_t sigCounter = traits_unit_get_wrapped_signals_counter();
        traits_unit_wraps(SIGABRT) {
            bitset_setOn(bitset, 64);
        }
        assert_equal(sigCounter + 1, traits_unit_get_wrapped_signals_counter());
    }
}

Feature(setOff) {
    {
        const uint64_t bitset = UINT64_MAX;
        for (unsigned i = 0; i < 64; i++) {
            assert_equal(UINT64_MAX - (1UL << i), bitset_setOff(bitset, i));
        }
    }

    {
        const uint64_t bitset = 0;
        const size_t sigCounter = traits_unit_get_wrapped_signals_counter();
        traits_unit_wraps(SIGABRT) {
            bitset_setOff(bitset, 64);
        }
        assert_equal(sigCounter + 1, traits_unit_get_wrapped_signals_counter());
    }
}

Describe("bitset",
         Trait("essentials",
               Run(checkBitsOnOff),
               Run(setOn),
               Run(setOff)
         )
)
