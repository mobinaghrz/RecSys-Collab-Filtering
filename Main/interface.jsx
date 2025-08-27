// App.js
import React, { useState } from 'react';
import './App.css';

function App() {
  const [searchId, setSearchId] = useState('');
  const [currentItem, setCurrentItem] = useState(null);
  const [recommendations, setRecommendations] = useState([]);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState('');

  const handleSearch = async () => {
    if (!searchId.trim()) return;
    
    setLoading(true);
    setError('');
    
    try {
      // This would connect to your C++ backend through a Node.js bridge
      const response = await fetch(`http://localhost:3001/search?id=${searchId}`);
      const data = await response.json();
      
      if (data.error) {
        setError(data.error);
      } else {
        setCurrentItem(data);
        
        // Get recommendations based on the title
        const recResponse = await fetch('http://localhost:3001/recommendations', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ title: data.title })
        });
        
        const recData = await recResponse.json();
        setRecommendations(recData.recommendations || []);
      }
    } catch (err) {
      setError('Failed to connect to the server');
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="app">
      <header className="header">
        <div className="header-content">
          <div className="logo">
            <span className="logo-icon">P</span>
            <span className="logo-text">interest</span>
          </div>
          <div className="search-bar">
            <input
              type="text"
              placeholder="Enter ID to search..."
              value={searchId}
              onChange={(e) => setSearchId(e.target.value)}
              onKeyPress={(e) => e.key === 'Enter' && handleSearch()}
            />
            <button onClick={handleSearch} disabled={loading}>
              {loading ? 'Searching...' : 'Search'}
            </button>
          </div>
        </div>
      </header>

      <main className="main-content">
        {error && <div className="error-message">{error}</div>}
        
        {currentItem && (
          <div className="current-item">
            <h2>Search Result</h2>
            <div className="pin-card">
              <div className="pin-image">
                <div className="image-placeholder">Image Preview</div>
              </div>
              <div className="pin-details">
                <h3>{currentItem.title}</h3>
                <p>ID: {currentItem.id}</p>
              </div>
            </div>
          </div>
        )}

        {recommendations.length > 0 && (
          <div className="recommendations">
            <h2>Recommended for You</h2>
            <div className="pins-grid">
              {recommendations.map((item, index) => (
                <div key={index} className="pin-card">
                  <div className="pin-image">
                    <div className="image-placeholder">Image Preview</div>
                  </div>
                  <div className="pin-details">
                    <h3>{item.title}</h3>
                    <p>Matches: {item.matches}</p>
                  </div>
                </div>
              ))}
            </div>
          </div>
        )}
      </main>
    </div>
  );
}

export default App;
