# RecSys-Collab-Filtering
Recommendation System using Collaborative Filtering

# Recommendation System using Collaborative Filtering in C++

This project implements a recommendation system using collaborative filtering to suggest items (e.g., Pinterest pins) to users based on their preferences and behavior. The system uses matrix factorization (Singular Value Decomposition - SVD) to reduce dimensionality and improve recommendations. Efficient data structures like graphs, hash maps, and priority queues are used to handle large datasets and retrieve top-k recommendations.

## Key Features
- Graph-based representation of user-item interactions.
- Matrix factorization (SVD) for dimensionality reduction.
- Efficient retrieval of top-k recommendations using priority queues.
- Optimized for scalability using hash maps and trees.

## Dataset
The system is tested on [Dataset Name] (e.g., MovieLens, Pinterest-like datasets).

## Usage
1. Clone the repository.
2. Build the project using CMake.
3. Run the executable with the dataset file as input.

## Dependencies
- Eigen (for matrix operations)
- CMake (for build management)

## Future Work
- Implement Alternating Least Squares (ALS) for matrix factorization.
- Add support for real-time recommendations.
- Integrate with a web service for interactive recommendations.