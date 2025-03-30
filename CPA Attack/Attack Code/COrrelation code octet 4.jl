using NPZ
using Statistics
using Plots

# Load the data
traces = npzread("traces.npy")                    # Measured power traces (N x T)
P = npzread("prediction_matrix_octet4.npy")       # Prediction matrix for byte 4 (N x 256)

# Get dimensions of the data
num_traces, num_points = size(traces)             # traces has dimensions N (samples) x T (time points)
_, num_keys = size(P)                             # P has dimensions N (samples) x 256 (key guesses)

# Initialize a matrix to store correlation values
correlations = zeros(Float64, num_keys, num_points)

# Compute correlation for each key guess and time point
for key_guess in 1:num_keys
    for time_point in 1:num_points
        correlations[key_guess, time_point] = cor(P[:, key_guess], traces[:, time_point])
    end
end

# Plot the correlation curves for each key guess
plot(
    correlations',                     # Transpose: each row represents a key guess
    xlabel = "Time Points",
    ylabel = "Correlation",
    title = "Correlations for Byte 4",
    legend = false,                    # Hide the legend to keep the plot clean
    grid = true
)

# Save the plot as an image
savefig("correlation_curves_octet4.png")

println("Correlations computed and plot saved as 'correlation_curves_octet4.png'")
