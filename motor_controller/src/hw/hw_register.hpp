#pragma once

#include <cstdint>
#include <cstddef>

namespace hw
{
namespace reg
{

class read_only { };
class write_only { };
class read_write : public read_only, public write_only { };

template<unsigned int sz>
struct hw_register_traits {
};

template<>
struct hw_register_traits<8> {
    using internal_type = std::uint8_t;
};

template<>
struct hw_register_traits<16> {
    using internal_type = std::uint16_t;
};

template<>
struct hw_register_traits<32> {
    using internal_type = std::uint32_t;
};

template<>
struct hw_register_traits<64> {
    using internal_type = std::uint64_t;
};

template<std::size_t reg_size, typename register_type = read_write>
class Hw_register
{
public:
    // Alias for convenience
    //
    using reg_type = typename hw_register_traits<reg_size>::internal_type;

    explicit Hw_register(std::uint32_t address) :
            raw_ptr {reinterpret_cast<std::uint32_t *>(address)}
    {
    }

    void operator=(reg_type bit_mask)
    {
      write(bit_mask, register_type { });
    }

    operator reg_type() const
    {
      return read(register_type { });
    }

    void operator|=(std::uint32_t bit_mask)
    {
      or_assign(bit_mask, register_type { });
    }

    void operator&=(std::uint32_t bit_mask)
    {
      and_assign(bit_mask, register_type { });
    }

  protected:
    void write(reg_type bit_mask, write_only)
    {
      *raw_ptr = bit_mask;
    }

    reg_type read(read_only) const
    {
      return *raw_ptr;
    }

    void or_assign(std::uint32_t bit_mask, read_write)
    {
      *raw_ptr |= bit_mask;
    }

    void and_assign(std::uint32_t bit_mask, read_write)
    {
      *raw_ptr &= bit_mask;
    }

private:
    volatile reg_type* const raw_ptr;
};

} //namespace reg
} //namespace hw
