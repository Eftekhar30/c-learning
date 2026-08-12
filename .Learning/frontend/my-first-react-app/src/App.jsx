import { useState, useEffect } from 'react'
const App = () => {
    const [students, setStudents] = useState([])

    useEffect(()=>{
      const fetchStudents = async()=>{
        try{
          const response = await fetch('http://localhost:5000/api/students')
          const data = await response.json()

          setStudents(data)
        }
        catch(error){
          console.log("Error fetching data")
        }
      }
      fetchStudents()
    },[])

    return (
        <div style={{ textAlign: 'center', marginTop: '50px' }}>
            <h2>Student Roster(from express server)</h2>
            
            <ul style={{listStyle: 'none', padding: 0}}>
                {students.map((student, index) => (
                    <li key={student.id} style={{margin: '10px 0px'}}>
                        <strong>{student.name}</strong> - Grade {student.grade}
                    </li>
                ))}
            </ul>
        </div>
    );
};

export default App;