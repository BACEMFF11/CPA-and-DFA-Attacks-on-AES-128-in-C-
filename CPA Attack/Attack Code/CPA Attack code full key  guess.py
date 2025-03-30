import numpy as np
from scipy.stats import pearsonr
import os

# Path to the folder containing prediction matrices and traces
folder_path = "D:\\telechargement"

# Load the traces of power consumption
traces = np.load(os.path.join(folder_path, "traces.npy"))  # (N x T)
num_traces, num_time_points = traces.shape

# Initialize a list to store the best key guess for each byte
aes_key = []

# Loop through all 16 prediction matrices
for octet_index in range(1, 17):
    print(f"\nProcessing octet {octet_index}...")

    # Construct the filename for the current octet
    prediction_file = os.path.join(folder_path, f"prediction_matrix_octet{octet_index}.npy")

    # Load the prediction matrix for the current octet
    prediction_matrix = np.load(prediction_file)  # (N x 256)
    num_hypotheses = prediction_matrix.shape[1]  # Should be 256

    # Initialize the correlation matrix
    correlations = np.zeros((num_hypotheses, num_time_points))

    # Compute Pearson correlation between predictions and traces
    for key_guess in range(num_hypotheses):
        for time_point in range(num_time_points):
            corr, _ = pearsonr(prediction_matrix[:, key_guess], traces[:, time_point])
            correlations[key_guess, time_point] = corr

    # Find the key guess with the highest correlation
    max_index = np.unravel_index(np.argmax(np.abs(correlations)), correlations.shape)
    best_key_guess = max_index[0]  # Best key hypothesis for this byte
    best_time_point = max_index[1]

    # Append the result to the AES key list
    aes_key.append(best_key_guess)

    print(f"  ➔ Best key guess for octet {octet_index}: {best_key_guess} (0x{best_key_guess:02X}) à l'instant : {best_time_point}")

# Display the full AES key
aes_key_hex = ''.join(f'{byte:02X}' for byte in aes_key)
print("\n🔑 Recovered AES Key (Hex):", aes_key_hex)
print("🔑 Recovered AES Key (Bytes):", aes_key)
