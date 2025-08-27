// server.js
const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 3001;

app.use(cors());
app.use(express.json());

// Endpoint to search by ID
app.get('/search', (req, res) => {
  const { id } = req.query;
  
  if (!id) {
    return res.status(400).json({ error: 'ID is required' });
  }

  // Spawn your C++ executable
  const cppProcess = spawn('./your_executable_name', [id]);
  
  let result = '';
  let error = '';

  cppProcess.stdout.on('data', (data) => {
    result += data.toString();
  });

  cppProcess.stderr.on('data', (data) => {
    error += data.toString();
  });

  cppProcess.on('close', (code) => {
    if (code !== 0 || error) {
      return res.status(500).json({ error: error || 'Failed to execute search' });
    }
    
    // Parse the result from your C++ program
    // The expected format: "ID: {id} -> Title: {title}"
    const match = result.match(/ID: \d+ -> Title: (.+)/);
    
    if (match && match[1]) {
      res.json({ id, title: match[1] });
    } else if (result.includes('No title found')) {
      res.json({ id, title: 'No title found for this ID' });
    } else {
      res.status(404).json({ error: 'ID not found' });
    }
  });
});

// Endpoint to get recommendations based on title
app.post('/recommendations', (req, res) => {
  const { title } = req.body;
  
  if (!title) {
    return res.status(400).json({ error: 'Title is required' });
  }

  // This would need to be adapted to work with your C++ program
  // You might need to modify your C++ code to accept title input
  // or create a separate executable for recommendations
  
  // For now, returning mock data
  res.json({
    recommendations: [
      { title: 'Similar Item 1', matches: 5 },
      { title: 'Similar Item 2', matches: 4 },
      { title: 'Similar Item 3', matches: 3 },
      { title: 'Similar Item 4', matches: 3 },
      { title: 'Similar Item 5', matches: 2 },
    ]
  });
});

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
