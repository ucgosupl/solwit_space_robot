#pragma once

constexpr uint32_t BITBAND_SRAM_REF = 0x20000000;
constexpr uint32_t BITBAND_SRAM_BASE = 0x22000000;

constexpr uint32_t BITBAND_PERIPH_REF = 0x40000000;
constexpr uint32_t BITBAND_PERIPH_BASE = 0x42000000;

template <typename PtrType, uint32_t base, uint32_t ref>
constexpr PtrType * bitband_addr_get(PtrType *address, uint32_t bit)
{
    uint32_t addr_val = reinterpret_cast<uint32_t>(address);

    return reinterpret_cast<PtrType *>(base + (addr_val - ref) * 32 + bit * 4);
}

template <typename PtrType>
constexpr PtrType * bitband_sram_addr_get(PtrType *address, uint32_t bit)
{
    return bitband_addr_get<PtrType, BITBAND_SRAM_BASE, BITBAND_SRAM_REF>(address, bit);
}

template <typename PtrType>
constexpr PtrType * bitband_sram_get(PtrType *address, uint32_t bit)
{
    auto *bit_addr = bitband_sram_addr_get(address, bit);

    return *bit_addr;
}

template <typename PtrType>
void bitband_sram_set(PtrType *address, uint32_t bit)
{
    auto *bit_addr = get_bitband_sram_addr(address, bit);
    *bit_addr = 1;
}

template <typename PtrType>
void bitband_sram_clear(PtrType *address, uint32_t bit)
{
    auto *bit_addr = get_bitband_sram_addr(address, bit);
    *bit_addr = 0;
}

template <typename PtrType>
constexpr PtrType * bitband_periph_addr_get(PtrType *address, uint32_t bit)
{
    return bitband_addr_get<PtrType, BITBAND_PERIPH_BASE, BITBAND_PERIPH_REF>(address, bit);
}

template <typename PtrType>
constexpr PtrType bitband_periph_get(PtrType *address, uint32_t bit)
{
    auto *bit_addr = bitband_periph_addr_get(address, bit);

    return *bit_addr;
}

template <typename PtrType>
void bitband_periph_set(PtrType *address, uint32_t bit)
{
    auto *bit_addr = bitband_periph_addr_get(address, bit);
    *bit_addr = 1;
}

template <typename PtrType>
void bitband_periph_clear(PtrType *address, uint32_t bit)
{
    auto *bit_addr = bitband_periph_addr_get(address, bit);
    *bit_addr = 0;
}
