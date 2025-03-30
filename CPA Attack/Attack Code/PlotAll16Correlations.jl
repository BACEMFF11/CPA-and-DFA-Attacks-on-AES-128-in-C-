using NPZ
using Statistics
using Plots

# Load the measured power traces
traces = npzread("traces.npy")                    # Traces: N measurements x T time points
num_traces, num_points = size(traces)             # Get the dimensions of the traces

# Loop over all 16 AES key bytes (octets)
for octet_index in 1:16
    # Load the prediction matrix for the current byte
    prediction_file = "prediction_matrix_octet$(octet_index).npy"
    P = npzread(prediction_file)                  # Prediction matrix: N measurements x 256 key guesses

    # Get dimensions of the prediction matrix
    _, num_keys = size(P)                         # Should be N x 256

    # Initialize a matrix to store correlation values
    correlations = zeros(Float64, num_keys, num_points)

    # Compute correlation between each key guess and each time point
    for key_guess in 1:num_keys
        for time_point in 1:num_points
            correlations[key_guess, time_point] = cor(P[:, key_guess], traces[:, time_point])
        end
    end

    # Plot correlation curves for the current key byte
    plot(
        correlations',                             # Transposed: each row = key guess curve
        xlabel = "Time Points",
        ylabel = "Correlation",
        title = "Correlations for Byte $(octet_index)",
        legend = false,                            # Hide legend for clarity
        grid = true
    )

    # Save the plot as an image file
    plot_file = "correlation_curves_octet$(octet_index).png"
    savefig(plot_file)

    println("Correlations for byte $(octet_index) computed and plot saved as '$(plot_file)'")
end
