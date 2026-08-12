
app.get('/greet/:someone', (req, res) => {
    const name = req.params.someone;
    res.send('Hello, ' + name+ ' !Welcome to my server');
});


app.get('/add/:num1/:num2', (req, res)=>{
    const num1 = Number(req.params.num1);
    const num2 = Number(req.params.num2);
    const sum = num1 + num2;
    res.send('The sum is: ' + sum);
});

app.get('/club/:age', (req, res)=>{
    const userage = Number(req.params.age);

    if(userage>=18){
        res.send('welcome!');
    } else{
        res.send('not eligible');
    }
});

app.get('/checkname/:name', (req, res)=>{
    const username = req.params.name;
    if(username === 'Eftekhar'){
        res.send('welcome to our club');
    } else{
        res.send('wrong user!');
    }
});

app.get('/status', (req,res) => {
    totalVisits = totalVisits +1;
    res.send('This server has been visited '+totalVisits+ ' times');
});

app.get('/user/profile', (req, res)=>{
    const userProfile = {
        name: "Eftekhar",
        occupation: "Backend Developer",
        Learning: "steady",
        isnewborn: true
    };
    res.json(userProfile);
});

app.get('/all-users', (req, res)=>{
    res.json(allUsers);
});

app.get('/user-by-id/:id', (req, res)=>{
    const searchId= Number(req.params.id);
    const foundUser = allUsers.find(user => user.id === searchId);
    if(foundUser){
        res.json(foundUser);
    } else{
        res.status(404).send('User not found');
    }
});

app.get('/promot-user/:id', (req, res) => {
    const searchId = Number(req.params.id);

    const userToPromote = allUsers.find(user => user.id === searchId);
    if(userToPromote){
        userToPromote.role = "Admin";
        saveToDisk();
        res.json({
            message: "User Promoted Successfully",
            updatedUser: userToPromote
        });
    }
});

app.delete('/delete-user/:id', (req, res) => {
    const userRole = req.headers['x-user-role'];

    if(userRole !== 'Admin'){
        return res.status(403).json({
            error: "Access denied: Only Admins can delete users."
        });
    }

    const searchId = Number(req.params.id);
    const initialCount = allUsers.length;

    allUsers = allUsers.filter(user => user.id !==searchId);

    if(allUsers.length < initialCount){
        saveToDisk();
        res.json({message: "User deleted successfully."});
    }else{
        res.status(404).json({error: "Delete failed: User ID does not exist."});
    }
});

app.post('/add-user', (req, res) => {
    const newUser = req.body;

    if(!newUser.name || newUser.name.trim() === ""){
        return res.status(400).json({error: "Validation Failed: Name is required!"});
    }

    const newId = allUsers.length > 0
        ? Math.max(...allUsers.map(user => user.id)) +1 
        : 1;
    
        newUser.id = newId;

    allUsers.push(newUser);
    saveToDisk();

    res.status(201).json({
        message: "user created!",
        totalUsers: allUsers.length
    });
});

app.put('/update-user/:id', (req,res) => {
    const searchId = Number(req.params.id);
    const updatedData = req.body;

    const user = allUsers.find(user => user.id === searchId);
    
    if(user){
        user.name = updatedData.name || user.name;
        user.role = updatedData.role || user.role;
        saveToDisk();
        res.json({
            message: "User updated Successfully!",
            user: user
        });
    }else{
        res.status(404).json({message: "user not found..."});
    }
});

app.get('/search', (req, res) => {
    const roleQuery = req.query.role;

    if(!roleQuery){
        return res.status(400).json({error: "Please provide a role to search for."});
    }

    const matches = allUsers.filter(u =>
         u.role.toLowerCase() === roleQuery.toLowerCase()
    );

    res.json({
        resultsfound: matches.length,
        users: matches
    });
});