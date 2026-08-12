require('dotenv').config();
const express = require('express');
const app = express();
const userRoutes = require('./src/routes/userRouters');

app.use(express.json());

// Tell the app to use our organized routes
app.use('/api', userRoutes); 

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});