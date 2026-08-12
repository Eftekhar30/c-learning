const express = require('express')
const cors = require('cors')
const mongoose = require('mongoose')

const app = express()
const PORT = 5000

app.use(cors())
app.use(express.json())

const MONGO_URL = "mongodb+srv://eftu303_db_user:BE6nQtncrtMO60Hl@cluster0.tk2vlwd.mongodb.net/?appName=Cluster0"
//const MONGO_URL = "mongodb+srv://eftu303_db_user:BE6nQtncrtMO60Hl@cluster0.tk2vlwd.mongodb.net/school?retryWrites=true&w=majority"

mongoose.connect(MONGO_URL)
    .then(()=> console.log("MongoDB connect successfull"))
    .catch((err)=> console.log("Database error",err))

const schoolSchema = new mongoose.Schema({
    name: {type: String, required: true},
    grade: {type: Number, required: true}
})

const student = mongoose.model('student', schoolSchema)

app.get('/api/students', async (req,res)=>{
    try{
        const students = await student.find()
        res.json(students)
    } catch(error){
        res.status(500).json({message: "server error fetching data"})
    }
})

app.post('/api/students', async (req,res)=>{
    try{
        const {name, grade} = req.body
        const newStudent = new Student({name, grade})
        await newStudent.save()
        res.status(201).json(newStudent)
    } catch(error){
        res.status(400).json({message: "error saving data"})
    }

})
app.listen(PORT , ()=>{
    console.log(`server running ar port ${PORT}`)
})