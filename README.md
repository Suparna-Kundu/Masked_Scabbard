# ARM Cortex-M4

This repository contains ARM Cortex-M4 code for the higher-order masked SCABBARD.

## Requirements

The code in this repository includes the [pqm4](https://github.com/mupq/pqm4) framework for testing and benchmarking on the [STM32F4 Discovery board](https://www.st.com/en/evaluation-tools/stm32f4discovery.html). We refer to the documentation of [pqm4](https://github.com/mupq/pqm4) for the required prerequisites.


## Running Benchmarks and Tests

To benchmarck Florete use the following command:

```bash
ln -rs ./src/Florete/m4-masked ./pqm4/crypto_kem/saber/
```
To benchmarck Sable use the following command:

```bash
ln -rs ./src/Sable/m4-masked ./pqm4/crypto_kem/saber/
```
To benchmarck Espada use the following command:

```bash
ln -rs ./src/Espada/m4-masked ./pqm4/crypto_kem/saber/
```

Subsequently, apply the following patches to make pqm4 work with the masked Saber API:

```bash
cd pqm4 && git apply ../pqm4.patch
cd mupq && git apply ../../mupq.patch
```

All masked Scabbard's benchmarks can be run using:

```bash
cd pqm4
[sudo -E] python3 benchmarks.py saber
```

Benchmarks can then be found in the [benchmarks](./pqm4/benchmarks) folder.

One can change the number of shares by changing the value of the parameter SABER_SHARES
