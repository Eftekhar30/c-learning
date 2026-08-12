const fs = require('fs');
const path = require('path');
const dataPath = path.join(__dirname, '../data/data.json');

const allUsers = [];

const saveToDisk = () => {
    fs.writeFileSync(dataPath.dataPath, JSON.stringify(allUsers, null,2));
};

exports.getAllUsers = (req, res) => {
    res.json(allUsers);
};

exports.deleteUser = (req,res) =>{
    const userRole = req.header['x-user-role'];

    if(userRole !== 'Admin'){
        return res.status(404).json({error: "Access Denied!"});
    }

    const searchId = Number(req.params.id);
    const initialCount = allUsers.length;

    allUsers = allUsers.filter(u => u.id !== searchId);
    if(allUsers.length > initialCount){
        saveToDisk();
        res.json({message: "User has been deleted successfully!"});
    } else{
        res.status(404).JSON({error: "User not found!"});
    }
};


