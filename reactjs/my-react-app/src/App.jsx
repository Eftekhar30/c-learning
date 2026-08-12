import React, { useState, useEffect, useRef } from 'react';

const App = () => {
  const [isOpen, setIsOpen] = useState(false);
  const [hearts, setHearts] = useState([]);
  const audioRef = useRef(null);

  useEffect(() => {
    // Generate random floating hearts
    const newHearts = Array.from({ length: 30 }).map((_, i) => ({
      id: i,
      left: Math.random() * 100 + 'vw',
      animationDuration: Math.random() * 4 + 3 + 's',
      animationDelay: Math.random() * 3 + 's',
      size: Math.random() * 15 + 15 + 'px',
    }));
    setHearts(newHearts);
  }, []);

  const handleOpen = () => {
    setIsOpen(true);
    // Play music when she interacts with the button
    if (audioRef.current) {
      audioRef.current.play().catch(e => console.log("Audio play allowed after interaction"));
    }
  };

  return (
    <div className="app-container">
      {/* All CSS is bundled here to keep it in one file. 
        Using 'clamp' allows fonts and sizes to adjust automatically for mobile and desktop! 
      */}
      <style>
        {`
          :root {
            --primary: #ff758c;
            --secondary: #ff7eb3;
            --bg-dark: #0f0c29;
            --bg-mid: #302b63;
            --bg-light: #24243e;
          }

          body { margin: 0; padding: 0; overflow: hidden; background: var(--bg-dark); }

          .app-container {
            min-height: 100vh;
            background: linear-gradient(135deg, var(--bg-dark) 0%, var(--bg-mid) 50%, var(--bg-light) 100%);
            display: flex;
            justify-content: center;
            align-items: center;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            position: relative;
            color: white;
            text-align: center;
            overflow: hidden;
          }

          /* Animations */
          @keyframes float {
            0% { transform: translateY(100vh) scale(0); opacity: 0; }
            20% { opacity: 0.8; }
            100% { transform: translateY(-10vh) scale(1); opacity: 0; }
          }
          @keyframes pulseText { 0%, 100% { transform: scale(1); } 50% { transform: scale(1.05); } }
          @keyframes fadeIn { from { opacity: 0; transform: translateY(20px); } to { opacity: 1; transform: translateY(0); } }
          @keyframes swing { 0%, 100% { transform: rotate(-10deg); } 50% { transform: rotate(10deg); } }
          @keyframes glow { 0%, 100% { filter: drop-shadow(0 0 10px rgba(255, 215, 0, 0.5)); } 50% { filter: drop-shadow(0 0 25px rgba(255, 215, 0, 0.9)); } }

          .floating-heart {
            position: absolute;
            bottom: -20px;
            z-index: 1;
          }

          .celestial-body {
            position: absolute;
            transform-origin: top center;
            z-index: 2;
          }

          /* Responsive placements for background elements */
          .moon { top: 5%; right: 8%; font-size: clamp(3rem, 8vw, 6rem); animation: swing 6s ease-in-out infinite; }
          .lantern-left { top: 2%; left: 8%; font-size: clamp(2.5rem, 6vw, 4rem); animation: swing 5s ease-in-out infinite, glow 3s infinite; }
          .lantern-right { top: 15%; right: 25%; font-size: clamp(2rem, 5vw, 3rem); animation: swing 4s ease-in-out infinite 1s, glow 4s infinite; }

          .card {
            background: rgba(255, 255, 255, 0.08);
            backdrop-filter: blur(15px);
            -webkit-backdrop-filter: blur(15px);
            padding: clamp(2rem, 5vw, 4rem) clamp(1.5rem, 4vw, 3rem);
            border-radius: 24px;
            border: 1px solid rgba(255, 255, 255, 0.15);
            box-shadow: 0 8px 32px 0 rgba(0, 0, 0, 0.3);
            z-index: 10;
            width: 85%;
            max-width: 450px;
            animation: fadeIn 1.2s ease-out;
            display: flex;
            flex-direction: column;
            align-items: center;
          }

          .photo-frame {
            width: clamp(100px, 25vw, 140px);
            height: clamp(100px, 25vw, 140px);
            border-radius: 50%;
            border: 4px solid var(--primary);
            padding: 4px;
            margin-bottom: 1.5rem;
            object-fit: cover;
            animation: fadeIn 1s ease-out;
            box-shadow: 0 0 20px rgba(255, 117, 140, 0.4);
          }

          .heading {
            font-size: clamp(2.2rem, 7vw, 3.2rem);
            margin: 0 0 10px 0;
            background: linear-gradient(45deg, #ff9a9e, #fecfef);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            animation: pulseText 2.5s infinite;
          }

          .subheading {
            font-size: clamp(1rem, 4vw, 1.3rem);
            margin: 0 0 30px 0;
            color: #e2d1f9;
            font-weight: 300;
          }

          .btn-primary {
            background: linear-gradient(45deg, var(--primary) 0%, var(--secondary) 100%);
            border: none;
            padding: clamp(12px, 3vw, 16px) clamp(24px, 6vw, 32px);
            border-radius: 50px;
            color: white;
            font-size: clamp(1rem, 3vw, 1.2rem);
            font-weight: bold;
            cursor: pointer;
            box-shadow: 0 4px 15px rgba(255, 117, 140, 0.4);
            transition: transform 0.3s ease, box-shadow 0.3s ease;
          }
          
          .btn-primary:hover {
            transform: scale(1.05);
            box-shadow: 0 6px 20px rgba(255, 117, 140, 0.6);
          }

          .message-box {
            animation: fadeIn 0.8s ease-out;
            display: flex;
            flex-direction: column;
            gap: 15px;
          }

          .message {
            font-size: clamp(1.1rem, 3.5vw, 1.3rem);
            line-height: 1.6;
            color: #f8f9fa;
            margin: 0;
          }

          .highlight {
            font-size: clamp(1.3rem, 4.5vw, 1.6rem);
            font-weight: bold;
            color: #ff9a9e;
            display: block;
            margin-top: 15px;
          }
        `}
      </style>

      {/* Floating Hearts */}
      {hearts.map((heart) => (
        <div
          key={heart.id}
          className="floating-heart"
          style={{
            left: heart.left,
            fontSize: heart.size,
            animation: `float ${heart.animationDuration} linear infinite`,
            animationDelay: heart.animationDelay,
          }}
        >
          💖
        </div>
      ))}

      {/* Background Eid Elements */}
      <div className="celestial-body moon">🌙</div>
      <div className="celestial-body lantern-left">🏮</div>
      <div className="celestial-body lantern-right">✨</div>

      {/* Hidden Audio Player */}
      <audio ref={audioRef} loop>
        <source src="https://cdn.pixabay.com/download/audio/2022/02/07/audio_24a2c0695c.mp3?filename=romantic-piano-101034.mp3" type="audio/mpeg" />
      </audio>

      {/* Main Glassmorphism Card */}
      <div className="card">
        {/* SURPRISE PHOTO: Change this URL to a picture of you two! */}
        {isOpen && (
          <img 
            src="https://images.unsplash.com/photo-1518199266791-5375a83190b7?q=80&w=300&auto=format&fit=crop" 
            alt="Us" 
            className="photo-frame"
          />
        )}

        <h1 className="heading">Eid Mubarak ✨</h1>
        <p className="subheading">To my beloved girlfriend 🥰</p>

        {!isOpen ? (
          <button className="btn-primary" onClick={handleOpen}>
            Tap to open your Eidi 🎁
          </button>
        ) : (
          <div className="message-box">
            <p className="message">
              May this beautiful day bring as much joy and peace to your life as you bring to mine every single day. You are my greatest blessing.
            </p>
            <span className="highlight">I love you so much! 💖🕌🌹</span>
          </div>
        )}
      </div>
    </div>
  );
};

export default App;