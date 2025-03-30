# AES-128 Algorithm and Cryptanalysis

## Overview
This repository provides an implementation of the AES-128 encryption algorithm, along with two cryptanalysis techniques:

CPA (Correlation Power Analysis)

DFA (Differential Fault Analysis)

These attacks were conducted as part of an academic project on an ATxmega128D4 microcontroller using a ChipWhisperer-Lite board.

## Repository Structure
```
├── AES Code C/                         # AES-128 encryption implementation in C
│   ├── aes.c                           # AES encryption source code
│   ├── aes.h                           # Header file for AES functions
│   └── main.c                          # Test file for AES encryption
│
├── CPA Attack/                         # CPA (Correlation Power Analysis) attack implementation
│   ├── traces.npy                      # Power consumption traces (NumPy format)
│   ├── correlation figures/            # Correlation plots from CPA analysis
│   ├── prediction matrices/            # Prediction matrices for correlation analysis
│   └── attack_code/                    # CPA attack scripts
│       ├── CPA Attack_code_full_key_guess.py      # Python script for key recovery
│       ├── GenerateAll16PredictionMatrices.jl     # Julia script for prediction matrices
│       └── PlotAll16Correlations.jl               # Julia script for plotting correlations
│
└── DFA Attack/                         # DFA (Differential Fault Analysis) attack implementation
    ├── DFA_Attack_code.py              # Python script for DFA attack
    ├── reverse_key_schedule.py         # Script to compute the master key
    ├── entropy_figures/                # Entropy analysis plots
    └── ciphered-faulty-npy/            # Correct and faulty ciphertexts (NumPy format)
```

## AES-128 Implementation
The AES Code C/ folder contains a full AES-128 encryption implementation in C, including the following core functions:

Key Expansion

SubBytes

ShiftRows

MixColumns

AddRoundKey

### How to Compile and Run

```bash
cd "AES Code C"
gcc -o aes main.c aes.c -lm
./aes
```


## CPA Attack (Correlation Power Analysis)
The `CPA Attack/` folder contains the implementation of the Correlation Power Analysis attack. This side-channel attack analyzes the correlation between power consumption and the Hamming Weight (HW) of intermediate values in the first round of AES (SubBytes operation).

### CPA Attack Steps:
1. Collect power traces during encryption (provided as `traces.npy`).
2. Use the provided Julia scripts to generate prediction matrices and correlation figures.
3. Recover the AES key using the Python script.

### How to Run CPA Attack

```bash
cd "CPA Attack/attack_code"
python "CPA_Attack_code_full_key_guess.py"
```

## DFA Attack
The `DFA Attack/` folder contains the implementation of the Differential Fault Analysis attack. This attack is based on Shannon entropy analysis applied to the last SubBytes operation of the final AES round, recovering the last round key and using the reverse key schedule to compute the master key.

### DFA Attack Steps:
1. Inject faults and analyze correct vs faulty ciphertexts.
2. Compute entropy to deduce the last round key.
3. Use the reverse key schedule script to derive the master key.

### How to Run DFA Attack

```bash
cd "DFA Attack"
python dfa_attack.py
python reverse_key_schedule.py
```

## Prerequisites
Ensure the following dependencies are installed before running the code:

- GCC compiler (for AES C code)
- Python (for attack scripts)
- Julia (for CPA attack analysis)
- NumPy and Matplotlib libraries
- Adapt the python and julia codes to have the correct directory of their inputs (traces,prediction matrices , etc.)
  


## ISSUES / AMELIORATIONS 
For any issues or questions, please open an issue on this repository or simply contact me directly.

---
