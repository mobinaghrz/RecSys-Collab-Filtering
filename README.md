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

## Installation

1. Compile your C++ code
   ```bash
   g++ -o recommendation_app your_code.cpp


2. Install Node.js dependencies
   ```bash
   npm init -y
   npm install express cors

3. Start the Node.js bridge server
   ```bash
   node server.js


4. Start the React application
   ```bash
   npm start

## Project Structure

├── recommendation_app      # Your compiled C++ executable
├── server.js              # Node.js bridge server
├── src/
│   ├── App.js            # Main React component
│   └── App.css           # Pinterest-style styling
├── package.json          # Node.js dependencies
└── README.md            # This file

